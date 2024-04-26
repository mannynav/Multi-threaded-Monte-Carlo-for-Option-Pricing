#include "AnalyticalFormulas.h"
#include <stdexcept>
#include <boost/math/distributions/normal.hpp>


double AnalyticalFormulas::Black_Scholes_Call(double S0, double K, double T, double r, double sigma)
{
	if (S0 <= 0.0 || K <= 0.0 || T <= 0.0)
	{
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

double AnalyticalFormulas::Black_Scholes_Put(double S0, double K, double T, double r, double sigma)
{

	//just using put call parity

	return K * std::exp(-r * T) - S0 + Black_Scholes_Call(S0, K, T, r, sigma);

}
