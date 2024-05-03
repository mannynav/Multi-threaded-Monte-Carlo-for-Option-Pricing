#include "EuroCallOption.h"

#include "GreekBase.h"
#include "PseudoFactory.h"

EuroCallOption::EuroCallOption(PseudoFactory& factory) : strike_(factory.GetX()), expiry_(factory.GetT()),
Greeks(factory.CreateGreek())
{
}

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

std::map<std::string, double> EuroCallOption::ComputeGreeks(Eigen::MatrixXd& stock_prices,const ModelBase& model) const
{
	std::cout << "Inside option greeks" << std::endl;

	std::map<std::string, double> greek_map = Greeks->ComputeGreeks(stock_prices, model);

	return greek_map;
}


