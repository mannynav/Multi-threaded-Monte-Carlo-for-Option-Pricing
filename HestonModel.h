#pragma once

#include "ModelBase.h"
#include "PseudoFactory.h"
#include "RandomBase.h"

#ifndef HESTONMODEL_H
#define HESTONMODEL_H

class PseudoFactory;

class HestonModel : public ModelBase

{
public:
	HestonModel(double S0, double r, double sigma);
	HestonModel(PseudoFactory& factory);
	virtual ~HestonModel();
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;

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
	double k3_{};
	double k4_{};

	double y1_ = 0.5;
	double y2_ = 0.5;

	double expression_;

	double Next_V(double V) const;
	mutable std::vector<double> FillCirPath_;

	double dt_{};
	double drift_{};
	double N_{};
	double T_{};

	double cbar_{};
	double dof_{};
	double ncp_{};


	RandomBase* generator_{};
	double mean(double meanreversion, double ltmean, double volvol, double dt, double v) const
	{
		double delta = 4 * meanreversion * ltmean / (volvol * volvol);
		double c = volvol * volvol / (4 * meanreversion) * (1 - std::exp(-meanreversion * dt));
		double kappabar = 4 * meanreversion * std::exp(-meanreversion * dt) * v / (volvol * volvol * (1 - std::exp(-meanreversion * dt)));
		double E_V = c * (delta + kappabar);
		return E_V;
	}
	double variance(double meanreversion, double ltmean, double volvol, double dt, double v) const
	{

		double delta = 4* meanreversion * ltmean / (volvol * volvol);
		double c = volvol * volvol / (4 * meanreversion) * (1 - std::exp(-meanreversion * dt));
		double kappabar = 4 * meanreversion * std::exp(-meanreversion * dt) * v / (volvol * volvol * (1 - std::exp(-meanreversion * dt)));
		double VarV = c * c * (2 * delta + 4 * kappabar);
		return VarV;
	}
};
#endif // HESTONMODEL_H