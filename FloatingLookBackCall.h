
#pragma once

#include "OptionBase.h"
#include "PseudoFactory.h"
#include <Eigen/Dense>
#include <map>


#ifndef FLOATINGLOOKBACKCALLOPTION_H
#define FLOATINGLOOKBACKCALLOPTION_H

class PseudoFactory;
class GreekBase;

class FloatingLookBackCallOption : public OptionBase
{
public:

	FloatingLookBackCallOption(double strike, double expiry) : strike_(strike), expiry_(expiry) {};
	FloatingLookBackCallOption(PseudoFactory& factory);
	~FloatingLookBackCallOption() = default;

	double ComputePayoff(double final_price) const override;
	Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;
	std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& stock_prices, const ModelBase& model) const override;

private:

	double strike_{};
	double expiry_{};
};
#endif // FIXEDLOOKBACKCALLOPTION_H
