
#pragma once
#include "ModelBase.h"
#include "TermStructureBase.h"


class PseudoFactory;
class ModelBase;

class StochasticTermStructure : public TermStructureBase
{
public:
	explicit StochasticTermStructure() = default;

	StochasticTermStructure(const PseudoFactory& factory);

	double Get_MT(const ModelBase& model) const override
	{
		return 1/model.Get_MT();
	}

private:
	double T_{};
	double r_{};
};

inline StochasticTermStructure::StochasticTermStructure(const PseudoFactory& factory)
{
	T_ = factory.GetT();
	r_ = factory.Getr();
}
