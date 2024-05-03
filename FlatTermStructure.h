#pragma once
#include "ModelBase.h"
#include "TermStructureBase.h"


class PseudoFactory;
class ModelBase;

class FlatTermStructure : public TermStructureBase
{
public:
	explicit FlatTermStructure() = default;

	FlatTermStructure(const PseudoFactory& factory);

	double Get_MT(const ModelBase& model) const override
	{
		double result = 1 / model.Get_MT();

		std::cout << "Result: " << result << std::endl;

		return result;
	}

private :
	double T_{};
	double r_{};
};
