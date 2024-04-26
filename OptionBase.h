

#ifndef OptionBaseH
#define OptionBaseH

#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <map>
#include <boost/math/distributions/normal.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

class OptionBase
{
public:
    virtual ~OptionBase() {}

    virtual double ComputePayoff(const double) const = 0;
    virtual Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const = 0;
    virtual std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& matrix) const = 0;
};


#endif

