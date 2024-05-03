# This application is a work in progress #

This is a multi-threaded Monte Carlo application for pricing plain vanilla and path-dependent European options. The models and options that are implemented will presented below. The Boost and Eigen libraries are used throughout, especially Eigen, to speed up vector computations.

# Models #
The models implemented are Geometric Brownian Motion, Variance Gamma, Heston Stochastic Volatility with the variance process being simulated with the Almost Exact scheme and the Heston Hull-White hybrid model with the variance process simulated with the Quadratic Exponential scheme, modified to work with the Hull-White discretization.

# Options #
The options implemented are a Euro call option and arithmetic asian option.

# Greeks #
Delta, vega and gamma can be computed for the Euro call option and Delta can be computed for the Heston model as of now. The pathwise method is used for the calculation of the delta and vega and a mixture of the likelihood ratio and pathwise method is used for the calculation of gamma. For the Euro call, these greeks have been checked with the formulas for the appropriate greeks. While the Delta for the Heston model has been checked against those in literature for plain call option.

# Term Structure # 
There are two term structure classes that inherit from a single base class. The flat term term structure is used for the GBM, VG and HSV models while the stochastic term structure is used for the Heston Hull-White hybrid model since the short rate will follow the Hull-White process and needs to be accumulated and used as the numeraire.

# Tests #
Tests are implemented using Google's unit testing framework. Google test and Google mock will be used where appropriate.



