

#include "Input.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	interface
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Input::Input()
{

    s0_ = 100;
    r_ = 0.1;
    sig_ = 0.30;

    x_ = 100;
    T_ = 1;

    v0_ = 0.04;
    meanreversion_ = 0.5;
    ltmean_ = 0.04;
    volvol_ = 1.0;
    correlation_ = -0.9;

    PsiC = 1.5;

    ThetaVG_ = -0.1436;
    BetaVg_ = 0.3;
    SigmaVG_ = 0.1213;

    M_ = 1000000;
    N_ = 100;
    num_threads_ = 16;
    seed_ = 1;

    O_type_ = 'c';   	                    // c for call,  a for asian call

    P_type_ = 'h';   	                    // g for gbm, h for heston sv, v for variance gamma

    //Heston_Discretization_Type = 'a';       // a for almost exact scheme, q for quadratic exponential scheme

    T_type_ = 'f';   	                    // f for flat term structure

    meth_type_ = 'm';  	                    // p for plain MC

    app_type_ = 'v';   	                    // v for valuation application
			
    acc_type_ = 'p'; 	                    // p for plain accumulator

    generator_type_ = 'm';                  // m for mersenne twister

}