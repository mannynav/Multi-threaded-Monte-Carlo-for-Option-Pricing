

#pragma once
#include "PseudoFactory.h"

class PseudoFactory;

class GreekDelta
{

public:

	explicit GreekDelta(const PseudoFactory& factory) : S0_(factory.GetS0()), strike_(factory.GetStrike()) {}

	double ComputeDeltaPathwise(Eigen::MatrixXd& stock_prices) const
	{

		const Eigen::VectorXd ExpiryPrice = stock_prices.rightCols(1);

		Eigen::VectorXd extracted(ExpiryPrice.size());

		extracted.setZero();

		for (int i = 0; i < ExpiryPrice.size(); ++i) {
			if (ExpiryPrice(i) > strike_) {
				extracted(i) = ExpiryPrice(i);
			}
		}

		extracted /= S0_;

		return extracted.mean();

	}

private:

	double S0_{};
	double strike_{};
};