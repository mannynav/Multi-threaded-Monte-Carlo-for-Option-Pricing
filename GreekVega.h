

#pragma once
#include "PseudoFactory.h"

class PseudoFactory;

class GreekVega
{

public:

	explicit GreekVega(const PseudoFactory& factory) : S0_(factory.GetS0()), strike_(factory.GetX()), sigma_(factory.Getsig()), r_(factory.Getr()), T_(factory.GetT()) {}

	double ComputeVegaPathwise(Eigen::MatrixXd& stock_prices) const
	{
		const Eigen::VectorXd ExpiryPrice = stock_prices.rightCols(1);

		Eigen::VectorXd extracted(ExpiryPrice.size());

		extracted.setZero();


		for (int i = 0; i < ExpiryPrice.size(); ++i) {
			if (ExpiryPrice(i) > strike_) {
				extracted(i) = ExpiryPrice(i) * (std::log(ExpiryPrice(i) / S0_) - (r_ + sigma_ * sigma_ / 2.0) * T_);
			}
		}

		double result = extracted.mean() / sigma_;
		return result;
	}

private:

	double S0_{};
	double strike_{};
	double sigma_{};
	double r_{};
	double T_{};
};
