#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This class implements the Heston Hull-White model using the Quadratic Exponential discretization scheme for the variance process.
// Prices obtained for European call options match those obtained with the COS method outlined in Oosterlee and Grezlak, 2019.
// This class is not (yet) implemented for multi-threading.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ModelBase.h"
#include "RandomBase.h"

#ifndef HESTONHULLWHITEMODEL
#define HESTONHULLWHITEMODEL

class HestonHullWhiteModel : public ModelBase
{
public:
	HestonHullWhiteModel(PseudoFactory& factory);
	~HestonHullWhiteModel() override = default;
	Eigen::MatrixXd simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;

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
	double dt_{};
	double differentiationStep_{};		//Used for numerical differentiation
	double N_{};
	double T_{};

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
