

#include "Input.h"
#include <iostream>
#include <ostream>
#include "AnalyticalFormulas.h"

Input::Input()
{
    s0_ = 100;
    r_ = 0.03;
    sig_ = 0.30;

    x_ = 100;
    T_ = 1;

    v0_ = 0.02;
    meanreversion_ = 0.5;
    ltmean_ = 0.05;
    volvol_ = 0.3;
    correlation_ = -0.9;

    corrXR_ = 0.5;
    corrXV_ = -0.8;

    lambda_ = 1.12;
    eta_ = 0.01;

    PsiC = 1.5;

    uJ_ = 0.1;
    sigmaJ_ = 0.2;
    lambdaJ_ = 1.7913;

    aDD_ = 5;
    sigmaDD_ = 0.2;

    C_VG_ = 18.0968;
    G_VG_ = 20.0276;
    M_VG_ = 26.3971;

	alpha_ = 0.2;
	beta_ = 0.5;
    rho_ = 0.0;
	nu_ = 0.3;

    M_ = 1500000;
    N_ = 100;
    num_threads_ = 3;
    seed_ = 1;

    std::cout << AnalyticalFormulas::Black_Scholes_Call(s0_, x_, T_, r_, sig_) << std::endl;

    O_type_ = 'c';   	                    // c for call,  a for asian call, 1 for up-in call option, 2 for floating lookback call, 3 fixed lookback call

	P_type_ = 'g';   	                    // g for gbm, 
                                            //h for heston sv, H for heston hull-white, 
                                            //v for variance gamma, m for merton model with fixed grid sampling, 
                                            //d for displaced diffusion, s for SABR model

    Brownian_Path_Type_ = 'p';               //p for plain brownian (All models), a for antithetic paths (GBM model), i for importance sampled path
    shift_for_drift_ = 0.0;                  //ONLY FOR IMPORTANCE SAMPLING


	T_type_ = 'f';   	                    // f for flat term structure, s for stochastic term structure

    meth_type_ = 'm';  	                    // p for plain MC

    app_type_ = 'v';   	                    // v for valuation application
			
    acc_type_ = 'p'; 	                    // p for plain accumulator

    generator_type_ = 'm';                  // m for mersenne twister

    greek_type_ = 'p';                      // p for pathwise, l for likelihood ratio.

}