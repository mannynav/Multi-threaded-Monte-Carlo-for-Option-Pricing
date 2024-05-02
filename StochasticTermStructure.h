
#pragma once
#include "ModelBase.h"
#include "TermStructureBase.h"


class PseudoFactory;
class ModelBase;

class StochasticTermStructure : public TermStructureBase
{
public:
	explicit StochasticTermStructure()
	{}

	StochasticTermStructure(PseudoFactory& factory);

	double Get_MT(const ModelBase& model) const override
	{
		return 1/model.Get_MT();
	}

private:
	double T_{};
	double r_{};
};
