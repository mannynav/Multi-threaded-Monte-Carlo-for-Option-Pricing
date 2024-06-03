#pragma once


#ifndef BROWNIANMOTIONPATHBASE
#define BROWNIANMOTIONPATHBASE

#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

class BrownianMotionPathBase
{
public:
	virtual ~BrownianMotionPathBase() {}
	virtual void GeneratePath(std::vector<double>& path,boost::mt19937& rng) = 0;
	virtual std::vector<double> likelihood_ratio() const = 0;

private:


};


#endif
