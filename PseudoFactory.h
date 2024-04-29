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

class PseudoFactory
{

public:
	std::unique_ptr<ApplicationBase> CreateApplication();
	std::unique_ptr<ValuationMethodBase> CreateValuationMethod();

	std::unique_ptr<OptionBase> CreateOption();

	std::unique_ptr<ModelBase> CreateModel();
	BrownianMotionPathBase* CreateBrownianMotionPath();

	std::unique_ptr<TermStructureBase> CreateTermStructure();

	RandomBase* CreateRandomBase();

	void SetInput(Input* inp){input_ = inp;}
	void SetOutput(Output* out) { output_ = out; }

	Output* GetOutput() const { return output_; }


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

	double GetBetaVG() const ;
	double GetThetaVG() const;
	double GetSigmaVG() const;

	double GetShift() const;

private:

	Input* input_ = nullptr;
	Output* output_ = nullptr;

};


#endif