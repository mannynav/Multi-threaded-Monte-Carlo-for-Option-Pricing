

#include "Input.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	interface
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Input::Input()
{

    s0_ = 100.0;
    r_ = 0.1;
    sig_ = 0.20;

    x_ = 100;
    T_ = 10;

    v0_ = 0.02;
    meanreversion_ = 0.5;
    ltmean_ = 0.04;
    volvol_ = 0.3;
    correlation_ = -0.9;

    corrXR_ = 0.5;
    corrXV_ = -0.8;

    lambda_ = 1.12;
    eta_ = 0.01;

    PsiC = 1.5;

    ThetaVG_ = -0.1436;
    BetaVg_ = 0.3;
    SigmaVG_ = 0.1213;

    M_ = 1000000;
    N_ = 15 ;
    num_threads_ = 1;
    seed_ = 1;

    O_type_ = 'c';   	                    // c for call,  a for asian call

    P_type_ = 'H';   	                    // g for gbm, h for heston sv, H for heston hull white, v for variance gamma

    Brownian_Path_Type_ = 'p';               //p for plain brownian, a for antithetic paths, i for importance sampled path
    shift_for_drift_ = 0.0;                  //ONLY FOR IMPORTANCE SAMPLING


    //Heston_Discretization_Type = 'a';       // a for almost exact scheme, q for quadratic exponential scheme

    T_type_ = 'f';   	                    // f for flat term structure

    meth_type_ = 'm';  	                    // p for plain MC

    app_type_ = 'v';   	                    // v for valuation application
			
    acc_type_ = 'p'; 	                    // p for plain accumulator

    generator_type_ = 'm';                  // m for mersenne twister

}