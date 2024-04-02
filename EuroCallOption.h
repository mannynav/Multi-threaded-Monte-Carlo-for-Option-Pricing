
#include <Eigen/Dense>
#include "OptionBase.h"

#ifndef EUROCALLOPTION_H
#define EUROCALLOPTION_H

class PseudoFactory;

class EuroCallOption : public OptionBase
{
public:

	explicit EuroCallOption();
	EuroCallOption(double strike, double expiry);
	EuroCallOption(const PseudoFactory& factory);

	double ComputePayoff(double final_price) const override;

	Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;

private:

	double strike_{};
	double expiry_{};

};
#endif // EUROCALLOPTION_H
