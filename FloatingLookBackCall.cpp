
#include "FloatingLookBackCall.h"

FloatingLookBackCallOption::FloatingLookBackCallOption(PseudoFactory& factory) :
	strike_(factory.GetX()),
	expiry_(factory.GetT()),
	Greeks(factory.CreateGreek())
{
}

FloatingLookBackCallOption::~FloatingLookBackCallOption() {

	delete Greeks;
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
	return std::map<std::string, double>();
}
