
#include "SamplingMethods.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>




    double norminv(double u) {
        if (u <= 0.0) return -7.0;
        if (u >= 1.0) return 7.0;
        if (u == 0.5) return 0.0;

        static const double a[4] = { 2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637 };
        static const double b[4] = { -8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833 };
        static const double c[9] = { 0.3374754822726147, 0.9761690190917186, 0.1607979714918209,
                                   0.0276438810333863, 0.0038405729373609, 0.0003951896511919,
                                   0.0000321767881768, 0.0000002888167364, 0.0000003960315187 };

        double x = u - 0.5;
        if (std::abs(x) < 0.42) {
            double r = x * x;
            return x * (((a[3] * r + a[2]) * r + a[1]) * r + a[0]) /
                ((((b[3] * r + b[2]) * r + b[1]) * r + b[0]) * r + 1.0);
        }

        double r = x > 0.0 ? 1.0 - u : u;
        r = std::log(-std::log(r));

        double result = c[0];
        for (int i = 1; i < 9; ++i) {
            result += c[i] * std::pow(r, i);
        }

        return x < 0.0 ? -result : result;
    }


    // Helper function to generate Halton sequence for index n and base b
    double halton_sequence(int n, int base) {
        double result = 0.0;
        double f = 1.0 / base;
        int i = n;
        while (i > 0) {
            result += f * (i % base);
            i /= base;
            f /= base;
        }
        return result;
    }



    // Helper function to get the i-th prime number (starting with 2, 3, 5, ...)
    int get_prime(int i) {
        static const std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
        if (i >= primes.size()) {
            throw std::runtime_error("Not enough prime numbers for Halton sequence dimensions");
        }
        return primes[i];
    }



    void StandardMCSampler::fill_vector(std::vector<double>& variates, boost::mt19937& rng) {

        std::normal_distribution<double> dist(0.0, 1.0);
        for (int i = 0; i < variates.size(); ++i) {
            variates[i] = dist(rng);

        }
    }

  


    void AntitheticSampler::fill_vector(std::vector<double>& variates, boost::mt19937& rng) {
        variates.resize(steps_);
        if (!is_antithetic_) {
            last_normal_path_.resize(steps_);
            boost::normal_distribution<double> dist(0.0, 1.0);
            boost::variate_generator<boost::mt19937&, boost::normal_distribution<double>> gen(rng, dist);
            for (int t = 0; t < steps_; ++t) {
                last_normal_path_[t] = gen();
                variates[t] = last_normal_path_[t];
            }
            is_antithetic_ = true;
        }
        else {
            for (int t = 0; t < steps_; ++t) {
                variates[t] = -last_normal_path_[t];
            }
            is_antithetic_ = false;
        }
    }


    void TerminalStratifiedSampler::fill_vector(std::vector<double>& variates, boost::mt19937& rng) {

        variates.resize(steps_);

        std::uniform_real_distribution<double> dist(0.0, 1.0);
        //boost::uniform_real_distribution<double> dist(0.0, 1.0);
        boost::normal_distribution<double> norm_dist(0.0, 1.0);
        double sqrt_T = std::sqrt(T_);
        double dt = T_ / steps_;

        // Assign path to a stratum based on path_index_

        int stratum = path_index_ % num_strata_; // Map path_index_ to a stratum

        double u = (dist(rng) + stratum) / num_strata_;
        double z = sqrt_T * norminv(u); // Stratified W_T

        std::vector<double> W(steps_ + 1, 0.0);
        W[steps_] = z;

        // Brownian bridge construction
        std::function<void(int, int)> fill_bridge = [&](int left, int right) {
            if (right - left <= 1) return;
            int mid = (left + right) / 2;
            double t_left = left * dt;
            double t_mid = mid * dt;
            double t_right = right * dt;
            double mean = ((t_right - t_mid) * W[left] + (t_mid - t_left) * W[right]) / (t_right - t_left);
            double variance = (t_right - t_mid) * (t_mid - t_left) / (t_right - t_left);
            W[mid] = mean + std::sqrt(variance) * norm_dist(rng);
            fill_bridge(left, mid);
            fill_bridge(mid, right);
            };
        fill_bridge(0, steps_);


        // Compute increments
        for (int t = 0; t < steps_; ++t) {
            variates[t] = (W[t + 1] - W[t]) / std::sqrt(dt);
        }
    }

 
    void HaltonSampler::fill_vector(std::vector<double>& variates, boost::mt19937& /*rng*/) {
        variates.resize(steps_);
        boost::math::normal normal(0.0, 1.0);

        // Generate Halton sequence for path_index_ across steps_ dimensions
        for (int t = 0; t < steps_; ++t) {
            int base = get_prime(t); // Use different prime for each time step
            double u = halton_sequence(path_index_ + 1, base); // Start at index 1 to avoid u=0
            variates[t] = boost::math::quantile(normal, u);
        }

        // Debugging: Compute S_T (assume S0_ = 100, r_ = 0.05, sigma_ = 0.2, T_ = 1)
        double S_T = 100.0;
        double dt = 1.0 / steps_;
        double drift = (0.05 - 0.5 * 0.2 * 0.2) * dt;
        for (int t = 0; t < steps_; ++t) {
            S_T *= std::exp(drift + 0.2 * std::sqrt(dt) * variates[t]);
        }

        // Log for first 20 paths
        if (path_index_ < 20) {
            double W_T = 0.0;
            for (int t = 0; t < steps_; ++t) {
                W_T += variates[t] * std::sqrt(dt);
            }
            //std::cout << "Halton Path " << path_index_ << ": W_T = " << W_T << ", S_T = " << S_T << std::endl;
        }
    }

 

    void AdaptiveImportanceSampler::fill_vector(std::vector<double>& variates, boost::mt19937& rng) {
        variates.resize(steps_);
        boost::random::normal_distribution<double> dist(0.0, 1.0);
        boost::variate_generator<boost::mt19937&, boost::random::normal_distribution<double>> gen(rng, dist);

        // Generate standard normal variates and compute W_T
        last_W_T_ = 0.0;
        double dt = T_ / steps_;
        double sqrtdt = std::sqrt(dt);
        for (int t = 0; t < steps_; ++t) {
            variates[t] = gen();
            last_W_T_ += variates[t] * sqrtdt;
        }

        // Debugging: Compute S_T with theta shift
        double S_T = S0_;
        double drift = (r_ - 0.5 * sigma_ * sigma_ + theta_) * dt;
        for (int t = 0; t < steps_; ++t) {
            S_T *= std::exp(drift + sigma_ * sqrtdt * variates[t]);
        }

        if (path_index_ < 20) {
            std::cout << "Importance Path " << path_index_ << ": theta = " << theta_
                << ", W_T = " << last_W_T_ << ", S_T = " << S_T << std::endl;
        }
    }

    std::vector<double> AdaptiveImportanceSampler::likelihood_ratio() const {
        // Likelihood ratio = exp(-theta * W_T - theta^2 * T / 2)
        double lr = std::exp(-theta_ * last_W_T_ - 0.5 * theta_ * theta_ * T_);
        return { lr };
    }

 



