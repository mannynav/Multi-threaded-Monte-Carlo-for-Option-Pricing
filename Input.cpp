

#include "Input.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	interface
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Input::Input()
{

    S_0_ = 100;
    r_ = 0.05;
    sig_ = 0.20;

    X_ = 100;
    T_ = 1;

    M_ = 1000000;
    N_ = 100;
    num_threads_ = 16;

    O_type_ = 'c';   	// c for call,  p  for put
    P_type_ = 'g';   	// g for gbm
    T_type_ = 'f';   	// f for flat term structure
    Meth_type_ = 'm';  	// p for plain MC
    app_type_ = 'v';   	// v for valuation application

    Acc_type_ = 'p'; 	// p for plain accumulator

}