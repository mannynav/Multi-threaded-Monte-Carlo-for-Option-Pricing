#include "rv.h"

boost::mt19937 rng;

double RandomVariableStatisticalFunctions::normVariate()
{

    boost::normal_distribution<> nd(0.0, 1.0);

    boost::variate_generator<boost::mt19937&, boost::normal_distribution<> >
		rnorm(rng, nd);

    return rnorm();
}

double RandomVariableStatisticalFunctions::rand_uniform()
{
    boost::uniform_real<> uni(0.0, 1.0);

    boost::variate_generator<boost::mt19937&, boost::uniform_real<> >
        uniRng(rng, uni);

    return uniRng();

}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// double ltqnorm(double p)
// Lower tail quantile for standard normal distribution function.
//
// This function returns an approximation of the inverse cumulative
// standard normal distribution function.  I.e., given P, it returns
// an approximation to the X satisfying P = Pr{Z <= X} where Z is a
// random variable from the standard normal distribution.
//
// The algorithm uses a minimax approximation by rational functions
// and the result has a relative error whose absolute value is less
// than 1.15e-9.
//
// Author:      Peter J. Acklam
// Time-stamp:  2002-06-09 18:45:44 +0200
// E-mail:      jacklam@math.uio.no
// WWW URL:     http://www.math.uio.no/~jacklam
//
// C implementation adapted from Peter's Perl version
//
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double RandomVariableStatisticalFunctions::inverseQNorm(double p, int err)
{

    static const double XINF = 1.79769313486231E+308; 	//Machine dependent constants

    static const double LOW = 0.02425;
    static const double HIGH = 0.97575;

    static const int ERR_DOM = 1;
    static const int ERR_RANGE = 2;

    err = 0;

    /* Coefficients in rational approximations. */

    static const double a[] =
    {
        -3.969683028665376e+01,
        2.209460984245205e+02,
        -2.759285104469687e+02,
        1.383577518672690e+02,
        -3.066479806614716e+01,
        2.506628277459239e+00
    };

    static const double b[] =
    {
        -5.447609879822406e+01,
        1.615858368580409e+02,
        -1.556989798598866e+02,
        6.680131188771972e+01,
        -1.328068155288572e+01
    };

    static const double c[] =
    {
        -7.784894002430293e-03,
        -3.223964580411365e-01,
        -2.400758277161838e+00,
        -2.549732539343734e+00,
        4.374664141464968e+00,
        2.938163982698783e+00
    };

    static const double d[] =
    {
        7.784695709041462e-03,
        3.224671290700398e-01,
        2.445134137142996e+00,
        3.754408661907416e+00
    };

    if (p < 0 || p > 1)
    {
        err = ERR_DOM;
        return 0.0;
    }
    else if (p == 0)
    {
        err = ERR_RANGE;
        return -XINF /* minus "infinity" */;
    }
    else if (p == 1)
    {
        err = ERR_RANGE;
        return XINF /* "infinity" */;
    }
    else if (p < LOW)
    {
        /* Rational approximation for lower region */
        double q = std::sqrt(-2.0 * std::log(p));
        return (((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) /
            ((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1.0);
    }
    else if (p > HIGH)
    {
        /* Rational approximation for upper region */
        double q = std::sqrt(-2.0 * std::log(1.0 - p));
        return -(((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) /
            ((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1.0);
    }
    else
    {
        /* Rational approximation for central region */
        double q = p - 0.5;
        double r = q * q;
        return (((((a[0] * r + a[1]) * r + a[2]) * r + a[3]) * r + a[4]) * r + a[5]) * q /
            (((((b[0] * r + b[1]) * r + b[2]) * r + b[3]) * r + b[4]) * r + 1.0);
    }
	
}


double RandomVariableStatisticalFunctions::NonCentral_CS_Sample(boost::mt19937& rng, double delta, double lambda)
{
    boost::random::non_central_chi_squared_distribution<> nccs(delta, lambda);

    boost::variate_generator<boost::mt19937&, boost::random::non_central_chi_squared_distribution<>> NonCentral_CS_Sample(rng, nccs);

    return NonCentral_CS_Sample();

}
