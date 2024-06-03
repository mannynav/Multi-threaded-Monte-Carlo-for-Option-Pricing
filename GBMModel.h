#pragma once

#include "ModelBase.h"

#ifndef GBMMODEL_H
#define GBMMODEL_H

class GBMModel : public ModelBase 
{
public:
	GBMModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double S0_{};
	double r_{};
	double sigma_{};

	double N_{};

	double T_{};
	double dt_{};
	double drift_{};
	double sqrtdt_{};

	std::unique_ptr<BrownianMotionPathBase> path_{};
	std::unique_ptr<RandomBase> generator_{};
};
#endif // GBMMODEL_H
