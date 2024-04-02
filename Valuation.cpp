

#include "Valuation.h"
#include "PseudoFactory.h"

#include "ValuationMethodBase.h"
#include "OptionBase.h"
#include "ModelBase.h"
#include "TermStructureBase.h"


Valuation::Valuation(PseudoFactory& factory) : option_(nullptr), model_(nullptr), term_structure_(nullptr), method_(nullptr)
{
	option_ = factory.CreateOption(); //return EuroCallOption
	model_ = factory.CreateModel(); //return GBMModel
	method_ = factory.CreateValuationMethod(); //return MC Simulation
	term_structure_ = factory.CreateTermStructure(); //return FlatTermStructure	
};

Valuation::~Valuation()
{
	delete option_;
	delete model_;
	delete method_;
	delete term_structure_;
	
};

void Valuation::run()
{
	//This method will be the MC simulation.
	std::cout << "Valuation::run()" << std::endl;
	method_->run(*option_, *model_, *term_structure_);
}