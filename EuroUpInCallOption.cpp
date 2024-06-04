
#include "PseudoFactory.h"
#include "EuroUpInCallOption.h"


EuroUpInCallOption::EuroUpInCallOption(PseudoFactory& factory) : expiry_(factory.GetExpiry()), strike_(factory.GetStrike()), barrier_(factory.GetUpperBarrier())
{
}

double EuroUpInCallOption::ComputePayoff(double final_price) const
{
	return std::max(final_price - strike_, 0.0);

}

Eigen::VectorXd EuroUpInCallOption::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{
    const Eigen::VectorXd ExpiryPrice = stock_prices.rightCols(1);
    const double barrier = barrier_;

    Eigen::VectorXd payoffs(stock_prices.rows()); // Initialize payoff vector
	payoffs.setZero(); // Initialize all elements to zero

    for (int path_index = 0; path_index < stock_prices.rows(); ++path_index) {

        for (int time_step = 0; time_step < stock_prices.cols(); ++time_step) {

            if (stock_prices(path_index, time_step) >= barrier) {
                payoffs(path_index) = ComputePayoff(ExpiryPrice(path_index));
                std::cout << payoffs(path_index) << std::endl;
                break; // No need to check further time steps for this path 
            }
        }
    }
    return payoffs;
}

std::map<std::string, double> EuroUpInCallOption::ComputeGreeks(Eigen::MatrixXd& stock_prices, const ModelBase& model) const
{
    std::map<std::string, double> greek_map{};
	return greek_map;
}
