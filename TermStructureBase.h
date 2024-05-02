#pragma once
#include <complex>


class ModelBase;

class TermStructureBase
{

public:

	explicit TermStructureBase() = default;

	~TermStructureBase() {}

	virtual double Get_MT(const ModelBase& model) const = 0;

private:
	double T_{};
	double r_{};
};

