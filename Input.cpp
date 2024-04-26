

#include "Input.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	interface
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Input::Input()
{

    s0_ = 1;
    r_ = 0.06;
    sig_ = 0.30;

    x_ = 0.9;
    T_ = 1;

    v0_ = 0.010201;
    meanreversion_ = 6.21;
    ltmean_ = 0.019;
    volvol_ = 0.61;
    correlation_ = -0.70;
    PsiC = 1.5;

    ThetaVG_ = -0.1436;
    BetaVg_ = 0.3;
    SigmaVG_ = 0.1213;

    M_ = 20000;
    N_ = 100;
    num_threads_ = 1;
    seed_ = 1;

    O_type_ = 'c';   	// c for call,  a for asian call

    P_type_ = 'g';   	// g for gbm, h for heston sv, v for variance gamma

    T_type_ = 'f';   	// f for flat term structure

    meth_type_ = 'm';  	// p for plain MC

    app_type_ = 'v';   	// v for valuation application

    acc_type_ = 'p'; 	// p for plain accumulator
    generator_type_ = 'm'; // m for mersenne twister

}