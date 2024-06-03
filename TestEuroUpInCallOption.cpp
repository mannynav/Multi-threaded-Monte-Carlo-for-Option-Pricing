#include "EuroUpInCallOption.h"
#include <Eigen/Dense>
#include "boost/test/unit_test.hpp"



BOOST_AUTO_TEST_CASE(TestEuroUpInOutCallOptionPayoff) {

	double strike = 125;
	double barrier = 132;
	EuroUpInCallOption option(strike,1,barrier);

	double resultITM = option.ComputePayoff(140);
	double resultOTM = option.ComputePayoff(120);
	double resultATM = option.ComputePayoff(strike);

	BOOST_CHECK_EQUAL(resultITM, std::max(140 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultOTM, std::max(120 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultATM, std::max(strike - strike, 0.0));
}

BOOST_AUTO_TEST_CASE(TestEuroUpInOutCallComputePayoffs) {

	double strike = 100;
	double barrier = 102;
	EuroUpInCallOption option(strike, 1, barrier);
	Eigen::MatrixXd prices(3, 3);
	prices << 100.0, 110.0, 90.0,
		100.0, 90.0, 80.0,
		100.0, 100.0, 100.0;

	Eigen::VectorXd ExpiryPrices = prices.rightCols(1);
	Eigen::VectorXd payoffs(prices.rows());
	payoffs.setZero();											// values not on or above the barrier remain zero

	for(int path_index = 0; path_index < prices.rows(); ++path_index)
	{
		for(int step = 0; step < prices.cols(); ++step)
		{
			if(prices(path_index, step) >= barrier)
			{
				payoffs(path_index) = option.ComputePayoff(ExpiryPrices(path_index));
				break;
			}
		}
	}
	Eigen::VectorXd result = option.ComputePayoffs(prices);

	BOOST_CHECK_EQUAL(result(0), payoffs(0));
	BOOST_CHECK_EQUAL(result(1), payoffs(1));
	BOOST_CHECK_EQUAL(result(2), payoffs(2));
}
