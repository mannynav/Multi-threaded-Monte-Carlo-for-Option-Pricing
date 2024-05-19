
#include "boost/test/unit_test.hpp"
#include "EuroCallOption.h"


BOOST_AUTO_TEST_CASE(TestEuroCallOptionPayoff) {

	EuroCallOption option(100, 1);
	BOOST_CHECK_EQUAL(option.ComputePayoff(110), std::max(110.0-100.0,0.0));
	//BOOST_CHECK_EQUAL(option.ComputePayoff(120), 0);
}
