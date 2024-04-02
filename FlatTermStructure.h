#pragma once
#include "TermStructureBase.h"


class PseudoFactory;

class FlatTermStructure : public TermStructureBase
{
public:
	explicit FlatTermStructure()
	{}

	FlatTermStructure(PseudoFactory& factory);

	double Get_MT() const override;

private :
	double T_{};
	double r_{};
};
