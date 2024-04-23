#pragma once

#ifndef InputH
#define InputH


class Input
{
public:
	Input();

	double GetS0() const { return s0_; }
	double Getr() const { return r_; }
	double Getsig() const { return sig_; }

	double GetX() const { return x_; }
	double GetT() const { return T_; }

	double GetV0() const { return v0_; }
	double GetMeanReversion() const { return meanreversion_; }
	double GetLtMean() const { return ltmean_; }
	double GetVolVol() const { return volvol_; }
	double GetCorrelation() const { return correlation_; }
	double GetPsiC() const { return PsiC; }

	long GetM() const { return M_; }
	long GetN() const { return N_; }
	long GetNumThreads() const { return num_threads_; }


	char GetPtype() const { return P_type_; }
	char GetOptionType() const { return O_type_; }
	char GetMethodType() const { return meth_type_; }
	char GetApplicationType() const { return app_type_; }
	char GetTermStructureType() const { return T_type_; }
	double GetSeed() const { return seed_; }

	char GetRandomGeneratorType() const {return generator_type_; }

	double GetBetaVG() const {return BetaVg_;}

	double GetThetaVG() const {return ThetaVG_;}

	double GetSigmaVG() const {return SigmaVG_;}

private:
	double s0_;
	double r_;
	double sig_;

	double x_;
	double T_;

	long M_; 
	long N_; 
	long num_threads_;
	double seed_;

	double v0_;
	double meanreversion_;
	double ltmean_;
	double volvol_;
	double correlation_;
	double PsiC;

	double BetaVg_{};
	double ThetaVG_{};
	double SigmaVG_{};

	char P_type_; // process type
	char O_type_; // option type
	char T_type_; // term structure type


	char acc_type_; // accumulator type
	char meth_type_; // method type
	char app_type_; // application type
	char generator_type_; // random generator type
};


#endif
