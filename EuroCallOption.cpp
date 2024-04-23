#include "EuroCallOption.h"
#include "PseudoFactory.h"


EuroCallOption::EuroCallOption(double strike, double expiry) : strike_(strike), expiry_(expiry)
{}

EuroCallOption::EuroCallOption(const PseudoFactory& factory) : strike_(factory.GetX()), expiry_(factory.GetT())
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
