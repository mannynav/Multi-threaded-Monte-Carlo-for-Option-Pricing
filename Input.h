#pragma once

#ifndef InputH
#define InputH


class Input
{
public:
    Input();

    double GetS0() const { return S_0_; }
    double Getr() const { return r_; }
    double Getsig() const { return sig_; }
    char GetPtype() const { return P_type_; }

    double GetX() const { return X_; }
    double GetT() const { return T_; }
    char GetOptionType() const { return O_type_; }

    long GetM() const { return M_; }
    long GetN() const { return N_; }
    long GetNumThreads() const { return num_threads_; }


    char GetMethodType() const { return Meth_type_; }
    char GetApplicationtype() const { return app_type_; }
    char GetTermStructureType() const { return T_type_; }
    

private:
    char P_type_;   	// process type
    double S_0_;
    double r_;
    double sig_;

    char O_type_;  	 	// option type
    double X_;
    double T_;

    char T_type_;   	// term structure type

    long M_;     		// number of sample paths
    long N_;     		// number of time steps
    long num_threads_;  // number of threads

    char Acc_type_;		// accumulator type
    char Meth_type_;   	// method type
    char app_type_;    	// application type

  
};













#endif 