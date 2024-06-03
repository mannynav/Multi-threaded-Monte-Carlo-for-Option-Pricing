

#pragma once


#ifndef ANTITHETICPATH_H
#define ANTITHETICPATH_H

#include "BrownianMotionPathBase.h"
#include "PseudoFactory.h"

class AntitheticPath : public BrownianMotionPathBase
{

public:

	AntitheticPath(const PseudoFactory& factory);
	void GeneratePath(std::vector<double>& path, boost::mt19937& rng) override;
	std::vector<double> likelihood_ratio() const override
	{
		return W;
	}

private:

	double drift_{};
	double sigma_{};
	double T_{};
	double N_{};
	double dt_{};
	bool even_;			//this will be the trigger for odd and even paths

	boost::normal_distribution<> standard_norm_distro_;
	mutable std::vector<double> W{};
	std::vector<double> neg_path{};

};

#endif