#pragma once

#include "ModelBase.h"
#include "PseudoFactory.h"
#include "RandomBase.h"

#ifndef GBMMODEL_H
#define GBMMODEL_H

class PseudoFactory;
class BrownianMotionPathBase;

class GBMModel : public ModelBase

{
public:
	GBMModel(PseudoFactory& factory);
	~GBMModel();
	Eigen::MatrixXd simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	std::vector<double> get_likelihood_ratio() const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double S0_{};
	double r_{};
	double sigma_{};

	double dt_{};
	double drift_{};

	double M_{};
	double N_{};
	double T_{};

	BrownianMotionPathBase* path_;
	std::unique_ptr<RandomBase> generator_{};
};
#endif // GBMMODEL_H
