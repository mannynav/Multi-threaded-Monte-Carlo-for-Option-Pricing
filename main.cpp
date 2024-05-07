
#include <iostream>
#include <valarray>
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

	return 0;
}
