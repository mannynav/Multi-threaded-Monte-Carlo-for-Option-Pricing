
/*
 * Stochastic Alpha Beta Rho (SABR) Model
 *
 * Models the dynamics of the forward price and its volatility as:
 *
 *   dF_t = alpha_t * F_t^beta * dW_t^1
 *   d(alpha_t) = nu * alpha_t * dW_t^2
 *   d<W^1, W^2>_t = rho * dt
 *
 * A market standard model across interest rate, FX, and equity asset
 * classes, capable of capturing implied volatility smiles and skews.
 * The CEV exponent beta controls the backbone of the volatility smile:
 *   beta = 1  - lognormal backbone (Black-Scholes like)
 *   beta = 0  - normal backbone
 *   beta = 0.5 - CIR-like backbone
 *
 * Discretization:
 *   The asset price and volatility are evolved using the predictor-corrector
 *   scheme, which improves accuracy over plain Euler-Maruyama by averaging
 *   the drift and diffusion coefficients at the current and predicted step.
 *
 * Validation:
 *   Monte Carlo prices for European options have been tested against the
 *   analytical approximation for implied volatility. See Hagan et al. (2002).
 *
 * Closed-form solutions for plain vanilla European options are available
 * via the Hagan et al. implied volatility approximation, which is then
 * substituted into the Black-76 formula. See Hagan et al. (2002).
 *
 * Parameters:
 *   S0      - Initial spot price
 *   r       - Continuously compounded risk-free rate
 *   alpha   - Initial stochastic volatility level
 *   beta    - CEV exponent; controls the volatility backbone
 *   rho     - Correlation between forward price and volatility (W^1, W^2)
 *   nu      - Volatility of volatility
 *   T       - Time to expiry in years
 *   N       - Number of time steps
 *   dt      - Time step size (T / N)
 *   sqrtdt  - Precomputed square root of dt
 */

#pragma once
#include "ModelBase.h"

#ifndef SABRMODEL_H
#define SABRMODEL_H

class SABRModel : public ModelBase
{
public:
	SABRModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths,unsigned seed) const override;
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

	mutable std::vector<double> variates1{};
	mutable std::vector<double> variates2{};
	mutable std::vector<double> sigmaVec_{};

	std::unique_ptr<SamplingMethod> path_{};
	std::unique_ptr<RandomBase> generator_{};
};
#endif
