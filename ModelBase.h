
#ifndef ProcessBaseH
#define ProcessBaseH

#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <boost/math/distributions/normal.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include "PseudoFactory.h"
#include "SamplingMethods.h"



class ModelBase
{
public:
    virtual ~ModelBase() {}
    virtual void simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const  =0;
    virtual double Get_MT() const = 0;
};


#endif

