#include "DoubleBarrierKnockInCall.h"

#include "PseudoFactory.h"

DoubleBarrierKnockInCall::DoubleBarrierKnockInCall(double strike, double lowerB, double upperB, double expiry) : strike_(strike),
                                                                                                                 lower_barrier_(lowerB),
                                                                                                                 upper_barrier_(upperB),
                                                                                                                 expiry_(expiry)
{}

DoubleBarrierKnockInCall::DoubleBarrierKnockInCall(PseudoFactory& factory) : strike_(factory.GetStrike()),
																			 lower_barrier_(factory.GetLowerBarrier()),
																			 upper_barrier_(factory.GetUpperBarrier()),
																			 expiry_(factory.GetExpiry())		
{
	
}


double DoubleBarrierKnockInCall::ComputePayoff(double final_price) const
{

    return std::max(final_price - strike_, 0.0);

	
}

Eigen::VectorXd DoubleBarrierKnockInCall::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{
    const Eigen::VectorXd ExpiryPrice = stock_prices.rightCols(1);

    Eigen::VectorXd payoffs(stock_prices.rows()); // Initialize payoff vector
    payoffs.setZero(); // Initialize all elements to zero

    for (int path_index = 0; path_index < stock_prices.rows(); ++path_index) {

        for (int time_step = 0; time_step < stock_prices.cols(); ++time_step) {

            if (stock_prices(path_index, time_step) >= upper_barrier_ || stock_prices(path_index,time_step <= lower_barrier_)) {
                payoffs(path_index) = ComputePayoff(ExpiryPrice(path_index));
                break; // No need to check further time steps for this path 
            }
        }
    }
    return payoffs;
	
}

std::map<std::string,double> DoubleBarrierKnockInCall::ComputeGreeks(Eigen::MatrixXd& stock_prices, const ModelBase& model) const
{
	return {};
}

	

