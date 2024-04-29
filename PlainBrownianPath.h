#pragma once


#ifndef PLAINBROWNIANPATH
#define PLAINBROWNIANPATH

#include "BrownianMotionPathBase.h"


class PlainBrownianPath : public BrownianMotionPathBase
{

public:

	PlainBrownianPath() = default;
	void GeneratePath(std::vector<double>& path, boost::mt19937& rng) const override;

};

#endif