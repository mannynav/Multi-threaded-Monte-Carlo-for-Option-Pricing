#pragma once

#ifndef PseudoFactoryH
#define PseudoFactoryH

class OptionBase;
class ModelBase;
class TermStructureBase;

class ValuationMethodBase;
class ApplicationBase;
class AccumulatorBase;

class Input;
class Output;

class PseudoFactory
{

public:

	ApplicationBase* CreateApplication(); //gets called in application wrapper. return Valuation class
	OptionBase* CreateOption();
	ModelBase* CreateModel();
	TermStructureBase* CreateTermStructure();
	ValuationMethodBase* CreateValuationMethod();
	


	void SetInput(Input* inp) { input_ = inp; }
	void SetOutput(Output* out) { output_ = out; }

	Output* GetOutput() const { return output_; }


	double GetS0() const;
	double Getr() const;
	double Getsig() const;
	char GetPtype() const;

	double GetX() const;
	double GetT() const;
	char GetOptionType() const;

	long GetM() const;
	long GetN() const;
	long GetNumThreads() const;

private:

	Input* input_ = nullptr;
	Output* output_ = nullptr;

};


#endif