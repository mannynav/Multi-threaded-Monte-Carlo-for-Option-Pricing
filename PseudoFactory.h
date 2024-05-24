#pragma once

#ifndef PseudoFactoryH
#define PseudoFactoryH

#include "RandomBase.h"
#include <memory>

#include "PlainBrownianPath.h"

class OptionBase;
class ModelBase;
class TermStructureBase;
class BrownianMotionPathBase;

class ValuationMethodBase;
class ApplicationBase;
class AccumulatorBase;

class RandomBase;

class Input;
class Output;

class GreekBase;

class PseudoFactory
{

public:
	std::unique_ptr<ApplicationBase> CreateApplication();
	std::unique_ptr<ValuationMethodBase> CreateValuationMethod();

	std::unique_ptr<OptionBase> CreateOption();

	std::unique_ptr<ModelBase> CreateModel();

	std::unique_ptr<BrownianMotionPathBase> CreateBrownianMotionPath();

	std::unique_ptr<TermStructureBase> CreateTermStructure();

	std::unique_ptr<RandomBase> CreateRandomBase();

	std::unique_ptr<GreekBase> CreateGreek();
	//GreekBase* CreateGreek();

	void SetInput(Input* inp){input_ = inp;}


	double GetS0() const;
	double GetRiskFreeRate() const;
	double GetVolatility() const;

	double GetStrike() const;
	double GetExpiry() const;

	long GetNumberOfPaths() const;
	long GetNumberTotalSteps() const;
	long GetNumThreads() const;
	double GetSeed() const;

	double GetV0() const;
	double GetMeanReversion() const;
	double GetLongTermMean() const;
	double GetVolVol() const;
	double GetCorrelation() const;
	double GetPsiC() const;

	double GetCorrXR() const;
	double GetCorrXV() const;

	double GetVolatilityHW() const;
	double GetMeanReversionHW() const;

	char GetMType() const;
	char GetOType() const;

	double GetJumpMean() const;
	double GetJumpVol() const;
	double GetJumpIntensity() const;

	double GetAdjustment() const;
	double GetVolatilityDD() const;

	double GetCVG() const ;
	double GetGVG() const;
	double GetMVG() const;

	double GetAlphaSABR() const;
	double GetBetaSABR() const;
	double GetRhoSABR() const;
	double GetNuSABR() const;

	double GetShift() const;

	char GetGreekType() const;

private:

	Input* input_ = nullptr;

};


#endif