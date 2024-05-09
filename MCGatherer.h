#pragma once
#include <utility>
#include <Eigen/Dense>

#include "TermStructureBase.h"


class ImportanceSampling;
class ModelBase;
class TermStructureBase;


class MCGatherer
{

public:
	virtual ~MCGatherer() {}

	virtual void accumulate(const Eigen::VectorXd& payoffs, const ModelBase& model)
	{
		
		//std::vector<double> RN = model.get_likelihood_ratio();

		//Eigen::VectorXd newPayoffs = Eigen::VectorXd(payoffs.size());
		//for (int i = 0; i < payoffs.size(); i++)
		//{
		//	newPayoffs[i] = payoffs[i] * RN[i];
		//}
		//

		////payoffs for IS
		//double mean_payoff = newPayoffs.mean();

		mean_payoff_ = payoffs.mean();


		double sum_squared_devs = 0.0;
		for (double value : payoffs) {
			sum_squared_devs += std::pow(value - mean_payoff_, 2);
		}

		double variance = sum_squared_devs / (payoffs.size() - 1); // Unbiased sample variance
		double std_deviation = std::sqrt(variance);
		double standard_error = std_deviation / std::sqrt(payoffs.size());
	}

	std::pair<double,double> GetResults(const TermStructureBase& ts,const ModelBase& model) const {

		double discount = ts.Get_MT(model);
		return std::make_pair(mean_payoff_ * discount, standard_error_);
	}

private:

	double mean_payoff_{};
	double standard_error_{};

};