


#include "AnalyticalFormulas.h"

#include <random>
#include <stdexcept>
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <iostream>
#include <numbers>
#include <cmath>

std::pair<double, double> AnalyticalFormulas::calculate_d1_d2(double S0, double K, double T, double r, double d, double sigma)
{

	double d1 = (std::log(S0 / K) + ((r-d) + (sigma * sigma) / 2) * T) / (sigma * std::sqrt(T));
	double d2 = d1 - sigma * sqrt(T);

	std::pair<double, double> pair{ d1,d2 };
	return pair;

}


double AnalyticalFormulas::Black_Scholes_Call(double S0, double K, double T, double r, double d, double sigma)
{
	if (S0 <= 0.0 || K <= 0.0 || T <= 0.0)
	{
		throw std::invalid_argument("Invalid input parameters (spot price, strike price, or time to maturity must be positive).");
	}
	std::pair<double, double> d1_d2 = AnalyticalFormulas::calculate_d1_d2(S0, K, T, r, d, sigma);
	double d1 = d1_d2.first;
	double d2 = d1_d2.second;

	boost::math::normal_distribution<>  norm_dist(0.0, 1.0); //
	double N_d1 = cdf(norm_dist, d1);

	double N_d2 = cdf(norm_dist, d2);

	return S0 * N_d1 - K * exp(-r * T) * N_d2;
}

double AnalyticalFormulas::Black_Scholes_Put(double S0, double K, double T, double r, double d, double sigma)
{
	//just using put call parity
	return K * std::exp(-r * T) - S0 + Black_Scholes_Call(S0, K, T, r,d, sigma);

}

double AnalyticalFormulas::Displaced_Diffusion_Call(double S0, double a, double K, double T, double r, double sigma)
{
	double K_new = K + a;
	double sigmaDD = (S0 / (S0 + a))*sigma;

	double d1 = (std::log((S0 + a) / K_new) + 0.5*sigmaDD * sigmaDD * T) / (sigmaDD * std::sqrt(T));
	double d2 = d1 - sigmaDD * sigmaDD * T;

	boost::math::normal_distribution<>  norm_dist(0.0, 1.0); //
	double N_d1 = cdf(norm_dist, d1);
	double N_d2 = cdf(norm_dist, d2);

	return std::exp(-r * T) * ((S0 + a) * N_d1 - K_new * N_d2);

}

double AnalyticalFormulas::Displaced_Diffusion_Put(double S0, double a, double K, double T, double r, double sigma)
{
	double K_new = K + a;
	double sigmaDD = (S0 / (S0 + a)) * sigma;

	double d1 = (std::log((S0 + a) / K_new) + 0.5 * sigmaDD * sigmaDD * T) / (sigmaDD * std::sqrt(T));
	double d2 = d1 - sigmaDD * sigmaDD * T;

	boost::math::normal_distribution<>  norm_dist(0.0, 1.0); //
	double N_d1 = cdf(norm_dist, -d1);
	double N_d2 = cdf(norm_dist, -d2);

	return std::exp(-r * T) * (K_new * N_d2 - (S0 + a) * N_d1);
}

double AnalyticalFormulas::delta(double S0, double K, double r, double sigma, double t, bool isCall)
{
	boost::math::normal_distribution<>  norm_dist(0.0, 1.0); //
	double d1 = (std::log(S0 / K) + (r + sigma * sigma / 2.0) * t) / (sigma * std::sqrt(t));
	return cdf(norm_dist, d1) * (isCall ? 1 : -1);
	
}

double AnalyticalFormulas::gamma(double S0, double K, double r, double sigma, double t)
{	double d1 = (log(S0 / K) + (r + sigma * sigma / 2.0) * t) / (sigma * sqrt(t));
	return (exp(-d1 * d1 / 2.0) / (((sqrt(t) * S0 * sigma))* std::sqrt(2*std::numbers::pi)));
}

double AnalyticalFormulas::vega(double S0, double K, double r, double sigma, double t)
{
	double d1 = (log(S0 / K) + (r + sigma * sigma / 2.0) * t) / (sigma * sqrt(t));
	return S0 * exp(-d1 * d1 / 2.0) * sqrt(t) / std::sqrt(2*std::numbers::pi);
}

double AnalyticalFormulas::theta(double S0, double K, double r, double sigma, double t, bool isCall) {

	boost::math::normal_distribution<>  norm_dist(0.0, 1.0);
	double d1 = (log(S0 / K) + (r + sigma * sigma / 2.0) * t) / (sigma * sqrt(t));
	double d2 = d1 - sigma * sqrt(t);
	if (isCall) {
		return -S0 * sigma * exp(-d1 * d1 / 2.0) * cdf(norm_dist,d1) / (2.0 * sqrt(t)) - r * K * exp(-r * t) * cdf(norm_dist, d2);
	}
	else {
		return -S0 * sigma * exp(-d1 * d1 / 2.0) * cdf(norm_dist, -d1) / (2.0 * sqrt(t)) + r * K * exp(-r * t) * cdf(norm_dist, -d2);
	}
}

double AnalyticalFormulas::ImpliedVolatilitySABR(double F, double strike, double T, double alpha, double beta, double nu, double rho)
{
	if (F == strike) {
		double V_atm = (alpha / pow(F, 1 - beta)) * (
			1 + (((1 - beta) * (1 - beta) * alpha * alpha) / (24.0 * pow(F, 2 - 2 * beta)) +
				(rho * beta * nu * alpha) / (4.0 * pow(F, 1 - beta)) +
				((2 - 3 * rho * rho) * nu * nu) / 24.0) * T);
		return V_atm;
	}

	double FK_beta = pow(F * strike, (1 - beta) / 2.0);
	double log_FK = std::log(F / strike);
	double z = nu / alpha * FK_beta * log_FK;
	double x_z = std::log((std::sqrt(1 - 2 * rho * z + z * z) + z - rho) / (1 - rho));

	double V = (alpha / FK_beta * (z / x_z) * (
		1 + (((1 - beta) * (1 - beta) * alpha * alpha) / (24.0 * FK_beta * FK_beta) +
			(rho * beta * nu * alpha) / (4.0 * FK_beta) +
			((2 - 3 * rho * rho) * nu * nu) / 24.0) * T));

	return V;
}
