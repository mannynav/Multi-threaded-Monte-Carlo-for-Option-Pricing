# This application is a work in progress #

This is a multi-threaded Monte Carlo application for pricing plain vanilla and path-dependent European options. The models and options that are implemented will presented below. The Boost and Eigen libraries are used throughout, especially Eigen, to speed up certain computations.

# Models #
The models implemented are Geometric Brownian Motion, Variance Gamma, Heston Stochastic Volatility with the variance process being simulated with the Almost Exact scheme and the Heston Hull-White hybrid model with the variance process simulated with the Quadratic Exponential scheme, modified to work with the Hull-White discretization.

# Options #
The options implemented are the European Call options, Arithmetic Asian option.

# Greeks #
Delta, Vega and Gamma can be computed for the Euro call option and Delta can be computed for the Heston model as of now. 

# Term Structure # 
There are two term structure classes that inherit from a single base class. The flat term term structure is used for the GBM, VG and HSV models while the stochastic term structure is used for the Heston Hull-White hybrid model since the short rate will follow the Hull-White process and needs to be accumulated and used as the numeraire.

# Tests #
Tests are implemented using Google's unit testing framework. Google test and Google mock will be used where appropriate.



