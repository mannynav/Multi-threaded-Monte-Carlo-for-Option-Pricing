
#include "FlatTermStructure.h"
#include "PseudoFactory.h"


FlatTermStructure::FlatTermStructure(PseudoFactory& factory) : T_(factory.GetT()), r_(factory.Getr())
{
}

