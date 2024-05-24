
#include "FlatTermStructure.h"
#include "PseudoFactory.h"


FlatTermStructure::FlatTermStructure(const PseudoFactory& factory) : T_(factory.GetExpiry()), r_(factory.GetRiskFreeRate())
{
}

