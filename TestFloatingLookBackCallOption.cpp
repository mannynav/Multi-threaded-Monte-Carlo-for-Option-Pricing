#include "FloatingLookBackCall.h"
#include <Eigen/Dense>
#include "boost/test/unit_test.hpp"



BOOST_AUTO_TEST_CASE(TestFloatingLBCallOptionPayoff) {

	double strike = 50;
	FloatingLookBackCallOption option(strike, 1);

	double resultITM = option.ComputePayoff(70);
	double resultOTM = option.ComputePayoff(45);
	double resultATM = option.ComputePayoff(strike);

	BOOST_CHECK_EQUAL(resultITM, std::max(70 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultOTM, std::max(45 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultATM, std::max(strike - strike, 0.0));
}

BOOST_AUTO_TEST_CASE(TestFloatingLBCallOptionComputePayoffs) {

	double strike = 70;
	FloatingLookBackCallOption option(strike, 1);
	Eigen::MatrixXd prices(3, 3);
	prices << 70, 110.0, 125,
		70, 90.0, 70,
		70, 60, 62;

	Eigen::VectorXd payoffs = prices.rightCols(1) - prices.rowwise().minCoeff();
	Eigen::VectorXd result = option.ComputePayoffs(prices);

	BOOST_CHECK_EQUAL(result(0), payoffs(0));
	BOOST_CHECK_EQUAL(result(1), payoffs(1));
	BOOST_CHECK_EQUAL(result(2), payoffs(2));
}

