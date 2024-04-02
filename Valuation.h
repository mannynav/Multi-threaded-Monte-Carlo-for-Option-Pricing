#pragma once

#ifndef ValuationH
#define ValuationH


class Output;

class OptionBase;
class ModelBase;
class TermStructureBase;
class ValuationMethodBase;

class PseudoFactory;

#include "ApplicationBase.h"

class Valuation : public ApplicationBase
{
public:
	explicit Valuation(PseudoFactory& factory);
	~Valuation();


	void run() override;

private:

	//Make this shared pointer
	OptionBase* option_;
	ModelBase* model_;
	TermStructureBase* term_structure_;

	ValuationMethodBase* method_; //will return the MCSimulation object


};


#endif