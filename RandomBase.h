#pragma once


#include <vector>
#include "PseudoFactory.h"

#include <memory>
#include <mutex>

#include "boost/random.hpp"
#include "Eigen/Dense"
#include "Eigen/Dense"


class RandomBase
{

public:

	virtual ~RandomBase() {}
	virtual void SeedGenerator(unsigned int seed) = 0;
	virtual boost::mt19937& GetGenerator() = 0;

private:


};