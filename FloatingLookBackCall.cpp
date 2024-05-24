
#include "FloatingLookBackCall.h"

FloatingLookBackCallOption::FloatingLookBackCallOption(PseudoFactory& factory) :
	strike_(factory.GetStrike()),
	expiry_(factory.GetExpiry())
{
}

double FloatingLookBackCallOption::ComputePayoff(double final_price) const
{
	return std::max(final_price - strike_, 0.0);
}

Eigen::VectorXd FloatingLookBackCallOption::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{
	Eigen::VectorXd expiryPrices = stock_prices.rightCols(1);

	Eigen::VectorXd minPrices = stock_prices.rowwise().minCoeff();

	Eigen::VectorXd result = (expiryPrices - minPrices);

	return result;
}

std::map<std::string, double> FloatingLookBackCallOption::ComputeGreeks(Eigen::MatrixXd& stock_prices, const ModelBase& model) const
{
	std::map<std::string, double> greek_map{};
	return greek_map;
}
