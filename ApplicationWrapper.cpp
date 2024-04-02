
#include <iostream>

#include "PseudoFactory.h"
#include "Input.h"
#include "ApplicationBase.h"
#include "ApplicationWrapper.h"


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Application_Wrapper::Application_Wrapper()
    : app_(0)
{
    fac_ = new PseudoFactory;      // owns this pointer
    inp_ = new Input;              // owns this pointer

    fac_->SetInput(inp_);

    std::cout << "Applicaiton wrapper constructor: creating application" << std::endl;
    app_ = fac_->CreateApplication();
}

Application_Wrapper::~Application_Wrapper()
{
    delete fac_;
    delete inp_;
    delete app_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	run
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Application_Wrapper::run()
{
    std::cout << "Application_Wrapper::run \n";

    //This delegates to Valuation::run() which delegates to MC Simulation
    app_->run();

}