
#include "AmericanOption.h"

// ---- LSM helper: shared logic, exercise_value distinguishes put vs call ----
static Eigen::VectorXd LSM(
    Eigen::MatrixXd& stock_prices,
    double strike,
    double r,
    double dt,
    int N,
    bool is_put)
{
    int num_paths = stock_prices.rows();
    double discount = std::exp(-r * dt);

    // Step 1: initialize cash flows at expiry
    Eigen::VectorXd cash_flows(num_paths);
    for (int i = 0; i < num_paths; ++i)
    {
        double S = stock_prices(i, N);
        cash_flows(i) = is_put ? std::max(strike - S, 0.0)
            : std::max(S - strike, 0.0);
    }

    // Step 2: backward pass
    for (int t = N - 1; t >= 1; --t)
    {
        // Discount cash flows back one step
        cash_flows *= discount;

        // Find in-the-money paths at time t
        std::vector<int> itm;
        for (int i = 0; i < num_paths; ++i)
        {
            double S = stock_prices(i, t);
            double exercise = is_put ? strike - S : S - strike;
            if (exercise > 0.0)
                itm.push_back(i);
        }

        if (itm.empty()) continue;

        int n_itm = itm.size();

        // Build regression matrix [1, S, S^2] for ITM paths
        Eigen::MatrixXd X(n_itm, 3);
        Eigen::VectorXd Y(n_itm);

        for (int k = 0; k < n_itm; ++k)
        {
            double S = stock_prices(itm[k], t);
            X(k, 0) = 1.0;
            X(k, 1) = S;
            X(k, 2) = S * S;
            Y(k) = cash_flows(itm[k]);
        }

        // Least squares: estimate continuation value
        Eigen::VectorXd coeffs = X.colPivHouseholderQr().solve(Y);

        // Step 3: compare continuation vs immediate exercise
        for (int k = 0; k < n_itm; ++k)
        {
            double S = stock_prices(itm[k], t);
            double continuation = coeffs(0) + coeffs(1) * S + coeffs(2) * S * S;
            double exercise = is_put ? strike - S : S - strike;

            if (exercise > continuation)
                cash_flows(itm[k]) = exercise;  // early exercise
        }
    }

    // Discount from t=dt back to t=0
    cash_flows *= discount;

    // cancel the discount GetResults will apply
    cash_flows *= std::exp(r * N * dt);

    return cash_flows;
}

Eigen::VectorXd AmericanPutOption::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{
    std::cout << "inside compute_payoffs for American Put" << std::endl;
    return LSM(stock_prices, strike_, r_, dt_, N_, true);
}

Eigen::VectorXd AmericanCallOption::ComputePayoffs(Eigen::MatrixXd& stock_prices) const
{
    std::cout << "inside compute_payoffs for American Put" << std::endl;
    return LSM(stock_prices, strike_, r_, dt_, N_, false);
}