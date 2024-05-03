#pragma once

#include "OptionBase.h"
#include <Eigen/Dense>
#include <map>

#include "GreekDelta.h"
#include "GreekGamma.h"
#include "GreekVega.h"

#ifndef EUROCALLOPTION_H
#define EUROCALLOPTION_H

class PseudoFactory;
class GreekBase;

class EuroCallOption : public OptionBase
{
public:

	EuroCallOption(PseudoFactory& factory);

	double ComputePayoff(double final_price) const override;
	Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;
	std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& stock_prices,const ModelBase& model) const override;

private:

	double strike_{};
	double expiry_{};

	GreekBase* Greeks;
};
#endif // EUROCALLOPTION_H
