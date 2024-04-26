#pragma once
#include <utility>


namespace AnalyticalFormulas
{
	//extend for dividends
	std::pair<double, double> calculate_d1_d2(double S0, double K, double T, double r, double sigma);
	double Black_Scholes_Call(double S0, double K, double T, double r, double sigma);
	double Black_Scholes_Put(double S0, double K, double T, double r, double sigma);

	//add greeks



}

namespace af = AnalyticalFormulas;