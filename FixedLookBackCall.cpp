#include "FixedLookBackCall.h"

FixedLookBackCallOption::FixedLookBackCallOption(PseudoFactory& factory) : 
																		strike_(factory.GetStrike()),
																		expiry_(factory.GetExpiry())
																		{}

double FixedLookBackCallOption::ComputePayoff(double final_price) const
{
	return std::max(final_price - strike_, 0.0);
}

Eigen::VectorXd FixedLookBackCallOption::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{

	Eigen::VectorXd maxPrices = stock_prices.rowwise().maxCoeff();

	Eigen::VectorXd vectorized_version_of_payoffs = maxPrices.unaryExpr([&](double max_price) {
		return ComputePayoff(max_price);
		});

	return vectorized_version_of_payoffs;
}

std::map<std::string, double> FixedLookBackCallOption::ComputeGreeks(Eigen::MatrixXd& stock_prices, const ModelBase& model) const
{
	std::map<std::string, double> greek_map{};
	return greek_map;
}



