
#include <iostream>

#include "ApplicationBase.h"
#include "AnalyticalFormulas.h"
#include "PseudoFactory.h"
#include "Input.h"

#include <gtest/gtest.h>


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

   
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();


	return 0;
}
