
#include "FlatTermStructure.h"
#include "PseudoFactory.h"


FlatTermStructure::FlatTermStructure(const PseudoFactory& factory) : T_(factory.GetT()), r_(factory.Getr())
{
}

