#pragma once

#include "ModelBase.h"
#include "PseudoFactory.h"
#include "RandomBase.h"

#ifndef GBMMODEL_H
#define GBMMODEL_H

class PseudoFactory;
class BrownianMotionPathBase;

class GBMModel : public ModelBase

{
public:
	GBMModel(double S0, double r, double sigma);
	GBMModel(PseudoFactory& factory);
	~GBMModel();
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;

private:
	double S0_{};
	double r_{};
	double sigma_{};

	double dt_{};
	double drift_{};
	double N_{};
	double T_{};

	BrownianMotionPathBase* path_;
	RandomBase* generator_{};
};
#endif // GBMMODEL_H
