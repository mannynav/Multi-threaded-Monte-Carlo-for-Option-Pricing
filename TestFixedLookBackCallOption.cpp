#include "FixedLookBackCall.h"
#include <Eigen/Dense>
#include "boost/test/unit_test.hpp"


BOOST_AUTO_TEST_CASE(TestFixedLBCallOptionPayoff) {

	//EuroCallOption option(100, 1);
	double strike = 200;
	FixedLookBackCallOption option(strike, 1);

	double resultITM = option.ComputePayoff(220);
	double resultOTM = option.ComputePayoff(180);
	double resultATM = option.ComputePayoff(strike);

	BOOST_CHECK_EQUAL(resultITM, std::max(220 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultOTM, std::max(180 - strike, 0.0));
	BOOST_CHECK_EQUAL(resultATM, std::max(strike - strike, 0.0));
}

BOOST_AUTO_TEST_CASE(TestFixedLBCallOptionComputePayoffs) {

	double strike = 210;
	FixedLookBackCallOption option(strike, 1);
	Eigen::MatrixXd prices(3, 3);
	prices << 100.0, 210.0, 105,
		100.0, 90.0, 80,
		100, 110, 235;

	Eigen::VectorXd ExpiryPrices = prices.rowwise().maxCoeff();
	Eigen::VectorXd payoffVector = ExpiryPrices.unaryExpr([&](double final_price)
		{
			return option.ComputePayoff(final_price);
		});
	Eigen::VectorXd result = option.ComputePayoffs(prices);

	BOOST_CHECK_EQUAL(result(0), payoffVector(0));
	BOOST_CHECK_EQUAL(result(1), payoffVector(1));
	BOOST_CHECK_EQUAL(result(2), payoffVector(2));

}
