#pragma once
#include <complex>


class TermStructureBase
{

public:

	explicit TermStructureBase() {}

	~TermStructureBase() {}

	virtual double Get_MT() const = 0;

private:
	double T_{};
	double r_{};
};

