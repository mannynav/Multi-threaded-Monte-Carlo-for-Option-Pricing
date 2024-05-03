

#include "Valuation.h"
#include "PseudoFactory.h"

#include "ValuationMethodBase.h"
#include "OptionBase.h"
#include "ModelBase.h"
#include "TermStructureBase.h"


Valuation::Valuation(PseudoFactory& factory) : model_(nullptr), term_structure_(nullptr), method_(nullptr)
{
	option_ = factory.CreateOption();
	model_ = factory.CreateModel();
	method_ = factory.CreateValuationMethod();
	term_structure_ = factory.CreateTermStructure();
}
Valuation::~Valuation()
= default
;

void Valuation::run()
{
	std::cout << "Valuation::run()" << std::endl;
	method_->run(*option_, *model_, *term_structure_);
}