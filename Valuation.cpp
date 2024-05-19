

#include "Valuation.h"
#include "PseudoFactory.h"

#include "ValuationMethodBase.h"
#include "OptionBase.h"
#include "ModelBase.h"
#include "TermStructureBase.h"


Valuation::Valuation(PseudoFactory& factory) : model_(factory.CreateModel()), 
											   term_structure_(factory.CreateTermStructure()), 
											   method_(factory.CreateValuationMethod()),
										       option_(factory.CreateOption())
{}
Valuation::~Valuation() = default;

void Valuation::run()
{
	std::cout << "Valuation::run()" << std::endl;

	method_->run(*option_, *model_, *term_structure_);
	method_->OutputResults(*term_structure_, *model_);
}