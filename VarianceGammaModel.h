/*
 *
 * This model is the Variance Gamma model for dynamics of the underlying asset.
 * The CGM representation is used for the input but are converted back for the implementation.
 * The characteristic function is known for this model in closed form.
 * 
 *
 */


#pragma once
#include "ModelBase.h"
#include "RandomBase.h"

#ifndef VARIANCEGAMMAMODEL_H
#define VARIANCEGAMMAMODEL_H


class VarianceGammaModel : public ModelBase

{
public:
	
	VarianceGammaModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double s0_{};
	double r_{};

	double C_{};
	double G_{};
	double M_{};

	double nu_{};
	double theta_{};
	double sigma_{};

	double mu_{};
	double omega_{};

	double N_{};

	double T_{};
	double dt_{};

	std::unique_ptr<BrownianMotionPathBase> path_{};
	boost::gamma_distribution<> gamma_distr_;
	std::unique_ptr<RandomBase> generator_{};
};
#endif
