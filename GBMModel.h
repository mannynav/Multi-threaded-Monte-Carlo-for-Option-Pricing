#include "ModelBase.h"
#include "PseudoFactory.h"

#ifndef GBMMODEL_H
#define GBMMODEL_H

class PseudoFactory;

class GBMModel : public ModelBase

{
public:
	GBMModel(double S0, double r, double sigma);
	GBMModel(PseudoFactory& factory);
	void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const override;

private:
	double S0_{};
	double r_{};
	double sigma_{};

	double dt_{};
	double drift_{};
};
#endif // GBMMODEL_H
