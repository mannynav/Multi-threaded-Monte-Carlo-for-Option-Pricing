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

	GreekBase* CreateGreek();

	void SetInput(Input* inp){input_ = inp;}


	double GetS0() const;
	double Getr() const;
	double Getsig() const;

	double GetX() const;
	double GetT() const;

	long GetM() const;
	long GetN() const;
	long GetNumThreads() const;
	double GetSeed() const;

	double GetV0() const;
	double GetMeanReversion() const;
	double GetLtMean() const;
	double GetVolVol() const;
	double GetCorrelation() const;
	double GetPsiC() const;

	double GetCorrXR() const;
	double GetCorrXV() const;

	double GetEta() const;
	double GetLambda() const;

	char GetPType() const;
	char GetOptionType() const;

	double GetUJ() const;
	double GetSigmaJ() const;
	double GetLambdaJ() const;

	double GetADD() const;
	double GetSigmaDD() const;

	double GetBetaVG() const ;
	double GetThetaVG() const;
	double GetSigmaVG() const;

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