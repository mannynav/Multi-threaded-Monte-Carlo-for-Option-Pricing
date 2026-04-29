
/*
 * Merton Jump Diffusion Model
 *
 * Extends GBM by superimposing a compound Poisson jump process:
 *
 *   dS_t = (r - lambda * kbar) * S_t * dt + sigma * S_t * dW_t + S_{t-} * (e^J - 1) * dN_t
 *
 * where:
 *   N_t  ~ Poisson(lambda)     is the jump arrival process
 *   J    ~ N(uJ, sigmaJ^2)    is the log-jump size distribution
 *   kbar = exp(uJ + sigmaJ^2 / 2) - 1  is the mean jump size (martingale correction)
 *
 * The jump component allows the model to generate steep implied volatility
 * skew or smile structures, particularly pronounced for short-dated options.
 * Commonly used for short-dated FX options where jumps are significant.
 *
 * Discretization:
 *   At each time step the number of jumps is drawn from a Poisson
 *   distribution. The aggregate jump contribution is then applied to
 *   the GBM step. The continuous diffusion component is discretized
 *   using the exact GBM solution.
 *
 * Closed-form solutions for plain vanilla European options are available
 * as an infinite weighted sum of Black-Scholes prices:
 *
 *   C = sum_{n=0}^{inf} [ exp(-lambda'T) * (lambda'T)^n / n! * BS(sigma_n, r_n) ]
 *
 * where lambda' = lambda * exp(uJ + sigmaJ^2 / 2), sigma_n and r_n are
 * jump-adjusted volatility and rate for n jumps. See Merton (1976).
 *
 * Parameters:
 *   S0       - Initial spot price
 *   r        - Continuously compounded risk-free rate
 *   sigma    - Diffusion volatility of the continuous component
 *   uJ       - Mean of the log-jump size distribution
 *   sigmaJ   - Standard deviation of the log-jump size distribution
 *   lambdaJ  - Jump intensity; expected number of jumps per year
 *   nu       - Precomputed martingale correction (kbar)
 *   T        - Time to expiry in years
 *   N        - Number of time steps
 *   dt       - Time step size (T / N)
 *   sqrtdt   - Precomputed square root of dt
 *   M        - Precomputed drift term per time step
 */


#pragma once
#include "ModelBase.h"
#include "RandomBase.h"

#ifndef MERTONMODEL_H
#define MERTONMODEL_H

class MertonModel : public ModelBase
{
public:
	MertonModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const override;
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

	std::unique_ptr<SamplingMethod> path_{};
	boost::poisson_distribution<> poisson_;
	std::unique_ptr<RandomBase> generator_{};

};

#endif
