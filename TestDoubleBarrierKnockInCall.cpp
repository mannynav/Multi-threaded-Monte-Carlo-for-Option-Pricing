#include "DoubleBarrierKnockInCall.h"
#include "EuroCallOption.h"
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE(TestDoubleBarrierKnockInCallPayoff)
{
	double strike = 100.0;
	double lower_barrier = 90.0;
	double upper_barrier = 110.0;
	double expiry= 1.0;

	double priceITM = 140;
	double priceOTM = 95;
	double priceATM = strike;

	DoubleBarrierKnockInCall option(strike, lower_barrier, upper_barrier, expiry);

	double resultITM = option.ComputePayoff(priceITM);
	double resultOTM = option.ComputePayoff(priceOTM);
	double resultATM = option.ComputePayoff(priceATM);

	BOOST_CHECK_EQUAL(resultITM, std::max(priceITM-strike, 0.0));
	BOOST_CHECK_EQUAL(resultOTM, std::max(priceOTM-strike, 0.0));
	BOOST_CHECK_EQUAL(resultATM, std::max(priceATM-strike, 0.0));

}

BOOST_AUTO_TEST_CASE(TestDoubleBarrierKnockInCallComputePayoffs)
{

	double strike = 100.0;
	double lower_barrier = 90.0;
	double upper_barrier = 110.0;
	double expiry = 1.0;

	DoubleBarrierKnockInCall option(strike, lower_barrier, upper_barrier, expiry);

	Eigen::MatrixXd prices(4, 4);
	prices << 100.0, 110.0, 100.0, 120.0,
		      100.0, 90.0, 80.0, 70,
		      100.0, 109.0, 95, 100.0,
		      100.0, 105.0, 95, 100.0;

	Eigen::VectorXd ExpiryPrices = prices.rightCols(1);
	Eigen::VectorXd payoffs(prices.rows());
	payoffs.setZero();											// paths that do not knock in remain 0

	for(int index = 0; index < prices.rows(); ++index)
	{
		for(int step = 0; step < prices.cols()-1; ++step)	   // do not include last column as this is the expiry column
		{
			if (prices(index, step) >= upper_barrier || prices(index, step) <= lower_barrier)
			{
				payoffs(index) = option.ComputePayoff(ExpiryPrices(index));
				break;
			}
		}
	}

	Eigen::VectorXd result = option.ComputePayoffs(prices);

	BOOST_CHECK_EQUAL(result(0), payoffs(0));
	BOOST_CHECK_EQUAL(result(1), payoffs(1));
	BOOST_CHECK_EQUAL(result(2), payoffs(2));
	BOOST_CHECK_EQUAL(result(3), payoffs(3));

}