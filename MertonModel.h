#pragma once

#include "ModelBase.h"
#include "RandomBase.h"

#ifndef MERTONMODEL_H
#define MERTONMODEL_H

class MertonModel : public ModelBase
{
public:
	MertonModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double S0_{};
	double r_{};
	double sigma_{};

	double uJ_{};
	double sigmaJ{};
	double lambdaJ_{};
	double nu_{};

	double M_{};
	double N_{};
	double T_{};

	double dt_{};
	double sqrtdt_{};

	std::unique_ptr<BrownianMotionPathBase> path_{};
	boost::poisson_distribution<> poisson_;
	std::unique_ptr<RandomBase> generator_{};

};

#endif
