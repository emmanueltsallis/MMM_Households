//**********C++ SUPPORT FUNCTIONS*********//

#include <stdio.h>
#include <math.h>


/*
ROUND(value, "direction")
This MACRO returns the rouded value of a value specified by the user. 
The user can specify the direction wih the word UP and "DOWN", in quotes and capital letters, in which case the MACRO will round up or down, respectively.
If any other word or no word is specified, the MACRO will simply round the value.
*/
double ROUND( double x , string d = "none")
{
	double r = round(x);
	double y;
	if(d=="UP")
		y = r>x? r: r+1;
	else if(d=="DOWN")
		y = r<x? r: r-1;
	else
		y = r;
	return y;
}


/*
LAG_SUM(obj, "lab", lag1, lag2)
This MACRO returns the sum of lagged values of a specifed variable named "lab". 
The first lag defines how many lags to sum. The secong lag defines from which lag it will start summing. By default, the second lag is 1.
WARNING: make sure there are specified lagged values for the variable "lab".
EXAMPLE 1: LAG_SUM(p, "X", 4) will return VL("X",0) + VL("X",1) + VL("X",2) + VL("X",3).
EXAMPLE 2: LAG_SUM(p, "X", 3, 2) will return VL("X",2) + VL("X",3) + VL("X",4).
*/
double LAG_SUM( object *obj , const char *var , int lag = 0, int lag2 = 0)
{
	double x = 0;
	int i;
	for(i=lag2; i<=lag2+lag-1; i++)
		x = x + VLS( obj, var, i);
	return x;
}

/*
LAG_AVE(obj, "lab", lag1, lag2)
Same as LAG_SUM but this MACRO returns the average for the lag1 periods.
WARNING: make sure there are specified lagged values for the variable "lab".
EXAMPLE 1: LAG_AVE(p, "X", 4) will return (VL("X",0) + VL("X",1) + VL("X",2) + VL("X",3))/4.
EXAMPLE 2: LAG_AVE(p, "X", 3, 2) will return (VL("X",2) + VL("X",3) + VL("X",4))/3.
*/
double LAG_AVE( object *obj , const char *var , int lag = 0, int lag2 = 0)
{
	double x = 0;
	int i;
	for(i=lag2; i<=lag2+lag-1; i++)
		x = x + VLS( obj, var, i);
	return x/lag;
}

/*
LAG_GROWTH(obj, "lab", lag1, lag2)
This MACRO returns the growth rate of a variable named "lab" for the lag1 periods.
The first lag defines how many lags to sum. The secong lag defines from which lag it will start summing. By default, the second lag is 0.
WARNING: make sure there are specified lagged values for the variable "lab".
EXAMPLE 1: LAG_GROWTH(p, "X", 4) will return (V("X") - VL("X",4))/VL("X",4).
EXAMPLE 2: LAG_GROWTH(p, "X", 3, 2) will return (VL("X",2) - VL("X",5))/VL("X",5).
*/
double LAG_GROWTH( object *obj , const char *var , int lag = 0, int lag2 = 0)
{
	double x = VLS( obj, var, lag2);
	double y = VLS( obj, var, lag2+lag);
	double r = y!=0? (x-y)/y : 0;
	return r;
}


/*
qexponentialcdf(q, lambda, x)
Returns the CDF of the q-exponential distribution with parameters q (shape) and lambda (scale), evaluated at x.
- For 1 ? q < 2: support is x ? 0 (infinite)
- For 0 < q < 1: support is 0 ? x < 1/((1-q)*lambda) (finite)
If parameters or x are out of support, prints a warning to stderr and returns NAN.
Parameters:
    q      : entropic index parameter (0 < q < 2)
    lambda : rate parameter (lambda > 0)
    x      : value to evaluate the CDF at
Returns:
    The CDF value at x, or NAN if out of support.
*/
double qexponentialcdf(double q, double lambda, double x)
{
    if (q <= 0.0 || q >= 2.0) {
        fprintf(stderr, "qexponentialcdf: q (%.4f) out of range (0 < q < 2)\n", q);
        return NAN;
    }
    if (lambda <= 0.0) {
        fprintf(stderr, "qexponentialcdf: lambda (%.4f) must be > 0\n", lambda);
        return NAN;
    }
    if (q >= 1.0) {
        if (x < 0.0) {
            fprintf(stderr, "qexponentialcdf: x (%.4f) out of support for q >= 1 (x >= 0)\n", x);
            return NAN;
        }
    } else { // 0 < q < 1
        double xmax = 1.0 / ((1.0 - q) * lambda);
        if (x < 0.0 || x >= xmax) {
            fprintf(stderr, "qexponentialcdf: x (%.4f) out of support for 0 < q < 1 (0 <= x < %.4f)\n", x, xmax);
            return NAN;
        }
    }
    double arg = 1.0 - (1.0 - q) * lambda * x;
    double exponent = (2.0 - q) / (1.0 - q);
    return 1.0 - pow(arg, exponent);
}


/*
qexponential(q, lambda)
Returns a random sample from the q-exponential distribution with parameters q (shape) and lambda (scale).
Quantile function:
    x = [1 - (1-U)^{(1-q)/(2-q)}] / [(1-q)*lambda]
where U ~ Uniform(0,1)
- For 1 ? q < 2: support is x ? 0 (infinite)
- For 0 < q < 1: support is 0 ? x < 1/((1-q)*lambda) (finite)
If parameters are out of support, prints a warning to stderr and returns NAN.
Parameters:
    q  : entropic index parameter (0 < q < 2)
    lambda : rate parameter (lambda > 0)
Returns:
    A random sample x, or NAN if out of support.
*/
double qexponential(double q, double lambda)
{
    if (q <= 0.0 || q >= 2.0) {
        fprintf(stderr, "qexponential: q (%.4f) out of range (0 < q < 2)\n", q);
        return NAN;
    }
    if (lambda <= 0.0) {
        fprintf(stderr, "qexponential: lambda (%.4f) must be > 0\n", lambda);
        return NAN;
    }
    double U = RND;
    double exponent = (1.0 - q) / (2.0 - q);
    double x = (1.0 - pow(1.0 - U, exponent)) / ((1.0 - q) * lambda);

    if (q >= 1.0) {
        if (x < 0.0) {
            fprintf(stderr, "qexponential: x (%.4f) out of support for q >= 1 (x >= 0)\n", x);
            return NAN;
        }
    } else { // 0 < q < 1
        double xmax = 1.0 / ((1.0 - q) * lambda);
        if (x < 0.0 || x >= xmax) {
            fprintf(stderr, "qexponential: x (%.4f) out of support for 0 < q < 1 (0 <= x < %.4f)\n", x, xmax);
            return NAN;
        }
    }
    return x;
}


