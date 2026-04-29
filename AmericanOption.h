#pragma once

#include "OptionBase.h"

class AmericanPutOption : public OptionBase {
public:
    AmericanPutOption(double strike, double r, double T, int N)
        : strike_(strike), r_(r), T_(T), N_(N), dt_(T / N) {
    }

    Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;
    double ComputePayoff(double final_price) const override
    {
        return std::max(strike_ - final_price, 0.0);
    }

    std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& matrix, const ModelBase& model) const override
    {
        return {}; // not implemented yet
    }

private:
    double strike_, r_, T_, dt_;
    int N_;
};

class AmericanCallOption : public OptionBase {
public:
    AmericanCallOption(double strike, double r, double T, int N)
        : strike_(strike), r_(r), T_(T), N_(N), dt_(T / N) {
    }

    Eigen::VectorXd ComputePayoffs(Eigen::MatrixXd& stock_prices) const override;
    double ComputePayoff(double final_price) const override
    {
        return std::max(final_price - strike_, 0.0);
    }

    std::map<std::string, double> ComputeGreeks(Eigen::MatrixXd& matrix, const ModelBase& model) const override
    {
        return {}; // not implemented yet
    }

private:
    double strike_, r_, T_, dt_;
    int N_;

};