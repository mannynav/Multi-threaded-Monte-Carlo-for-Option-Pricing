
#pragma once
#include "ModelBase.h"

#ifndef SABRMODEL_H
#define SABRMODEL_H

class SABRModel : public ModelBase
{
public:
	SABRModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double S0_{};
	double r_{};

	double alpha_{};
	double beta_{};
	double rho_{};
	double nu_{};

	double M_{};
	double N_{};

	double T_{};
	double dt_{};
	double sqrtdt_{};

	mutable std::vector<double> sigmaVec_{};

	std::unique_ptr<BrownianMotionPathBase> path_{};
	std::unique_ptr<RandomBase> generator_{};
};
#endif // GBMMODEL_H
