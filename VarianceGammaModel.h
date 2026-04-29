
/*
 * Variance Gamma (VG) Model
 *
 * Models the log-price as a Brownian motion with drift time-changed by a
 * Gamma process:
 *
 *   X_t^VG = theta * G_t + sigma * W_{G_t}
 *   S_t = S_0 * exp((r + omega) * t + X_t^VG)
 *
 * where G_t ~ Gamma(t/nu, nu) is the Gamma subordinator and omega is the
 * martingale correction term:
 *
 *   omega = (1/nu) * ln(1 - theta*nu - sigma^2*nu/2)
 *
 * The model produces skew and excess kurtosis in the return distribution,
 * capturing the fat tails and asymmetry observed in equity markets.
 * Setting nu -> 0 recovers GBM dynamics.
 *
 * Parameterization:
 *   The CGM (C, G, M) parameterization is used for input, where:
 *     C = 1/nu     (controls kurtosis)
 *     G = 1/(-theta*nu + sqrt(theta^2*nu^2 + sigma^2*nu)) (controls negative tail)
 *     M = 1/(theta*nu + sqrt(theta^2*nu^2 + sigma^2*nu))  (controls positive tail)
 *
 *   These are converted internally to the (sigma, nu, theta) representation
 *   for simulation.
 *
 * Discretization:
 *   At each time step, an increment of the Gamma process is drawn directly
 *   from a Gamma distribution with shape dt/nu and scale nu. The log-spot
 *   is then advanced using the sampled Gamma increment and a correlated
 *   normal variate.
 *
 * Closed-form solutions for plain vanilla European options are available
 * via the characteristic function and the Carr-Madan FFT method.
 * See Madan, Carr & Chang (1998).
 *
 * Parameters:
 *   s0      - Initial spot price
 *   r       - Continuously compounded risk-free rate
 *   C, G, M - CGM parameterization inputs
 *   nu      - Variance rate of the Gamma time change; controls kurtosis
 *   theta   - Drift of the Brownian component; controls skew
 *   sigma   - Volatility of the Brownian component
 *   mu      - Precomputed drift correction for the log-spot update
 *   omega   - Precomputed martingale correction term
 *   T       - Time to expiry in years
 *   N       - Number of time steps
 *   dt      - Time step size (T / N)
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
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const override;
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

	std::unique_ptr<SamplingMethod> path_{};
	boost::gamma_distribution<> gamma_distr_;
	std::unique_ptr<RandomBase> generator_{};
};
#endif
