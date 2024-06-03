#include "AsianCallOption.h"
#include <Eigen/Dense>
#include "boost/test/unit_test.hpp"



BOOST_AUTO_TEST_CASE(TestAsianCallOptionPayoff) {


	double strike = 125;
	AsianCallOption option(strike, 1);

	double resultITM = option.ComputePayoff(135);
	double resultOTM = option.ComputePayoff(50);
	double resultATM = option.ComputePayoff(strike);

	BOOST_CHECK_EQUAL(resultITM, std::max(135 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultOTM, std::max(50 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultATM, std::max(strike - strike, 0.0));
}

BOOST_AUTO_TEST_CASE(TestAsianCallOptionComputePayoffs) {

	double strike = 120;
	AsianCallOption option(strike, 1);
	Eigen::MatrixXd prices(3, 3);
	prices << 100.0, 110.0, 10,
		100.0, 90.0, 1500.0,
		100.0, 100.0, 400.0;

	Eigen::VectorXd ExpiryPrices = prices.rowwise().mean();
	Eigen::VectorXd payoffVector = ExpiryPrices.unaryExpr([&](double final_price)
		{
			return option.ComputePayoff(final_price);
		});
	Eigen::VectorXd result = option.ComputePayoffs(prices);

	BOOST_CHECK_EQUAL(result(0), payoffVector(0));
	BOOST_CHECK_EQUAL(result(1), payoffVector(1));
	BOOST_CHECK_EQUAL(result(2), payoffVector(2));

}
