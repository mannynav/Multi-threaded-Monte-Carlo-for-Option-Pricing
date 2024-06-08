
/*
 *
 * This model is the Heston Stochastic Vol model.
 * The model can capture skew or smile based implied volatility.
 * Numerous discretization schemes available.
 * The scheme used here is the Almost Exact Scheme, sampling directly from a non-central chi-squared distribution.
 *
 */

#pragma once
#include "ModelBase.h"
#include "RandomBase.h"

#ifndef HESTONMODEL_H
#define HESTONMODEL_H

class HestonModel : public ModelBase

{
public:
	
	HestonModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double S0_{};
	double r_{};
	double sigma_{};

	double V_0_{};
	double corr_{};
	double volvol_{};
	double meanreversion_{};
	double ltmean_{};
	double PsiC_{};

	double k0_{};
	double k1_{};
	double k2_{};

	double expression_;
	double sqrt_expression_;
	double delta_;
	double c_;

	double N_{};
	double T_{};
	double dt_{};

	mutable std::vector<double> cir_path_;

	std::unique_ptr<RandomBase> generator_{};
	std::vector<double> generate_CIR_path(boost::mt19937 & rng) const;

};
#endif // HESTONMODEL_H