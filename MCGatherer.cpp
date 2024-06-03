#include "MCGatherer.h"



void MCGatherer::accumulate(const Eigen::VectorXd& payoffs, const ModelBase& model)
{
	mean_payoff_ = payoffs.mean();


	double sum_squared_devs = 0.0;
	for (double value : payoffs) {
		sum_squared_devs += std::pow(value - mean_payoff_, 2);
	}

	double variance = sum_squared_devs / (payoffs.size() - 1);
	double std_deviation = std::sqrt(variance);
	standard_error_ = std_deviation / std::sqrt(payoffs.size());
}

std::pair<double,double> MCGatherer::GetResults(const TermStructureBase& ts, const ModelBase& model) const
{
	double discount = ts.Get_MT(model);
	return std::make_pair(mean_payoff_ * discount, standard_error_);
}