
#include "PseudoFactory.h"
#include "AsianCallOption.h"


AsianCallOption::AsianCallOption(double strike, double expiry) : strike_(strike), expiry_(expiry)
{}

AsianCallOption::AsianCallOption(const PseudoFactory& factory) : strike_(factory.GetX()), expiry_(factory.GetT())
{}

double AsianCallOption::ComputePayoff(double final_price) const
{
	return std::max(final_price - strike_, 0.0);
}

Eigen::VectorXd AsianCallOption::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{
	//const Eigen::VectorXd SumAtExpiry = stock_prices.rightCols(1);
	const Eigen::VectorXd SumAtExpiry = stock_prices.rowwise().mean();

	Eigen::VectorXd vectorized_version_of_payoffs = SumAtExpiry.unaryExpr([&](double final_price)
		{
			return ComputePayoff(final_price);
		});

	return vectorized_version_of_payoffs;
}