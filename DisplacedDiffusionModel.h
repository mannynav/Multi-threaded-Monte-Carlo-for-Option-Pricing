
#pragma once

#include "ModelBase.h"
#include "PseudoFactory.h"
#include "RandomBase.h"

#ifndef DISPLACEDDIFFUSIONMODEL_H
#define DISPLACEDDIFFUSIONMODEL_H

class PseudoFactory;
class BrownianMotionPathBase;

class DisplacedDiffusionModel : public ModelBase

{
public:
	DisplacedDiffusionModel(PseudoFactory& factory);
	~DisplacedDiffusionModel();
	Eigen::MatrixXd simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double S0_{};
	double r_{};

	double a_{};			//Displacement parameter
	double sigmaDD_{};

	double dt_{};
	double drift_{};

	double M_{};
	double N_{};
	double T_{};

	//BrownianMotionPathBase* path_;
	std::unique_ptr<BrownianMotionPathBase> path_;
	std::unique_ptr<RandomBase> generator_{};
};
#endif 
