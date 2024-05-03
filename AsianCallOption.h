#pragma once
#include <Eigen/Dense>
#include "OptionBase.h"

#ifndef ASIANCALLOPTION_H
#define ASIANCALLOPTION_H

class PseudoFactory;
class ModelBase;

class AsianCallOption : public OptionBase
{
public:

	AsianCallOption(PseudoFactory& factory);

	double ComputePayoff(double final_price) const override;
	Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;
	std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& stock_prices,const ModelBase& model) const override;

private:

	double strike_{};
	double expiry_{};

};
#endif // ASIANCALLOPTION_H
