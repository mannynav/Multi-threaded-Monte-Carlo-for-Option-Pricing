
/*
 * Geometric Brownian Motion Model (Black-Scholes)
 *
 * Models the dynamics of the underlying asset as:
 *
 *   dS_t = r * S_t * dt + sigma * S_t * dW_t
 *
 * The discretization scheme is exact — the closed-form solution to the GBM
 * SDE is evaluated at each time step:
 *
 *   S_{t+dt} = S_t * exp((r - sigma^2 / 2) * dt + sigma * sqrt(dt) * Z)
 *
 * where Z ~ N(0,1). This eliminates discretization error entirely.
 *
 * Parameters:
 *   S0      - Initial spot price
 *   r       - Continuously compounded risk-free rate
 *   sigma   - Constant instantaneous volatility
 *   T       - Time to expiry in years
 *   N       - Number of time steps
 *   dt      - Time step size (T / N)
 *   sqrtdt  - Precomputed square root of dt
 *   drift   - Precomputed drift term (r - sigma^2 / 2) * dt
 *   theta   - Precomputed diffusion term sigma * sqrt(dt)
 *
 * Closed-form solutions for plain vanilla European options are available.
 * See Black & Scholes (1973).
 */
 
#pragma once
#include "ModelBase.h"

#ifndef GBMMODEL_H
#define GBMMODEL_H

class GBMModel : public ModelBase 
{
public:
	GBMModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const override;
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
	double theta_{};

	std::unique_ptr<SamplingMethod> path_{};
	std::unique_ptr<RandomBase> generator_{};
};
#endif // GBMMODEL_H
