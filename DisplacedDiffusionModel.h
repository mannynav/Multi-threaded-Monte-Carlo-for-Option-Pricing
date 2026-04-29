

/*
 * Displaced Diffusion Model
 *
 * Models the dynamics of the underlying asset as:
 *
 *   dS_t = r * S_t * dt + sigmaDD * (S_t + a) * dW_t
 *
 * The displacement parameter a shifts the lognormal distribution, allowing
 * the model to produce skewed implied volatility structures. Setting a = 0
 * recovers standard GBM / Black-Scholes dynamics.
 *
 * Parameters:
 *   S0      - Initial spot price
 *   r       - Continuously compounded risk-free rate
 *   a       - Displacement parameter; controls the degree of skew
 *   sigmaDD - Displaced diffusion volatility
 *   T       - Time to expiry in years
 *   N       - Number of time steps
 *   dt      - Time step size (T / N)
 *   sqrtdt  - Precomputed square root of dt
 *
 * Closed-form solutions for plain vanilla European options are available.
 * See Rebonato (2002).
 */


#pragma once
#include "ModelBase.h"
#include "RandomBase.h"


#ifndef DISPLACEDDIFFUSIONMODEL_H
#define DISPLACEDDIFFUSIONMODEL_H

class DisplacedDiffusionModel : public ModelBase

{
public:
	DisplacedDiffusionModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths,unsigned seed) const override;
	double Get_MT() const override
	{
		return std::exp(r_ * T_);
	}

private:
	double S0_{};
	double r_{};

	double a_{};
	double sigmaDD_{};

	double drift_{};

	double M_{};
	double N_{};

	double T_{};
	double dt_{};
	double sqrtdt_{};

	std::unique_ptr<SamplingMethod> path_;
	std::unique_ptr<RandomBase> generator_{};
};
#endif 
