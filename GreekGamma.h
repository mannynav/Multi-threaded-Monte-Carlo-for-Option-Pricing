

#pragma once
#include "PseudoFactory.h"
#include "rv.h"
#include "Eigen/Dense"

class PseudoFactory;


class GreekGamma
{
public:

	explicit GreekGamma(const PseudoFactory& factory) : S0_(factory.GetS0()), strike_(factory.GetStrike()), sigma_(factory.GetVolatility()), r_(factory.GetRiskFreeRate()), T_(factory.GetExpiry()) {}

	double ComputeGammaLRPW(Eigen::MatrixXd& stock_prices) const
	{
		const Eigen::VectorXd ExpiryPrice = stock_prices.rightCols(1);

		Eigen::VectorXd extracted(ExpiryPrice.size());

		extracted.setZero();


		for (int i = 0; i < ExpiryPrice.size(); ++i) {
			if (ExpiryPrice(i) > strike_) {

				double temp1 = (std::log(ExpiryPrice(i) / S0_) - (r_ - 0.5 * sigma_ * sigma_) * T_) / (sigma_ * std::sqrt(T_));

				double temp2 = (ExpiryPrice(i) / (S0_ * S0_)) * ((temp1 / (sigma_ * std::sqrt(T_))) - 1);

				extracted(i) = temp2;

			}
		}

		double result = extracted.mean();

		return result;
	}


private:

	double S0_{};
	double strike_{};
	double sigma_{};
	double r_{};
	double T_{};

};