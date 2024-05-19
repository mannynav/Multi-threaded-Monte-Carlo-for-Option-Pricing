

#include "Input.h"
#include <iostream>
#include <ostream>

#include "AnalyticalFormulas.h"

Input::Input()
{
    s0_ = 100;
    r_ = 0.1;
    sig_ = 0.20;

    x_ = 0.004;
    T_ = 1;

    v0_ = 0.04;
    meanreversion_ = 0.5;
    ltmean_ = 0.04;
    volvol_ = 0.5;
    correlation_ = -0.9;

    corrXR_ = 0.5;
    corrXV_ = -0.8;

    lambda_ = 1.12;
    eta_ = 0.01;

    PsiC = 1.5;

    uJ_ = 0.05;
    sigmaJ_ = 0.2;
    lambdaJ_ = 0.10;

    aDD_ = 1.0;
    sigmaDD_ = 0.15;

    ThetaVG_ = -0.1436;
    BetaVg_ = 0.3;
    SigmaVG_ = 0.1213;

	alpha_ = 0.5;
	beta_ = 0.5;
	rho_ = 0.0;
	nu_ = 0.1;

    M_ = 10;
    N_ = 120;
    num_threads_ = 1;
    seed_ = 1;

    O_type_ = 'c';   	                    // c for call,  a for asian call, 1 for up-in call option, 2 for floating look back call

	P_type_ = 's';   	                    // g for gbm, h for heston sv, H for heston hull white, v for variance gamma. H is not implemented for more than 1 thread
											//m for merton model with fixed grid sampling, d for displaced diffusion, s for SABR model

    Brownian_Path_Type_ = 'p';               //p for plain brownian (All models), a for antithetic paths (GBM model), i for importance sampled path
    shift_for_drift_ = 0.0;                  //ONLY FOR IMPORTANCE SAMPLING


	T_type_ = 'f';   	                    // f for flat term structure, s for stochastic term structure

    meth_type_ = 'm';  	                    // p for plain MC

    app_type_ = 'v';   	                    // v for valuation application
			
    acc_type_ = 'p'; 	                    // p for plain accumulator

    generator_type_ = 'm';                  // m for mersenne twister

    greek_type_ = 'p';                      // p for path wise, l for likelihood ratio.

}