#pragma once

#ifndef SAMPLINGMETHOD_H
#define SAMPLINGMETHOD_H

#include <vector>
#include <memory>
#include <random>
#include "Eigen/Dense"
#include <boost/math/distributions/normal.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include "PseudoFactory.h"


    double norminv(double u);

    class SamplingMethod {
    public:
        virtual ~SamplingMethod() = default;
        virtual void fill_vector(std::vector<double>& variates, boost::mt19937& rng) = 0;
        virtual std::vector<double> likelihood_ratio() const
        {
            return { 1.0 };
        }
        virtual std::string getName() const = 0;
        virtual std::unique_ptr<SamplingMethod> clone() const = 0;
        virtual void set_path_index(int index) = 0;
    };

    class StandardMCSampler : public SamplingMethod {
    public:
        StandardMCSampler(PseudoFactory& factory) {}
        void fill_vector(std::vector<double>& variates, boost::mt19937& rng) override;
        std::string getName() const override { return "Standard Monte Carlo"; }
        std::unique_ptr<SamplingMethod> clone() const override { return std::make_unique<StandardMCSampler>(*this); }
        void set_path_index(int index) override { 
            //std::cout << " Standard MC Sampler" << std::endl; 
        } // No-op for StandardMCSampler
     
    };

    class AntitheticSampler : public SamplingMethod {
    public:
        AntitheticSampler(PseudoFactory& factory) : path_index_(0), is_antithetic_(false)
        {
            steps_ = factory.GetNumberTotalSteps();
        }
        void fill_vector(std::vector<double>& variates, boost::mt19937& rng) override;
        std::string getName() const override { return "Antithetic"; }
        std::unique_ptr<SamplingMethod> clone() const override { return std::make_unique<AntitheticSampler>(*this); }
        
        
    public:
        void set_path_index(int index) { path_index_ = index; is_antithetic_ = (index % 2 != 0); 
        //std::cout << "Antithetic Sampler" << std::endl;
        }
    private:
        int steps_;
        int path_index_;
        mutable bool is_antithetic_;
        mutable std::vector<double> last_normal_path_;
    };
    
    class HaltonSampler : public SamplingMethod {
    public:
        HaltonSampler(PseudoFactory& factory)
            : steps_(factory.GetNumberTotalSteps()), path_index_(0) {
        }
        void fill_vector(std::vector<double>& variates, boost::mt19937& rng) override;
        std::string getName() const override { return "Halton"; }
        std::unique_ptr<SamplingMethod> clone() const override { return std::make_unique<HaltonSampler>(*this); }
        void set_path_index(int index) { path_index_ = index;
        //std::cout << " Halton Sampler" << std::endl;
        }
    private:
        int steps_;
        int path_index_;
    };

    class TerminalStratifiedSampler : public SamplingMethod {
    public:
        TerminalStratifiedSampler(PseudoFactory& factory, int num_strata=50) : T_(factory.GetExpiry()), steps_(factory.GetNumberTotalSteps()), S0_(factory.GetS0()), K_(factory.GetStrike()), r_(factory.GetRiskFreeRate()), sigma_(factory.GetVolatility()), path_index_(0)
        {
            // Compute d2 for ITM probability
            d2_ = (std::log(S0_ / K_) + (r_ - 0.5 * sigma_ * sigma_) * T_) / (sigma_ * std::sqrt(T_));
            p_itm_ = 0.5 * (1.0 + std::erf(-d2_ / std::sqrt(2.0)));
            num_strata_ = num_strata;
            
        }
        void fill_vector(std::vector<double>& variates, boost::mt19937& rng) override;
        std::string getName() const override { return "Terminal Stratified (ITM)"; }
        std::unique_ptr<SamplingMethod> clone() const override { return std::make_unique<TerminalStratifiedSampler>(*this); }
        void set_path_index(int index)
        {
            path_index_ = index;
            //std::cout << "Terminal Stratified Sampler" << std::endl;

        }
        //std::unique_ptr<SamplingMethod> clone() const override { return std::make_unique<TerminalStratifiedSampler>(T_, steps_, num_strata_, S0_, K_, r_, sigma_); }
    private:
        double T_;
        int steps_;
        int num_strata_{};
        int path_index_;
        double S0_, K_, r_, sigma_;
        double d2_, p_itm_; // ITM probability
    };

    class AdaptiveImportanceSampler : public SamplingMethod {
    public:
        AdaptiveImportanceSampler(PseudoFactory& factory)
            : S0_(factory.GetS0()), K_(factory.GetStrike()), r_(factory.GetRiskFreeRate()),
            sigma_(factory.GetVolatility()), T_(factory.GetExpiry()), steps_(factory.GetNumberTotalSteps()),
            path_index_(0), last_W_T_(0.0) {

            // Linearized theta for put option
            double mu = r_ - 0.5 * sigma_ * sigma_;
            theta_ = (std::log(K_ / S0_) - mu * T_) / (sigma_ * T_);
        }
        void fill_vector(std::vector<double>& variates, boost::mt19937& rng) override;
        std::vector<double> likelihood_ratio() const override;
        std::string getName() const override { return "Adaptive Importance Sampling"; }
        std::unique_ptr<SamplingMethod> clone() const override { return std::make_unique<AdaptiveImportanceSampler>(*this); }
        void set_path_index(int index) { path_index_ = index;
        //std::cout << "Adaptive Importance Sampler" << std::endl;

        }
    private:
        double S0_, K_, r_, sigma_, T_;
        int steps_;
        int path_index_;
        double theta_; // Drift shift
        mutable double last_W_T_; // Store W_T for likelihood ratio
    };


#endif // SAMPLINGMETHOD_H