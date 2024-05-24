#pragma once


#include "OptionBase.h"
#include <Eigen/Dense>
#include <map>


#ifndef EUROUPINCALLOPTION_H
#define EUROUPINCALLOPTION_H

class PseudoFactory;
class GreekBase;

class EuroUpInCallOption : public OptionBase
{
public:

	EuroUpInCallOption(double strike, double expiry, double barrier) : strike_(strike), expiry_(expiry), barrier_(barrier) {};
	EuroUpInCallOption(PseudoFactory& factory);
	~EuroUpInCallOption() = default;

	double ComputePayoff(double final_price) const override;
	Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;
	std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& stock_prices, const ModelBase& model) const override;


private:

	double expiry_{};
	double strike_{};
	double barrier_{};

};


#endif

