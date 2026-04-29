# This application is a work in progress #

This is a multi-threaded Monte Carlo application for pricing plain vanilla and path-dependent European options. The models and options that are implemented will presented below. The Boost and Eigen libraries are used throughout, especially Eigen, to speed up vector computations.

# Models #
The models implemented are Geometric Brownian Motion, Variance Gamma, Merton, Heston, Heston Hull-White, Displaced Diffusion and SABR. The Heston is implemented with the Almost Exact scheme and the Heston Hull-White hybrid model is implemented with the Quadratic Exponential scheme, modified to work with the Hull-White Euler-discretization.

# Options #
The options implemented are a plain call ption, arithmetic Asian call, up-In-call, fixed and floating lookBack calls, and double barrier knock-in call. All of the options are of European type.

# Greeks #
Greeks calculations are not currently implemented but the structure is there for them, specifically using the pathwise and likelihood ratio methods for delta, vega and gamma of plain Euro call options. Computations using the proxy method will be implemented in due time.

# Term Structure # 
There are two term structure classes that inherit from a single base class. The flat term term structure is used for the GBM, VG and HSV models while the stochastic term structure is used for the Heston Hull-White hybrid model since the short rate will follow the Hull-White process and needs to be accumulated and used for discounting.

# Tests #
Tests are currently implemented only for the option payoffs using Boost test. Test Driven Development will be used for any new option payoffs.



