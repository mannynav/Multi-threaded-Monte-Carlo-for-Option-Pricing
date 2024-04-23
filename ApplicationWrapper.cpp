#include <iostream>

#include "PseudoFactory.h"
#include "ApplicationBase.h"
#include "ApplicationWrapper.h"
#include "Input.h"


Application_Wrapper::Application_Wrapper()
	: fac_(std::make_unique<PseudoFactory>())
{
	std::cout << "Application wrapper constructor: creating application" << '\n';

	inp_ = new Input;

	fac_->SetInput(inp_);
	app_ = fac_->CreateApplication();
}

Application_Wrapper::~Application_Wrapper()
{
	delete inp_;
}


void Application_Wrapper::run() const
{
	std::cout << "Application_Wrapper::run \n";

	//This delegates to Valuation::run() which delegates to MC Simulation
	app_->run();
}
