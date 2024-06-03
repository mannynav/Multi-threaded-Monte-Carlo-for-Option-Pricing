#pragma once


#ifndef PLAINBROWNIANPATH
#define PLAINBROWNIANPATH

#include "BrownianMotionPathBase.h"


class PlainBrownianPath : public BrownianMotionPathBase
{

public:

	PlainBrownianPath();
	void GeneratePath(std::vector<double>& path, boost::mt19937& rng) override;
	std::vector<double> likelihood_ratio() const override
	{
		std::vector<double> W;
		return W;
	}

private:

	boost::normal_distribution<> standard_norm_distro_;

};

#endif