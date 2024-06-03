#pragma once
#include <utility>
#include <Eigen/Dense>
#include "TermStructureBase.h"
#include "ImportanceSampledPath.h"
#include "ModelBase.h"
#include "TermStructureBase.h"

class ModelBase;
class TermStructureBase;
class ImportanceSampledPath;

class MCGatherer
{

public:
	virtual ~MCGatherer() {}
	void accumulate(const Eigen::VectorXd& payoffs, const ModelBase& model);							// will modify mean_payoff_ and standard_error_
	std::pair<double, double> GetResults(const TermStructureBase& ts, const ModelBase& model) const;


private:

	double mean_payoff_{};
	double standard_error_{};

};