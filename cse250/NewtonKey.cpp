/** File "Newton.cpp", by KWR for CSE250, Fall 2009.  Problem Set 1(2) answer.
    Loosely based on http://www.daniweb.com/forums/thread154965.html, fixing
    its bugs.  Test code in "main" and conversion to function-objects by KWR.
    "Const"---intended as final version, except that code for the PS2 answer
    will be added when its key is posted.  

    USAGE: Since this now (11/30) includes the HiResTimer, it can only be
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

/** Problem Set 1, problem (2) answers---calculating n_0 for c = 2, 1.1.
 */
int main() {
   MonicFn* xx = new Times(new X(), new X());
   MonicFn* xxx = new Times(xx, new X());

   // Build f(x) = x^3  - 5x^2 - 20x + 10.
   MonicFn* p2 = new Plus(xxx, new Constant(10.0));
   p2 = new Minus(p2, new Times(new Constant(5.0), xx));
   p2 = new Minus(p2, new Times(new Constant(20.0), new X()));

   // Build x^3 - 50x^2 - 200x + 100
   MonicFn* p11 = new Plus(xxx, new Constant(100.0));
   p11 = new Minus(p11, new Times(new Constant(50.0), xx));
   p11 = new Minus(p11, new Times(new Constant(200.0), new X()));

   // Build 40x(log x)^2 - (3x^2 + x).
   // Or rather, build 40(log x)^2 - 3x - 1

   MonicFn* log2x = new Log(2.0,new X());
   MonicFn* ps2 = new Times(new Constant(40.0), new Times(log2x,log2x));
   ps2 = new Minus(new Minus(ps2, new Times(new Constant(3.0), new X())),
                   new Constant(1.0) );

   //Fall 2010 PS6 #2 answer:

   // Build 30n(log n)^2 - (2n^2 - n).  Or rather, cancelling a factor of n,
   // build 30(log n)^2 - (2n - 1)

   MonicFn* logsq = new Times(log2x,log2x);
   MonicFn* lnsq = new Times(new Ln(new X()), new Ln(new X()));
   MonicFn* twonm1 = new Minus(new Times(new Constant(2.0),new X()),
                               new Constant(1.0));
   MonicFn* ps62lhs = new Times(new Constant(30.0), logsq);
   MonicFn* ps62altlhs = new Times(new Constant(30.0), lnsq);
   MonicFn* ps62 = new Minus(ps62lhs, twonm1);
   MonicFn* altps62 = new Minus(ps62altlhs, twonm1);

   Newton newt2(p2);
   Newton newt11(p11);
   Newton newtps2(ps2);

   Newton newtps62(ps62);
   Newton newtaltps62(altps62);


   double start = 10000.0;
   double root2 = newt2.findRootFrom(start);
   double root11 = newt11.findRootFrom(start);
   double rootps2 = newtps2.findRootFrom(start);

   double rootps62 = newtps62.findRootFrom(1000.0);
   double rootaltps62 = newtaltps62.findRootFrom(1000.0);
   
   cout << fixed << setprecision(6) << endl;

   cout << "Assgt. 6(2) answer = (least int above) " << rootps62 << endl;
   cout << "Alternate if logs to base e: " << rootaltps62 << endl;


   cout << "Starting point for all three runs: x = " << start << endl;
   cout << endl;
   cout << "Fn for c = 2: " << p2->str() << endl;
   cout << "Assgt. 1 Problem (2) answer for c = 2: n_0 = least int above "
        << root2 << endl;
   cout << endl;
   cout << "Fn for c = 1.1: " << p11->str() << endl;
   cout << "Answer for c = 1.1: n_0 = least int above " << root11 << endl;
   cout << endl;

   //cout << "f11(54) = " << p11->operator()(54.0); //legal but verbose
   cout << "f11(53) = " << (*p11)(53.0) << endl;
   cout << "f11(54) = " << (*p11)(54.0) << endl;
   cout << "f11(" << root11 << ") = " << (*p11)(root11) << endl;

   cout << endl;
   cout << "Fn for PS2, problem (2): " << ps2->str() << endl;
   cout << "Tests of ps2: log2x(8.0) = " << (*log2x)(8.0) << endl;
   cout << "ps2(8.0) = " << (*ps2)(8.0) << endl;
   cout << endl;
   cout << "Assgt. 2 (2) answer: n_0 = least int above " << rootps2 << endl;
   cout << "Check: ps2(" << rootps2 << ") = " << (*ps2)(rootps2) << endl;
   cout << "ps2(1477) = " << (*ps2)(1477.0) << endl;
   cout << "ps2(1478) = " << (*ps2)(1478.0) << endl;

   double altStart = 100.0;
   cout << endl;
   cout << "Note, however, if you choose starting point x = " << altStart
        << ", you get:" << endl;
   double rootNaN = newtps2.findRootFrom(altStart);
   cout << "rootps2 = " << rootNaN << ", and weirdly, "
        << "ps2(" << rootNaN << ") = " << (*ps2)(rootNaN) << endl;
   cout << endl;
   cout << "Thus Newton's Method is not foolproof.  Even centuries later \n"
        << "there is active research on improving it, including by Dr. Xu\n"
        << "and his students here at UB." << endl << endl;

   MonicFn* lhs = new Plus(xx, new Constant(3.0));
   MonicFn* rhs = new Minus(log2x, new Constant(4.0));
   MonicFn* prod = new Times(lhs,rhs);
   cout << endl;
   cout << "Parentheses example: " << prod->str() << endl;
   
   MonicFn* log2log2x = new Log(2.0, log2x);
   MonicFn* weirdExponent = new Div(log2x, log2log2x);
   MonicFn* powExample = new Pow(log2x, weirdExponent);
   cout << "Value of " << powExample->str() << " for x = 3 is "
        << (*powExample)(3.0) << endl;
   cout << "Derivative is " << powExample->dfdx()->str() << endl;
   cout << "Value of derivative at x = " << 7 << " is "
        << (*powExample->dfdx())(7.0) << endl;

   HiResTimer timer;

   MonicFn* lnx = new Ln(new X());
   MonicFn* lnlnx = new Ln(lnx);
   MonicFn* weirdExponent2 = new Div(lnx, lnlnx);
   MonicFn* powExample2 = new Pow(lnx, weirdExponent2);

   MonicFn* powExample2B = new PowB(lnx, weirdExponent2);

   cout << "Value of " << powExample2->str() << " for x = 3 is "
        << (*powExample2)(3.0) << endl;

   MonicFn* derivLazy;
   MonicFn* derivExplicit;
   double timeLazy;
   double timeExplicit;

   timer.reset();
   derivLazy = powExample2->dfdx();
   timeLazy = timer.elapsedTime();
   derivExplicit = powExample2B->dfdx();
   timeExplicit = timer.elapsedTime();
   double sumTime = timer.timeSinceReset();

   cout << "Lazy derivative is " << derivLazy->str() << endl;
   cout << "Expl derivative is " << derivExplicit->str() << endl;
   cout << "Times in " << timer.getUnits() << "---Lazy: " << timeLazy
        << ", Explicit: " << timeExplicit << endl;
   
   cout << "Value of derivative at x = " << 7 << " is "
        << (*powExample2->dfdx())(7.0) << endl;
 
   


   return(0);

}

