
#include <iostream>
#include <boost/math/distributions/normal.hpp>

#include "ApplicationWrapper.h"
#include "AnalyticalFormulas.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


int main(int argc, char* argv[])
{

    std::cout << "Main method" << std::endl;
	Application_Wrapper app;
	app.run();

	//double bs_call = af::Black_Scholes_Call(100, 100, 0.5, 0.05, 0.30);

    //std::cout << "BS price: " << bs_call << std::endl;

    std::cout << "Finished main! " << std::endl;

   
}
