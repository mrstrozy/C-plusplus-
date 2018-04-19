/** File "NewtonKeyS13.cpp", for CSE250, Spring 2013.  Problem Set 5(1) answer.
    Loosely based on http://www.daniweb.com/forums/thread154965.html, fixing
    its bugs.  Test code in "main" and conversion to function-objects by KWR.
    "Const"---intended as final version, except that code for the PS2 answer
    will be added when its key is posted.  New "main" by Mahmoud Abo Khamis.

    USAGE: Since this includes the HiResTimer, it can only be
    compiled on timberlake, via g++ -O5 Newton.cpp -lrt

    NB: This file is NOT required for Problem Set 2, and no extra credit
    will be given fopr using it.  I coded it because:
    () some students asked me about Newton's Method, and
    () "RealFn.h" is better for lecture notes than the example I'd previously
       prepared to use for pp303-306, which is part of a larger professional
       project of mine...which fails to build on some students' machines...

    Also illustrates working with "by-value" and "by-pointer" objects in
    the same code.  The *objects* are the same, but both the modes of
    access and the virtual/non-virtual behavior can be different.
 */
#include <iostream>
#include <cmath>
#include <iomanip>     // for fixed, setprecision
#include "RealFn.h"
#include "HiResTimer.h"

using namespace Real;

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

class Newton {    // an object that wraps a function to apply Newton's method
   const int maxIterations;
   const double error;
   const Real::MonicFn* f;
   const Real::MonicFn* fprime;
 public:

   Newton(const Real::MonicFn* f)
    : maxIterations(1000)
    , error(1.0e-6)
    , f(f)
    , fprime(f->dfdx())
   { }

   /** Second constructor was debug help for Real::MonicFn::dfdx methods.
       It also allows other error tolerances and limits.
    */
   Newton(const int maxIterations, const double error,
          const Real::MonicFn* f, const Real::MonicFn* fprime)
    : maxIterations(maxIterations)
    , error(error)
    , f(f)
    , fprime(fprime)
   { }


   /** Find root from starting point x---when x is greater than any root
       ** and inflection point **, this is "guaranteed" to find the 
       largest root (except for really pathological functions!?).
    */
   double findRootFrom(double x) {
      int n = 0;
      double xLast = x - 2.0*error;
      while ((std::abs(x - xLast) > error) && (n < maxIterations)) {
         xLast = x;
         //cout << n << ": " << xLast << endl;   //debug only
         x -= ((*f)(x)/(*fprime)(x));
         n++;
      }
      return x;
   }
};

/** Problem Set 5, problem (1) answer, by TA Mahmoud Abo Khamis
 */
int main()
{
	// The following line will create the function n_squared by multiplying n by n
	MonicFn* n_squared = new Times(new X(), new X());

	// The following line will create the function 3*n_squared by multipling n_squared by 3.
	MonicFn* n_squared_X3 = new Times(n_squared, new Constant(3));

	// The following line will create the binary logarithm of n.
	MonicFn* log2n = new Log(2.0, new X());

	// The following line will create n*log(n) by multiplying n by log(n).
	MonicFn* nlog2n = new Times(new X(), log2n);

	// The following line will create 40*n*log(n) by multiplying n*log(n) by 40.
	MonicFn* nlog2n_X40 = new Times(nlog2n, new Constant(40));

	// The following line will create the difference function dif = 3*n_squared - 40*n*log(n).
	MonicFn* dif = new Minus(n_squared_X3, nlog2n_X40);

	// The following line will create a root-finder for the function dif = 3*n_squared - 40*n*log(n).
	Newton newton(dif);

	double n0;

	// The following line will seacrh for a root, starting from a large arbitrary point (e.g. 100).
	n0 = newton.findRootFrom(100);
	cout << "n0 = " << n0 << ", which rounds up to " << int(n0+1.0) << endl;

	cout<<"But if you started Newton from 1 not 100, you'd get the wrong zero:"<<endl;

	// The following line will seacrh for a root, starting from a small arbitrary point (e.g. 1).
	n0 = newton.findRootFrom(1);
	cout << "n0 = " << n0 << endl;

	return 0;
}


