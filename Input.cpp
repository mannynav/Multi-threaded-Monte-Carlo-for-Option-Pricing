

#include "Input.h"

#include <iostream>
#include <ostream>

#include "AnalyticalFormulas.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	interface
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Input::Input()
{

    s0_ = 100.0;
    r_ = 0.1;
    sig_ = 0.20;

    x_ = 100.0;
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

    ThetaVG_ = -0.1436;
    BetaVg_ = 0.3;
    SigmaVG_ = 0.1213;

    M_ = 10;
    N_ = 100;
    num_threads_ = 1;
    seed_ = 1;


    std::cout << "BS Call:" << AnalyticalFormulas::Black_Scholes_Call(s0_, x_, T_, r_, sig_) << '\n';
    std::cout << "BS Delta:" << AnalyticalFormulas::delta(s0_, x_, r_, sig_, T_, true) << '\n';
    std::cout << "BS Vega:" << AnalyticalFormulas::vega(s0_, x_, r_, sig_, T_) << '\n';
    std::cout << "BS gamma:" << AnalyticalFormulas::gamma(s0_, x_, r_, sig_, T_) << '\n';



    O_type_ = 'c';   	                    // c for call,  a for asian call, 1 for up-in call option, 2 for floating look back call

	P_type_ = 'g';   	                    // g for gbm, h for heston sv, H for heston hull white, v for variance gamma. H is not implemented for more than 1 thread

    Brownian_Path_Type_ = 'p';               //p for plain brownian (All models), a for antithetic paths (GBM model), i for importance sampled path
    shift_for_drift_ = 0.0;                  //ONLY FOR IMPORTANCE SAMPLING


	T_type_ = 'f';   	                    // f for flat term structure, s for stochastic term structure

    meth_type_ = 'm';  	                    // p for plain MC

    app_type_ = 'v';   	                    // v for valuation application
			
    acc_type_ = 'p'; 	                    // p for plain accumulator

    generator_type_ = 'm';                  // m for mersenne twister

    greek_type_ = 'p';                      // p for path wise, l for likelihood ratio.

}