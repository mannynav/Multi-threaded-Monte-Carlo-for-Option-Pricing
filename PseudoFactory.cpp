#include "PseudoFactory.h"

#include "Input.h"

#include "ApplicationBase.h"
#include "Valuation.h"

#include "ValuationMethodBase.h"
#include "MCSimulation.h"


#include "OptionBase.h"
#include "EuroCallOption.h"

#include "ModelBase.h"
#include "GBMModel.h"

#include "TermStructureBase.h"
#include "FlatTermStructure.h"

#include "RandomBase.h"

#include <stdexcept>

#include "RandomMersenneTwister.h"


double PseudoFactory::GetS0() const { return input_->GetS0(); }
double PseudoFactory::Getr() const { return input_->Getr(); }
double PseudoFactory::Getsig() const { return input_->Getsig(); }
char PseudoFactory::GetPtype() const { return input_->GetPtype(); }

double PseudoFactory::GetX() const { return input_->GetX(); }
double PseudoFactory::GetT() const { return input_->GetT(); }
char PseudoFactory::GetOptionType() const { return input_->GetOptionType(); }

long PseudoFactory::GetM() const { return input_->GetM(); }
long PseudoFactory::GetN() const { return input_->GetN(); }
long PseudoFactory::GetNumThreads() const { return input_->GetNumThreads(); }



double PseudoFactory::GetSeed() const
{
	return input_->GetSeed();
}



OptionBase* PseudoFactory::CreateOption()
{
	char option_type = GetOptionType();
	std::cout << "Creating option" << '\n';

	switch (option_type)
	{
	case 'c':
		return new EuroCallOption(*this);
		break;

	default:
		throw std::invalid_argument("CreateOption: Bad character. Invalid option type");
	}
}

ModelBase* PseudoFactory::CreateModel()
{
	char p_type = input_->GetPtype();
	std::cout << "Creating model" << '\n';

	switch (p_type)
	{
	case 'g': return new GBMModel(*this);
		break;
	default: throw std::runtime_error("PseudoFactory::CreateModel:  Bad character");
	}
}

TermStructureBase* PseudoFactory::CreateTermStructure()
{
	char ts_type = input_->GetTermStructureType();
	std::cout << "Creating term structure" << '\n';

	switch (ts_type)
	{
	case 'f': return new FlatTermStructure(*this);
		break;

	default: throw std::invalid_argument("Invalid term structure type");
	}
}


ValuationMethodBase* PseudoFactory::CreateValuationMethod()
{
	char meth_type = input_->GetMethodType();
	std::cout << "Creating valuation method which is MC" << '\n';

	switch (meth_type)
	{
	case 'm': return new MCSimulation(*this);
		break;
	default: throw std::runtime_error("PseudoFactory::CreateMethod:  Bad character");
	}
}

ApplicationBase* PseudoFactory::CreateApplication()
{
	char app_type = input_->GetApplicationtype();
	std::cout << "Creating application" << '\n';

	switch (app_type)
	{
	case 'v': return new Valuation(*this);
		break;
	default: throw std::runtime_error("PseudoFactory::CreateApplication:  Bad character");
	}
}

RandomBase* PseudoFactory::CreateRandomBase()
{
	char gen_type = input_->GetRandomGeneratorType();
	std::cout << "Creating random" << '\n';

	switch (gen_type)
	{
	case 'm': return new RandomMersenneTwister(*this);
		break;
	default: throw std::runtime_error("PseudoFactory::CreateRandomBase:  Bad character");
	}
}
