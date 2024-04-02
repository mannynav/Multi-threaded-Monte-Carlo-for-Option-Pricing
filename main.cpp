
#include <iostream>
#include <boost/math/distributions/normal.hpp>

#include "ApplicationWrapper.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

std::pair<double, double> calculate_d1_d2(double S0, double K, double T, double r, double sigma) {
    if (sigma <= 0.0) {
        throw std::invalid_argument("Volatility (sigma) must be positive.");
    }
    double d1 = (std::log(S0 / K) + (r + sigma * sigma / 2.0) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    return std::make_pair(d1, d2);
}

// Black-Scholes call option pricing formula
double black_scholes_call_price(double S0, double K, double T, double r, double sigma) {
    if (S0 <= 0.0 || K <= 0.0 || T <= 0.0) {
        throw std::invalid_argument("Invalid input parameters (spot price, strike price, or time to maturity must be positive).");
    }
    std::pair<double, double> d1_d2 = calculate_d1_d2(S0, K, T, r, sigma);
    double d1 = d1_d2.first;
    double d2 = d1_d2.second;

    boost::math::normal_distribution<>  norm_dist(0.0, 1.0); //
    double N_d1 = boost::math::cdf(norm_dist, d1);
    double N_d2 = boost::math::cdf(norm_dist, d2);

    return S0 * N_d1 - K * exp(-r * T) * N_d2;
}

int main(int argc, char* argv[])
{

    std::cout << "Main method" << std::endl;
	Application_Wrapper app;
	app.run();


    double bs_call_price = black_scholes_call_price(100, 100, 1, 0.05, 0.20);
    std::cout << "BS price: " << bs_call_price << std::endl;

	std::cout << "Finished main! " << std::endl;
   
}
