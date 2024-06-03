

#include "EuroCallOption.h"
#include <Eigen/Dense>
#include "boost/test/unit_test.hpp"



BOOST_AUTO_TEST_CASE(TestEuroCallOptionPayoff) {

	EuroCallOption option(100, 1);

	double resultITM = option.ComputePayoff(110);
	double resultOTM = option.ComputePayoff(90);
	double resultATM = option.ComputePayoff(100);

	BOOST_CHECK_EQUAL(resultITM, std::max(110.0-100.0,0.0));
	BOOST_CHECK_EQUAL(resultOTM, std::max(90.0-100.0,0.0));
	BOOST_CHECK_EQUAL(resultATM, std::max(100.0-100.0,0.0));
}

BOOST_AUTO_TEST_CASE(TestEuroCallOptionComputePayoffs) {

	double strike = 100;
	EuroCallOption option(strike, 1);
	Eigen::MatrixXd prices(3, 3);

	prices << 100.0,110.0,90.0,
			  100.0,90.0,80.0,
			  100.0,100.0,100.0;

	Eigen::VectorXd ExpiryPrices = prices.rightCols(1);
	Eigen::VectorXd payoffVector = ExpiryPrices.unaryExpr([&](double final_price)
		{
			return option.ComputePayoff(final_price);
		});
	Eigen::VectorXd result = option.ComputePayoffs(prices);

	BOOST_CHECK_EQUAL(result(0), std::max(ExpiryPrices(0) - strike, 0.0));
	BOOST_CHECK_EQUAL(result(1), std::max(ExpiryPrices(1) - strike, 0.0));
	BOOST_CHECK_EQUAL(result(2), std::max(ExpiryPrices(2) - strike, 0.0));

}

