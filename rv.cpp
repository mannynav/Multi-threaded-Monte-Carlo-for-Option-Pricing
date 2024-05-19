#include "rv.h"

#include <chrono>

boost::mt19937 rng;

double RandomVariableStatisticalFunctions::my_rand2()   //modified from Numerical recipes
{
    static const long NTAB = 32;

    static const long IM1 = 2147483563;	static const long IA1 = 40014;
    static const long IQ1 = 53668;		static const long IR1 = 12211;

    static const long IM2 = 2147483399;	static const long IA2 = 40692;
    static const long IQ2 = 52774;		static const long IR2 = 3791;

    static const long IMM1 = IM1 - 1;
    static const long NDIV = 1 + IMM1 / NTAB;
    static const double EPS = 3.0e-16;
    static const double RNMX = 1.0 - EPS;
    static const double AM = 1.0 / double(IM1);

    static long idum2;
    static long iy;
    static long iv[NTAB];
    static long idum;

    static bool NOT_FIRST_TIME = false;

    if (NOT_FIRST_TIME == false)		//run for first time
    {
        srand(time(NULL));	//initialise ran2
        idum = -rand();

        idum = (idum == 0) ? 1 : -idum;
        idum2 = idum;

        for (long j = NTAB + 7; j >= 0; --j)
        {
            long k = idum / IQ1;
            idum = IA1 * (idum - k * IQ1) - k * IR1;
            if (idum < 0) idum += IM1;

            if (j < NTAB) iv[j] = idum;
        }

        iy = iv[0];

        NOT_FIRST_TIME = true;
    }

    long k = idum / IQ1;
    idum = IA1 * (idum - k * IQ1) - k * IR1;
    if (idum < 0) idum += IM1;

    k = idum2 / IQ2;
    idum2 = IA2 * (idum2 - k * IQ2) - k * IR2;
    if (idum2 < 0) idum2 += IM2;

    long j = iy / NDIV;
    iy = iv[j] - idum2;
    iv[j] = idum;

    if (iy < 1) iy += IMM1;

    double temp = AM * iy;

    return (temp > RNMX) ? RNMX : temp;
}

double RandomVariableStatisticalFunctions::GetNormalVariate()
{
    static bool Spare_normal_flag = false;
    static double Spare_normal;

    double rsq, v1, v2;

    if (Spare_normal_flag == false)
    {
        do
        {
            v1 = 2.0 * my_rand2() - 1.0;			//Put in range (-1,1)
            v2 = 2.0 * my_rand2() - 1.0;

            rsq = v1 * v1 + v2 * v2;

        } while (rsq >= 1.0 || rsq == 0.0);		//Reject if outside unit circle

        double fac = std::sqrt(-2.0 * std::log(rsq) / rsq);

        Spare_normal = v1 * fac; 					//Generates two normals
        Spare_normal_flag = true;  				//Store one,  return the other

        return v2 * fac;

    }
    else
    {
        Spare_normal_flag = false;
        return Spare_normal;
    }
}

long RandomVariableStatisticalFunctions::Poisson_jumps(const double lambda)
{
    const long N_max = 1000;     //Arbitrary upper bound on the number of jumps
    double w = 1.0;
    double sum = 1.0;

    double u = rv::my_rand2() * std::exp(lambda);
    if (u < sum) return 0;

    for (long i = 1; i <= N_max; ++i)
    {
        w *= lambda / i;
        sum += w;

        if (u < sum) return i;
    }

    return N_max;
}

double RandomVariableStatisticalFunctions::normVariate()
{
    boost::normal_distribution<> nd(0.0, 1.0);

    boost::variate_generator<boost::mt19937&, boost::normal_distribution<> >
		rnorm(rng, nd);

    return rnorm();
}

double RandomVariableStatisticalFunctions::normVariate(boost::mt19937& rng)
{
		boost::normal_distribution<> nd(0.0, 1.0);

	boost::variate_generator<boost::mt19937&, boost::normal_distribution<> >
		rnorm(rng, nd);

	return rnorm();
}

double RandomVariableStatisticalFunctions::rand_uniform(boost::mt19937& rng)
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

double RandomVariableStatisticalFunctions::poisson_jumps(const double lambda)
{

    boost::poisson_distribution<> pois(lambda);
    boost::variate_generator<boost::mt19937&, boost::poisson_distribution<>> poisRNG(rng, pois);

    return poisRNG();

}


double RandomVariableStatisticalFunctions::NonCentral_CS_Sample(boost::mt19937& rng, double delta, double lambda)
{
    boost::random::non_central_chi_squared_distribution<> nccs(delta, lambda);

    boost::variate_generator<boost::mt19937&, boost::random::non_central_chi_squared_distribution<>> NonCentral_CS_Sample(rng, nccs);

    return NonCentral_CS_Sample();

}
