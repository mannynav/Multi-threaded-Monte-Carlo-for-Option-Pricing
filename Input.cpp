
#include "Input.h"
#include <iostream>
#include <ostream>
#include "AnalyticalFormulas.h"

Input::Input()
{
    s0_ = 0.2;                             
    risk_free_rate = 0.0;     

    strike_ = 0.2;                          // Strike price
    expiry_ = 2;                            // Time to expiry

    lower_barrier_ = 90;                    // Double Barrier parameters
    upper_barrier_ = 110;

    volatility_ = 0.30;                     // Geometric Brownian Motion parameter

    v0_ = 0.02;                             // Heston model parameters
    mean_reversion_ = 0.5;
    long_term_mean_ = 0.05;
    volatility_of_volatility_ = 0.3;
    correlation_ = -0.9;

    correlation_XR_ = 0.5;                  // Correlations for Heston Hull-White
    correlationXV_ = -0.8;

    mean_reversion_hw_ = 1.12;              // Hull-White parameters
    volatility_hw_ = 0.01;

    PsiC = 1.5;					            //Switching parameter for Heston QE scheme

    jump_mean_ = 0.1;			            // Merton parameters
    jump_vol_ = 0.2;
    jump_intensity = 1.7913;

    adjustment_ = 5;			            // Displaced Diffusion parameters 
    volatility_dd_ = 0.2;

    C_ = 18.0968;                           // Variance Gamma parameters using CGM representation
    G_ = 20.0276;
    M_ = 26.3971;

	alpha_ = 0.2;				            // SABR parameters
	beta_ = 0.5;
    rho_ = 0.0;
	nu_ = 0.2;

    number_of_paths_ = 10;                  // Monte Carlo parameters
    total_number_steps_ = 10;
    number_threads_ = 1;
    seed_ = 1;

    option_type_ = 'c';   	                // c - for call,
                                            // a - for asian call, 
                                            // 1 - up-in call option, 
                                            // 2 - floating look back call, 
                                            // 3 - fixed look back call
											// 4 - double barrier knock in call

	model_type_ = 'g';   	                // g for gbm, 
                                            // h for heston sv, H for heston hull-white, 
                                            // v for variance gamma, m for merton model with fixed grid sampling, 
                                            // d for displaced diffusion, s for SABR model

    brownian_path_type_ = 'p';               //p for plain brownian (All models), a for antithetic paths (GBM model)
    shift_for_drift_ = 0.0;                  //ONLY FOR IMPORTANCE SAMPLING


	term_structure_type_ = 'f';   	         // f for flat term structure, s for stochastic term structure

    pricing_method_type_ = 'm';  	         // p for plain MC

    application_type_ = 'v';   	             // v for valuation application
			
    accumulator_type_ = 'p'; 	             // p for plain accumulator

    random_generator_type_ = 'm';            // m for mersenne twister

    greek_type_ = 'p';                       // p for pathwise, l for likelihood ratio.

    double sabrIV = AnalyticalFormulas::ImpliedVolatilitySABR(0.3, 0.2, 2, 0.2, 0.5, 0.2, 0);
    std::cout << sabrIV << '\n';
    std::cout << AnalyticalFormulas::Black_Scholes_Call(s0_, strike_, expiry_, risk_free_rate, volatility_) << '\n';


}