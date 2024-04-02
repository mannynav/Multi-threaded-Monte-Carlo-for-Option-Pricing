
#include "FlatTermStructure.h"
#include "PseudoFactory.h"


FlatTermStructure::FlatTermStructure(PseudoFactory& factory) : T_(factory.GetT()), r_(factory.Getr())
{
}


double FlatTermStructure::Get_MT() const
{
	double discount = std::exp(-T_ * r_);
	return discount;
}
