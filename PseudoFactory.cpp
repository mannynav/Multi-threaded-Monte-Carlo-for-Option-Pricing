#include "PseudoFactory.h"

#include "Input.h"

#include "ApplicationBase.h"
#include "Valuation.h"

#include "ValuationMethodBase.h"
#include "MCSimulation.h"


#include "OptionBase.h"
#include "EuroCallOption.h"
#include "AsianCallOption.h"
#include "EuroUpInCallOption.h"
#include "FloatingLookBackCall.h"

#include "ModelBase.h"
#include "GBMModel.h"
#include "HestonModel.h"
#include "HestonHullWhiteModel.h"
#include "VarianceGammaModel.h"
#include "MertonModel.h"
#include "DisplacedDiffusionModel.h"
#include "SABRModel.h"

#include "TermStructureBase.h"
#include "FlatTermStructure.h"
#include "StochasticTermStructure.h"

#include "RandomBase.h"

#include "GreekBase.h"
#include "PathwiseGreeks.h"
//#include "LikelihoodRatioGreeks.h"

#include <stdexcept>


#include "AntitheticPath.h"
#include "PlainBrownianPath.h"
#include "ImportanceSampledPath.h"

#include "RandomMersenneTwister.h"


double PseudoFactory::GetS0() const { return input_->GetS0(); }
double PseudoFactory::Getr() const { return input_->Getr(); }
double PseudoFactory::Getsig() const { return input_->Getsig(); }

double PseudoFactory::GetX() const { return input_->GetX(); }
double PseudoFactory::GetT() const { return input_->GetT(); }

long PseudoFactory::GetM() const { return input_->GetM(); }
long PseudoFactory::GetN() const { return input_->GetN(); }
long PseudoFactory::GetNumThreads() const { return input_->GetNumThreads(); }
double PseudoFactory::GetSeed() const {return input_->GetSeed();}

double PseudoFactory::GetV0() const { return input_->GetV0(); }
double PseudoFactory::GetMeanReversion() const { return input_->GetMeanReversion(); }
double PseudoFactory::GetLtMean() const { return input_->GetLtMean(); }
double PseudoFactory::GetVolVol() const { return input_->GetVolVol(); } 
double PseudoFactory::GetCorrelation() const { return input_->GetCorrelation(); }
double PseudoFactory::GetPsiC() const { return input_->GetPsiC(); }

double PseudoFactory::GetCorrXR() const { return input_->GetCorrXR(); }
double PseudoFactory::GetCorrXV() const { return input_->GetCorrXV(); }

double PseudoFactory::GetEta() const { return input_->GetEta(); }
double PseudoFactory::GetLambda() const{ return input_->GetLambda();}

double PseudoFactory::GetADD() const { return input_->GetADD(); }
double PseudoFactory::GetSigmaDD() const { return input_->GetSigmaDD(); }

double PseudoFactory::GetBetaVG() const {return input_->GetBetaVG(); }
double PseudoFactory::GetSigmaVG() const { return input_->GetSigmaVG(); }
double PseudoFactory::GetShift() const { return input_->GetShift(); }
double PseudoFactory::GetThetaVG() const{ return input_->GetThetaVG(); }

double PseudoFactory::GetAlphaSABR() const { return input_->GetAlphaSABR(); }
double PseudoFactory::GetBetaSABR() const { return input_->GetBetaSABR(); }
double PseudoFactory::GetRhoSABR() const { return input_->GetRhoSABR(); }
double PseudoFactory::GetNuSABR() const { return input_->GetNuSABR(); }

double PseudoFactory::GetUJ() const { return input_->GetUJ(); }
double PseudoFactory::GetSigmaJ() const { return input_->GetSigmaJ(); }
double PseudoFactory::GetLambdaJ() const { return input_->GetLambdaJ(); }


