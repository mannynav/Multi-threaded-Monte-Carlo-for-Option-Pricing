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

	long GetM() const { return M_; }
	long GetN() const { return N_; }
	long GetNumThreads() const { return num_threads_; }


	double GetV0() const { return v0_; }
	double GetMeanReversion() const { return meanreversion_; }
	double GetLtMean() const { return ltmean_; }
	double GetVolVol() const { return volvol_; }
	double GetCorrelation() const { return correlation_; }
	double GetPsiC() const { return PsiC; }

	double GetCorrXV() const { return corrXV_; }
	double GetCorrXR() const { return corrXR_; }


	double GetEta() const { return eta_; }
	double GetLambda() const { return lambda_; }

	double GetUJ() const { return uJ_;}						//Merton Model Parameters
	double GetSigmaJ() const { return sigmaJ_; }
	double GetLambdaJ() const { return lambdaJ_; }

	double GetADD() const{return aDD_;}

	double GetSigmaDD() const{return sigmaDD_;}

	double GetBetaVG() const { return BetaVg_; }			//Variance Gamma model parameters
	double GetThetaVG() const { return ThetaVG_; }
	double GetSigmaVG() const { return SigmaVG_; }

	double GetAlphaSABR() const { return alpha_; }			//SABR model parameters
	double GetBetaSABR() const { return beta_; }
	double GetRhoSABR() const { return rho_; }
	double GetNuSABR() const { return nu_; }

	char GetPtype() const { return P_type_; }
	char GetOptionType() const { return O_type_; }
	char GetMethodType() const { return meth_type_; }
	char GetTermStructureType() const { return T_type_; }
	char GetApplicationType() const { return app_type_; }

	char GetBrownianMotionPathType() const { return Brownian_Path_Type_; }
	double GetShift() const { return shift_for_drift_; }
	

	double GetSeed() const { return seed_; }
	char GetRandomGeneratorType() const {return generator_type_; }

	char GetGreekType() const { return greek_type_; }

	

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

	double v0_;					//Heston and Heston Hull-White model parameters
	double meanreversion_;
	double ltmean_;
	double volvol_;
	double correlation_;
	double corrXV_;
	double corrXR_;
	double PsiC;

	double eta_;				//Hull White parameters
	double lambda_;

	double uJ_{};				//Merton parameters	
	double sigmaJ_{};
	double lambdaJ_{};

	double aDD_{};				//Displaced Diffusion parameters
	double sigmaDD_{};

	double BetaVg_{};			//Variance Gamma parameters
	double ThetaVG_{};
	double SigmaVG_{};

	double alpha_{};			//SABR parameters
	double beta_{};
	double rho_{};
	double nu_{};

	char P_type_;				// process type
	char O_type_; // option type
	char T_type_; // term structure type

	char Brownian_Path_Type_;
	double shift_for_drift_;

	char acc_type_; // accumulator type
	char meth_type_; // method type
	char app_type_; // application type
	char generator_type_; // random generator type
	char greek_type_;  //type of greeks
};


#endif
