#pragma once

#include "OptionBase.h"
#include "Eigen/Dense"
#include <map>

#ifndef DOUBLEBARRIERKNOCKINCALL_H
#define DOUBLEBARRIERKNOCKINCALL_H

class PseudoFactory;
class GreekBase;

class DoubleBarrierKnockInCall : public OptionBase
{
public:

	DoubleBarrierKnockInCall(double strike, double lowerB, double upperB, double expiry);
	DoubleBarrierKnockInCall(PseudoFactory& factory);
	~DoubleBarrierKnockInCall() = default;

	double ComputePayoff(double final_price) const override;
	Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;
	std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& stock_prices, const ModelBase& model) const override;

private:

	double strike_{};
	double lower_barrier_{};
	double upper_barrier_{};
	double expiry_{};

};







#endif 

