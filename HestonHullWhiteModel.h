
/*
 * Heston Hull-White Model
 *
 * Jointly models stochastic volatility and stochastic interest rates:
 *
 *   dS_t = r_t * S_t * dt + sqrt(V_t) * S_t * dW_t^1
 *   dV_t = kappa * (theta - V_t) * dt + xi * sqrt(V_t) * dW_t^2
 *   dr_t = lambda * (theta_t - r_t) * dt + eta * dW_t^3
 *
 * where theta_t is calibrated to the initial yield curve via the
 * instantaneous forward rate f(0,t).
 *
 * Correlations:
 *   corrXV - Correlation between spot and variance (W^1, W^2)
 *   corrXR - Correlation between spot and short rate (W^1, W^3)
 *
 * Discretization:
 *   The variance process V_t is discretized using the Quadratic Exponential
 *   (QE) scheme (Andersen 2007), which avoids the instability of Euler
 *   discretization near zero variance. The short rate r_t is discretized
 *   exactly using the Hull-White analytical solution.
 *
 * Validation:
 *   European call prices match those obtained via the COS method.
 *   See Fang & Oosterlee (2008) and Grzelak & Oosterlee (2019).
 *
 * Note: Multi-threading is not yet implemented for this model.
 *
 * Heston Parameters:
 *   S0             - Initial spot price
 *   V0             - Initial instantaneous variance
 *   meanreversion  - Speed of variance mean reversion (kappa)
 *   ltmean         - Long-term mean of the variance process (theta)
 *   volvol         - Volatility of the variance process (xi)
 *   corrXV         - Correlation between spot and variance
 *   corrXR         - Correlation between spot and short rate
 *   PsiC           - Threshold parameter for QE scheme; controls switching
 *                    between the exponential and quadratic branches
 *
 * Hull-White Parameters:
 *   eta            - Volatility of the short rate process
 *   lambda         - Mean reversion speed of the short rate
 *
 * Simulation Parameters:
 *   T              - Time to expiry in years
 *   N              - Number of time steps
 *   dt             - Time step size (T / N)
 *   k0, k1, k2, k3 - Precomputed constants for the log-spot update
 *   L1, L2         - Precomputed constants for the Hull-White rate update
 *   expression     - Precomputed exp(-kappa * dt) for the QE scheme
 */

#pragma once
#include "ModelBase.h"
#include "RandomBase.h"

#ifndef HESTONHULLWHITEMODEL
#define HESTONHULLWHITEMODEL

class HestonHullWhiteModel : public ModelBase
{
public:
	HestonHullWhiteModel(PseudoFactory& factory);
	~HestonHullWhiteModel() override = default;
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const override;

	double Get_MT() const override
	{
		return Mt_.back();
	}

private:
	double S0_{};

	double V_0_{};						//Heston Parameters
	double corrXR_{};
	double corrXV_{};
	double volvol_{};
	double meanreversion_{};
	double ltmean_{};
	double PsiC_{};

	double eta_{};						//Hull-White Parameters	
	double lambda_{};

	double k0_{};						//Parameters for asset simulation and necessary parameters for QE scheme to work with the Hull-White model.
	double k1_{};
	double k2_{};
	double k3_{};
	double L1_{};
	double L2_{};

	double expression_{};
	double differentiationStep_{};		//Used for numerical differentiation
	double N_{};
	double T_{};
	double dt_{};

	double ZCB(double t) const { return std::exp(-0.1 * t); }	//Hard coded initial bond curve
	double GetM_T() const { return Mt_.back(); }
	double f0(double t) const;
	double theta(double t) const;

	double next_v(boost::mt19937&, double V) const;
	std::vector<double> generate_CIR_path(boost::mt19937& rng) const;

	mutable std::vector<double> cir_path_;
	mutable std::vector<double> pathR_;
	mutable std::vector<double> Mt_;
	mutable std::vector<double> timeDt_;

	std::unique_ptr<RandomBase> generator_{};
};


#endif
