#pragma once
#include <utility>


namespace AnalyticalFormulas
{
	//extend for dividends
	std::pair<double, double> calculate_d1_d2(double S0, double K, double T, double r, double sigma);
	double Black_Scholes_Call(double S0, double K, double T, double r, double sigma);
	double Black_Scholes_Put(double S0, double K, double T, double r, double sigma);

	double delta(double S0, double K, double r, double sigma, double t, bool isCall);
	double gamma(double S0, double K, double r, double sigma, double t);
	double vega(double S0, double K, double r, double sigma, double t);
	double theta(double S0, double K, double r, double sigma, double t, bool isCall);


	double ImpliedVolatilitySABR(double F, double strike, double T, double alpha, double beta, double nu, double rho);



}

namespace af = AnalyticalFormulas;