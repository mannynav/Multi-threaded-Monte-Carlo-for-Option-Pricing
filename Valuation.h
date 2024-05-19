#pragma once

#ifndef ValuationH
#define ValuationH
#include <memory>


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

	std::unique_ptr<OptionBase> option_;
	std::unique_ptr<ModelBase> model_;
	std::unique_ptr<TermStructureBase> term_structure_;
	std::unique_ptr<ValuationMethodBase> method_;
};


#endif