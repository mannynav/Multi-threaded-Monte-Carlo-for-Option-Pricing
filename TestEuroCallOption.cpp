

#include "EuroCallOption.h"
#include <Eigen/Dense>

#include "boost/test/unit_test.hpp"


BOOST_AUTO_TEST_CASE(TestEuroCallOptionPayoff) {

	EuroCallOption option(100, 1);

	BOOST_CHECK_EQUAL(option.ComputePayoff(110), std::max(110.0-100.0,0.0));
	BOOST_CHECK_EQUAL(option.ComputePayoff(90), std::max(90.0-100.0,0.0));
	BOOST_CHECK_EQUAL(option.ComputePayoff(100), std::max(100.0-100.0,0.0));
}

//BOOST_AUTO_TEST_CASE(TestEuroCallOptionComputePayoffs) {
//
//	EuroCallOption option(100, 1);
//
//	//Create Eigen Matrix. 
//
//	Eigen::MatrixXd prices;
//
//	//Get right colum.
//
//	Eigen::VectorXd ExpiryPrices = prices.rightCols(1);
//
//	Eigen::VectorXd payoffVector = ExpiryPrices.unaryExpr([&](double final_price)
//		{
//			return option.ComputePayoff(final_price);
//		});
//
//
//	//Apply unary function to every value in right column calling the compute payoff function
//
//	Eigen::VectorXd result = option.ComputePayoffs(prices);
//
//
//
//}

