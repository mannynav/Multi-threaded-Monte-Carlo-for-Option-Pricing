#pragma once

#include "ModelBase.h"
#include "PseudoFactory.h"
#include "RandomBase.h"

#ifndef VARIANCEGAMMAMODEL_H
#define VARIANCEGAMMAMODEL_H

class PseudoFactory;
class BrownianMotionPathBase;

class VarianceGammaModel : public ModelBase

{
public:
	
	VarianceGammaModel(PseudoFactory& factory);
	~VarianceGammaModel() = default;
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	std::vector<double> get_likelihood_ratio() const override
	{
		std::vector<double> W;
		return W;
	}
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double s0_{};
	double r_{};

	double mu_Vg_{};
	double theta_{};
	double omega_{};
	double beta_{};
	double sigmaVg_{};

	double dt_{};
	double N_{};
	double T_{};

	BrownianMotionPathBase* path_{};
	std::unique_ptr<RandomBase> generator_{};
};
#endif // GBMMODEL_H