char PseudoFactory::GetPType() const { return input_->GetPtype(); }
char PseudoFactory::GetOptionType() const { return input_->GetOptionType(); }
char PseudoFactory::GetGreekType() const{return input_->GetGreekType(); }


std::unique_ptr<OptionBase> PseudoFactory::CreateOption()
{
	char option_type = GetOptionType();
	std::cout << "Creating option" << '\n';

	switch (option_type)
	{
	case 'c':
		return std::make_unique<EuroCallOption>(*this);
	case 'a':
		return std::make_unique<AsianCallOption>(*this);
	case '1':
		return std::make_unique<EuroUpInCallOption>(*this);

	default:
		throw std::invalid_argument("CreateOption: Bad character. Invalid option type");
	}
}

std::unique_ptr<ModelBase> PseudoFactory::CreateModel()
{
	char p_type = input_->GetPtype();
	std::cout << "Creating model" << '\n';

	switch (p_type)
	{
	case 'g':
		return std::make_unique<GBMModel>(*this);
	case 'h':
		return std::make_unique<HestonModel>(*this);
	case 'v':
		return std::make_unique<VarianceGammaModel>(*this);
	case 'H':
		return std::make_unique<HestonHullWhiteModel>(*this);
	case 'm':
		return std::make_unique<MertonModel>(*this);
	case 'd':
		return std::make_unique<DisplacedDiffusionModel>(*this);
	case 's':
		return std::make_unique<SABRModel>(*this);

	default: throw std::runtime_error("PseudoFactory::CreateModel:  Bad character");
	}
}

std::unique_ptr<BrownianMotionPathBase> PseudoFactory::CreateBrownianMotionPath()
{
	char type = input_->GetBrownianMotionPathType();

	std::cout << "Creating Brownian Path Object" << std::endl;

	switch(type)
	{
	case 'p':
		return std::make_unique<PlainBrownianPath>();
	case 'a':
		return std::make_unique<AntitheticPath>(*this);

	default: throw std::runtime_error("PseudoFactory::CreateModel:  Bad character");
	}
}

std::unique_ptr<TermStructureBase> PseudoFactory::CreateTermStructure()
{
	char ts_type = input_->GetTermStructureType();
	std::cout << "Creating term structure" << '\n';

	switch (ts_type)
	{
	case 'f':
		return std::make_unique<FlatTermStructure>(*this);

	case 's':
		return std::make_unique<StochasticTermStructure>(*this);

	default: throw std::invalid_argument("Invalid term structure type");
	}
}

std::unique_ptr<ValuationMethodBase> PseudoFactory::CreateValuationMethod()
{
	char meth_type = input_->GetMethodType();
	std::cout << "Creating valuation method which is MC" << '\n';

	switch (meth_type)
	{
	case 'm': 
		return std::make_unique<MCSimulation>(*this);
	default: throw std::runtime_error("PseudoFactory::CreateMethod:  Bad character");
	}
}

std::unique_ptr<ApplicationBase> PseudoFactory::CreateApplication()
{
	char app_type = input_->GetApplicationType();
	std::cout << "Creating application" << '\n';

	switch (app_type)
	{
	case 'v':
		return std::make_unique<Valuation>(*this);

	default: throw std::runtime_error("PseudoFactory::CreateApplication:  Bad character");
	}
}

std::unique_ptr<RandomBase> PseudoFactory::CreateRandomBase()
{
	char gen_type = input_->GetRandomGeneratorType();
	std::cout << "Creating random" << '\n';

	switch(gen_type)
	{
	case 'm': 
		return std::make_unique<RandomMersenneTwister>(*this);

	default: throw std::runtime_error("PseudoFactory::CreateRandomBase:  Bad character");
	}
}

GreekBase* PseudoFactory::CreateGreek()
{
	char greek_type = input_->GetGreekType();

	switch(greek_type)
	{
	case 'p':
		return new PathwiseGreeks(*this);

	default: throw std::runtime_error("PseudoFactory::CreateGreek:  Bad character");
	}
}
