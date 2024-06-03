#pragma once
#include "GreekBase.h"

#ifndef PATHWISEGREEKS_H
#define PATHWISEGREEKS_H

#include "PseudoFactory.h"
#include "ModelBase.h"

class PathwiseGreeks : public GreekBase
{
public:

	explicit PathwiseGreeks(const PseudoFactory& factory);
	~PathwiseGreeks() override = default;
	std::map<std::string, double> ComputeGreeks(const Eigen::MatrixXd& prices, const ModelBase& model) const override;


private:

	double ComputeDelta(const Eigen::MatrixXd& prices, const ModelBase& model) const override;
	double ComputeVega(const Eigen::MatrixXd& prices, const ModelBase& model) const override;
	double ComputeGamma(const Eigen::MatrixXd& prices, const ModelBase& model) const override;

	double S0_{};
	double X_{};
	double T_{};
	double r_{};
	double sigma_{};


};

#endif