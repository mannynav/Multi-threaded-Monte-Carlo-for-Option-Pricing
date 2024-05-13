
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



class ModelBase
{
public:
    virtual ~ModelBase() {}
    virtual Eigen::MatrixXd simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const  =0;
    virtual double Get_MT() const = 0;
};


#endif

