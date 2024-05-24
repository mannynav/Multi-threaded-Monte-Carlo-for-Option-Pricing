#include "PseudoFactory.h"
#include <stdexcept>

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
#include "FixedLookBackCall.h"

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

#include "GreekBase.h"
#include "PathwiseGreeks.h"

#include "AntitheticPath.h"
#include "PlainBrownianPath.h"
#include "ImportanceSampledPath.h"

#include "RandomBase.h"
#include "RandomMersenneTwister.h"


double PseudoFactory::GetS0() const { return input_->GetS0(); }
double PseudoFactory::GetRiskFreeRate() const { return input_->GetRiskFreeRate(); }
double PseudoFactory::GetVolatility() const { return input_->GetVolatility(); }

double PseudoFactory::GetStrike() const { return input_->GetStrike(); }
double PseudoFactory::GetExpiry() const { return input_->GetExpiry(); }

long PseudoFactory::GetNumberOfPaths() const { return input_->GetNumberOfPaths(); }
long PseudoFactory::GetNumberTotalSteps() const { return input_->GetTotalNumberOfSteps(); }
long PseudoFactory::GetNumThreads() const { return input_->GetNumThreads(); }
double PseudoFactory::GetSeed() const {return input_->GetSeed();}

double PseudoFactory::GetV0() const { return input_->GetV0(); }
double PseudoFactory::GetMeanReversion() const { return input_->GetMeanReversion(); }
double PseudoFactory::GetLongTermMean() const { return input_->GetLongTermMean(); }
double PseudoFactory::GetVolVol() const { return input_->GetVolVol(); } 
double PseudoFactory::GetCorrelation() const { return input_->GetCorrelation(); }
double PseudoFactory::GetPsiC() const { return input_->GetPsiC(); }

double PseudoFactory::GetCorrXR() const { return input_->GetCorrelationXR(); }
double PseudoFactory::GetCorrXV() const { return input_->GetCorrelationXV(); }

double PseudoFactory::GetVolatilityHW() const { return input_->GetVolatilityHW(); }
double PseudoFactory::GetMeanReversionHW() const{ return input_->GetMeanReversionHW();}

double PseudoFactory::GetAdjustment() const { return input_->GetAdjustment(); }
double PseudoFactory::GetVolatilityDD() const { return input_->GetVolatilityDD(); }

double PseudoFactory::GetCVG() const {return input_->GetC(); }
double PseudoFactory::GetGVG() const { return input_->GetG(); }
double PseudoFactory::GetMVG() const { return input_->GetNumberOfPaths(); }

double PseudoFactory::GetShift() const { return input_->GetShift(); }

double PseudoFactory::GetAlphaSABR() const { return input_->GetAlphaSABR(); }
double PseudoFactory::GetBetaSABR() const { return input_->GetBetaSABR(); }
double PseudoFactory::GetRhoSABR() const { return input_->GetRhoSABR(); }
double PseudoFactory::GetNuSABR() const { return input_->GetNuSABR(); }

double PseudoFactory::GetJumpMean() const { return input_->GetJumpMean(); }
double PseudoFactory::GetJumpVol() const { return input_->GetJumpVol(); }
double PseudoFactory::GetJumpIntensity() const { return input_->GetJumpIntensity(); }


char PseudoFactory::GetMType() const { return input_->GetModelType(); }
char PseudoFactory::GetOType() const { return input_->GetOptionType(); }
char PseudoFactory::GetGreekType() const{return input_->GetGreekType(); }


std::unique_ptr<OptionBase> PseudoFactory::CreateOption()
{
	char option_type = input_->GetOptionType();

	switch (option_type)
	{
	case 'c':
		return std::make_unique<EuroCallOption>(*this);
	case 'a':
		return std::make_unique<AsianCallOption>(*this);
	case '1':
		return std::make_unique<EuroUpInCallOption>(*this);
	case '2':
		return std::make_unique<FloatingLookBackCallOption>(*this);
	case '3':
			return std::make_unique<FixedLookBackCallOption>(*this);
	default:
		throw std::invalid_argument("CreateOption: Bad character. Invalid option type");
	}
}

std::unique_ptr<ModelBase> PseudoFactory::CreateModel()
{
	char p_type = input_->GetModelType();

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

	switch(type)
	{
	case 'p':
		return std::make_unique<PlainBrownianPath>();
	case 'a':
		return std::make_unique<AntitheticPath>(*this);

	default: throw std::runtime_error("PseudoFactory::CreateModel: Bad character");
	}
}

std::unique_ptr<TermStructureBase> PseudoFactory::CreateTermStructure()
{
	char ts_type = input_->GetTermStructureType();

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

	switch(gen_type)
	{
	case 'm': 
		return std::make_unique<RandomMersenneTwister>(*this);

	default: throw std::runtime_error("PseudoFactory::CreateRandomBase:  Bad character");
	}
}

std::unique_ptr<GreekBase> PseudoFactory::CreateGreek()
{
	char greek_type = input_->GetGreekType();

	switch(greek_type)
	{
	case 'p':
		return std::make_unique<PathwiseGreeks>(*this);
		//return new PathwiseGreeks(*this);

	default: throw std::runtime_error("PseudoFactory::CreateGreek:  Bad character");
	}
}
