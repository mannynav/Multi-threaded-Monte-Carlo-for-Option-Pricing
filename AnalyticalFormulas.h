#pragma once
#include <utility>

/*
 *
 * This file will contain analytical formulas commonly used in mathematical finance,
 * It will include the formula for the SABR implied vol, which is the implied vol that can be put back into the Black-76 formula for European options.
 * To avoid implementing the Black-76 formula, we will use the BS formula and set "r" to be 0 and S equal to the futures price, which will give us the Black-76 formula.
 * 
 *
 */

namespace AnalyticalFormulas
{
	//extend for dividends
	std::pair<double, double> calculate_d1_d2(double S0, double K, double T, double r,double d, double sigma);
	double Black_Scholes_Call(double S0, double K, double T, double r, double d, double sigma);
	double Black_Scholes_Put(double S0, double K, double T, double r,double d, double sigma);

	double Displaced_Diffusion_Call(double S0, double a, double K, double T, double r, double sigma);
	double Displaced_Diffusion_Put(double S0, double a, double K, double T, double r, double sigma);

	double delta(double S0, double K, double r, double sigma, double t, bool isCall);
	double gamma(double S0, double K, double r, double sigma, double t);
	double vega(double S0, double K, double r, double sigma, double t);
	double theta(double S0, double K, double r, double sigma, double t, bool isCall);


	double ImpliedVolatilitySABR(double F, double strike, double T, double alpha, double beta, double nu, double rho);



}

namespace af = AnalyticalFormulas;