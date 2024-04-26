#include "EuroCallOption.h"
#include "PseudoFactory.h"

EuroCallOption::EuroCallOption(const PseudoFactory& factory) : strike_(factory.GetX()), expiry_(factory.GetT()), delta(factory), vega(factory), gamma(factory)
{}

double EuroCallOption::ComputePayoff(double final_price) const
{
	return std::max(final_price - strike_, 0.0);
}

Eigen::VectorXd EuroCallOption::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{
	const Eigen::VectorXd ExpiryPrice = stock_prices.rightCols(1);

	Eigen::VectorXd vectorized_version_of_payoffs = ExpiryPrice.unaryExpr([&](double final_price)
	{
		return ComputePayoff(final_price);
	});

	return vectorized_version_of_payoffs;
}

std::map<std::string, double> EuroCallOption::ComputeGreeks(Eigen::MatrixXd& stock_prices) const
{

	std::map<std::string, double> Greeks;

	Greeks["Delta"] = delta.ComputeDeltaPathwise(stock_prices);
	Greeks["Vega"] = vega.ComputeVegaPathwise(stock_prices);
	Greeks["Gamma"] = gamma.ComputeGammaLRPW(stock_prices);

	return Greeks;


}


