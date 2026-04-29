
/*
 * Heston Stochastic Volatility Model
 *
 * Jointly models the asset price and its variance:
 *
 *   dS_t = r * S_t * dt + sqrt(V_t) * S_t * dW_t^1
 *   dV_t = kappa * (theta - V_t) * dt + xi * sqrt(V_t) * dW_t^2
 *   d<W^1, W^2>_t = rho * dt
 *
 * The model can capture both skew and smile shapes in the implied
 * volatility surface depending on the choice of parameters.
 *
 * Feller Condition:
 *   2 * kappa * theta > xi^2 ensures the variance process remains
 *   strictly positive. If violated, V_t can hit zero.
 *
 * Discretization:
 *   The variance process V_t is discretized using the Almost Exact scheme,
 *   sampling directly from a non-central chi-squared distribution at each
 *   time step. This avoids the bias and instability of Euler discretization
 *   near zero variance.
 *
 *   The conditional distribution of V_{t+dt} | V_t is:
 *
 *     V_{t+dt} = c * chi^2(delta, kappaBar)
 *
 *   where:
 *     c        = xi^2 * (1 - exp(-kappa*dt)) / (4 * kappa)
 *     delta    = 4 * kappa * theta / xi^2       (degrees of freedom)
 *     kappaBar = 4 * kappa * V_t * exp(-kappa*dt)
 *                / (xi^2 * (1 - exp(-kappa*dt))) (non-centrality parameter)
 *
 *   The log-spot is advanced using a moment-matched scheme with
 *   precomputed constants k0, k1, k2.
 *
 * Closed-form solutions for plain vanilla European options are available
 * via characteristic function inversion. See Heston (1993).
 *
 * Parameters:
 *   S0             - Initial spot price
 *   r              - Continuously compounded risk-free rate
 *   V0             - Initial instantaneous variance
 *   meanreversion  - Speed of variance mean reversion (kappa)
 *   ltmean         - Long-term mean of the variance process (theta)
 *   volvol         - Volatility of the variance process (xi)
 *   corr           - Correlation between spot and variance (rho)
 *   T              - Time to expiry in years
 *   N              - Number of time steps
 *   dt             - Time step size (T / N)
 *   k0, k1, k2     - Precomputed constants for the log-spot update
 *   expression     - Precomputed exp(-kappa * dt)
 *   delta          - Precomputed degrees of freedom for chi-squared sampling
 *   c              - Precomputed scaling constant for chi-squared sampling
 *   PsiC           - Threshold for switching discretization branches (unused
 *                    in the Almost Exact scheme; retained for compatibility)
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
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const override;
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
	double delta_;
	double c_;

	double N_{};
	double T_{};
	double dt_{};

	std::unique_ptr<SamplingMethod> path_{};
	std::unique_ptr<RandomBase> generator_{};
	void generate_CIR_path(std::vector<double>& vec, boost::mt19937 & rng) const;

};
#endif