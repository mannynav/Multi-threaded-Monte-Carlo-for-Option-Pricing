#pragma once

#ifndef INPUTH
#define INPUTH


class Input
{
public:

	Input();

	double GetS0() const { return s0_; }
	double GetRiskFreeRate() const { return risk_free_rate; }
	double GetVolatility() const { return volatility_; }

	double GetStrike() const { return strike_; }
	double GetExpiry() const { return expiry_; }

	long GetNumberOfPaths() const { return number_of_paths_; }
	long GetTotalNumberOfSteps() const { return total_number_steps_; }
	long GetNumThreads() const { return number_threads_; }

	double GetV0() const { return v0_; }
	double GetMeanReversion() const { return mean_reversion_; }
	double GetLongTermMean() const { return long_term_mean_; }
	double GetVolVol() const { return volatility_of_volatility_; }
	double GetCorrelation() const { return correlation_; }
	double GetPsiC() const { return PsiC; }

	double GetCorrelationXV() const { return correlationXV_; }
	double GetCorrelationXR() const { return correlation_XR_; }


	double GetVolatilityHW() const { return volatility_hw_; }
	double GetMeanReversionHW() const { return mean_reversion_hw_; }

	double GetJumpMean() const { return jump_mean_;}						
	double GetJumpVol() const { return jump_vol_; }
	double GetJumpIntensity() const { return jump_intensity; }

	double GetAdjustment() const{return adjustment_;}						
	double GetVolatilityDD() const{return volatility_dd_;}

	double GetC() const { return C_; }							
	double GetG() const { return G_; }	
	double GetM() const { return M_; }

	double GetAlphaSABR() const { return alpha_; }							
	double GetBetaSABR() const { return beta_; }
	double GetRhoSABR() const { return rho_; }
	double GetNuSABR() const { return nu_; }

	char GetModelType() const { return model_type_; }
	char GetOptionType() const { return option_type_; }
	char GetMethodType() const { return pricing_method_type_; }
	char GetTermStructureType() const { return term_structure_type_; }
	char GetApplicationType() const { return application_type_; }

	char GetBrownianMotionPathType() const { return brownian_path_type_; }
	double GetShift() const { return shift_for_drift_; }
	
	double GetSeed() const { return seed_; }
	char GetRandomGeneratorType() const {return random_generator_type_; }

	char GetGreekType() const { return greek_type_; }

	

private:
	double s0_{};
	double risk_free_rate{};
	double volatility_{};

	double strike_{};
	double expiry_{};

	long number_of_paths_{};
	long total_number_steps_{};
	long number_threads_{};
	double seed_{};

	double v0_{};							//Heston and Heston Hull-White model parameters
	double mean_reversion_{};
	double long_term_mean_{};
	double volatility_of_volatility_{};
	double correlation_{};
	double correlationXV_{};
	double correlation_XR_{};
	double PsiC{};

	double volatility_hw_{};				//Hull White parameters
	double mean_reversion_hw_{};

	double jump_mean_{};					//Merton parameters	
	double jump_vol_{};
	double jump_intensity{};

	double adjustment_{};					//Displaced Diffusion parameters
	double volatility_dd_{};

	double C_{};							//Variance Gamma parameters
	double G_{};
	double M_{};

	double alpha_{};						//SABR parameters
	double beta_{};
	double rho_{};
	double nu_{};

	char model_type_;						// process type
	char option_type_;						// option type
	char term_structure_type_;				// term structure type

	char brownian_path_type_;				// brownian path type
	double shift_for_drift_;

	char accumulator_type_;					// accumulator type
	char pricing_method_type_;				// method type
	char application_type_;					// application type
	char random_generator_type_;			// random generator type
	char greek_type_;						//type of greeks
};


# endif
