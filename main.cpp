
#include <iostream>
#include "ApplicationBase.h"
#include "PseudoFactory.h"
#include "Input.h"


#define BOOST_TEST_MODULE test
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


int main(int argc, char* argv[])
{

	std::cout << "Main method" << std::endl;

	PseudoFactory factory;

	Input* Input_ = new Input;

	factory.SetInput(Input_);

	std::unique_ptr<ApplicationBase> app = factory.CreateApplication();			//If valuation is the only method this does not really have to be a unique pointer but a calibration application
																				//might be added in the future

	app->run();

	std::cout << "Running tests" << std::endl;
	boost::unit_test::unit_test_main(&init_unit_test, argc, argv);

	delete Input_;


	return 0;
}
