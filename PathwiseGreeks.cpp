#include "PathwiseGreeks.h"

PathwiseGreeks::PathwiseGreeks(const PseudoFactory& factory) : S0_(factory.GetS0()), X_(factory.GetStrike()),
                                                               T_(factory.GetExpiry()),
                                                               r_(factory.GetRiskFreeRate()), sigma_(factory.GetVolatility())

{
}

std::map<std::string, double> PathwiseGreeks::ComputeGreeks(const Eigen::MatrixXd& prices, const ModelBase& model) const
{
	std::map<std::string, double> Greeks;

	std::cout << "Computing greeks:" << std::endl;

	Greeks["Delta"] = ComputeDelta(prices, model);
	Greeks["Vega"] = ComputeVega(prices, model);
	Greeks["Gamma"] = ComputeGamma(prices, model);

	return Greeks;
}

double PathwiseGreeks::ComputeDelta(const Eigen::MatrixXd& prices, const ModelBase& model) const
{

	std::cout << "Delta:" << std::endl;

	const Eigen::VectorXd ExpiryPrice = prices.rightCols(1);

	Eigen::VectorXd extracted(ExpiryPrice.size());

	extracted.setZero();

	for (int i = 0; i < ExpiryPrice.size(); ++i)
	{
		if (ExpiryPrice(i) > X_)
		{
			extracted(i) = ExpiryPrice(i);
		}
	}

	extracted /= S0_;

	return extracted.mean();
}

double PathwiseGreeks::ComputeVega(const Eigen::MatrixXd& prices, const ModelBase& model) const
{
	const Eigen::VectorXd ExpiryPrice = prices.rightCols(1);

	Eigen::VectorXd extracted(ExpiryPrice.size());

	extracted.setZero();

	for (int i = 0; i < ExpiryPrice.size(); ++i)
	{
		if (ExpiryPrice(i) > X_)
		{
			extracted(i) = ExpiryPrice(i) * (std::log(ExpiryPrice(i) / S0_) - (r_ + sigma_ * sigma_ / 2.0) * T_);
		}
	}

	double result = extracted.mean() / sigma_;
	return result;
}

double PathwiseGreeks::ComputeGamma(const Eigen::MatrixXd& prices, const ModelBase& model) const
{
	//this is LRPW!

	const Eigen::VectorXd ExpiryPrice = prices.rightCols(1);

	Eigen::VectorXd extracted(ExpiryPrice.size());

	extracted.setZero();

	for (int i = 0; i < ExpiryPrice.size(); ++i)
	{
		if (ExpiryPrice(i) > X_)
		{
			double temp1 = (std::log(ExpiryPrice(i) / S0_) - (r_ - 0.5 * sigma_ * sigma_) * T_) / (sigma_ *
				std::sqrt(T_));

			double temp2 = (ExpiryPrice(i) / (S0_ * S0_)) * ((temp1 / (sigma_ * std::sqrt(T_))) - 1);

			extracted(i) = temp2;
		}
	}

	double result = extracted.mean();

	return result;
}
