/** File "FibonacciTimes.cpp", by KWR for CSE250, Fall 2009
    Illustrates difference between exponential time and linear time, and:
    () command-line arguments in C++
    () getting system time for blocks of code
    () using static variables to count function invocations and iterations
    () code set up for separate compilation with a makefile
    () conditional compilation, with a user-defined -Dlabel makefile macro
    () a third-party C++ "bigint" class (by W. Rossi and A. Vinokur, under GPL)
    () the standard-library "pair" class, in <utility>

    **MUST BE COMPILED WITH -lrt OPTION!!, linking in the real-time library**
    I.e. g++ -o fib FibonacciTimes.cpp -lrt
    Usage: ./fib n [base]
    Outputs the nth Fibonacci number F_n, starting with F_0 = 0, F_1 = 1,
    in base "base" notation (default=10).  The argument n must be base-10.
    Also outputs user-selected timing data.
 */

#include<iostream>
#include<sstream>
#include<iomanip>          // for setprecision, fixed
#include<utility>          // for pair
#include "bigint.h"        // copyright (c) by Rossi and Vinokur, under GPL
#include "bigint.cpp"      //just testing before Makefile
//#define BigInt VinBigInt // we'll use the VinBigInt class from this file.
#include "HiResTimer.h"    // code is all in the .h file, inside class braces

using std::cout;
using std::cerr;
using std::istringstream;  
using std::setprecision;
using std::fixed;

/** Typedefs are better style than macros in C++.  The order is reversed---the
    replacement name comes first.  Note that if we also commented-in the above
    #define'd macro, this would now textually read
    "typedef RossiVinBigInt VinBigInt;" 
    and probably cause errors.
 */
typedef RossiBigInt BigInt;  


int countDF = 0;
int countSF = 0;


/** Output F_n by executing the standard mathematical definition recursively,
    resulting in an exp(n) runtime and maybe system stack overflow!
    Base cases: n=0, n=1
 */
BigInt dumbFib(const int n) {
   if (n <= 1) {
      return BigInt(n);
   } else {
      countDF += 2;
      return( dumbFib(n-1) + dumbFib(n-2) );
   }
}

/** Output the pair (F_n, F_{n-1}).  The F_{n-1} is more than you asked
    for, but the extra work really helps the recursion!
    REQUIRES n >= 1, because F_{-1} should be regarded as garbage!
    Hence n = 2 must also become a base case.
 */
pair<BigInt,BigInt> smartFibHelper(const int n) {
   if (n <= 2) {
      return pair<BigInt,BigInt>(BigInt((3*n - n*n)/2), BigInt(n-1));
   } else {
      countSF++;
      pair<BigInt,BigInt> pf23 = smartFibHelper(n-2);

      // F_{n-2} = pf23.first, F_{n-3} = pf23.second.  Main point is that
      // F_n = 2*F_{n-2} + F_{n-3}, while F_{n-1} = F_{n-2} + F_{n-3} of course
      // return pair<BigInt,BigInt>(BigInt(2)*(pf23.first) + pf23.second,

      return pair<BigInt,BigInt>((pf23.first)*2 + pf23.second,
                                 pf23.first + pf23.second);
   }
}  //may give warning about not ending with a return statement

BigInt smartFib(const int n) {
   return (smartFibHelper(n).first);
}


/** Fill in an array, with no recursion!  Takes O(n) time.
 */
BigInt smarterFib(const int n) {
   vector<BigInt>* fibs = new vector<BigInt>(n+1);  //indices 0..n
   fibs->at(0) = BigInt(0);     //here we are using value, not pointer
   fibs->at(1) = BigInt(1);
   for (int i = 2; i <= n; i++) {
      fibs->at(i) = fibs->at(i-2) + fibs->at(i-1);
   }
   //return fibs->at(n);                   //natural, but causes memory leak
   const BigInt preserveMe = fibs->at(n);  //can do with reference & ?
   delete(fibs);
   return preserveMe;
}
      


int main(int argc, char** argv) {
   // First convert args from C-strings to proper C++ STL strings,
   // using the same kind of string-array "args" Java uses from the get-go.
   // Note that it is OK to assign a C-string to an STL string. 
   // One could say (char*)[] in place of char**, but latter is traditional
   // NOTE: argc *includes* the name of the executable! so always >= 1

   vector<string>* args = new vector<string>(argc);
   for (int i = 0; i < argc; i++) {
      args->at(i) = *(argv + i);         //equivalent to argv[i]
   }
  
   //Now the args are strings.  We want integers, n may be a big integer.
   //Annoyingly, C++ does not have a standard string-to-int conversion.
   //We could import the "atoi" function from the C library, but that would
   //require us to use the string::c_str() method to convert the string
   //back to a char*, which we avoid like the plague.  Here's the C++ way:

   istringstream INS;
   int n;

   int base = 10;     //default
   if (argc >= 3) {   //change it
      INS.str(args->at(2));        //safe since argc >= 2
      if (INS >> base) {
         //OK
      } else {
         cerr << "Second argument given but not a valid integer" << endl;
         return(1);
      }
   } 
   if (argc >= 2) {   //note that this is *not* an "else" of the first "if"
      INS.str(args->at(1));
      if (!(INS >> n)) {
         cerr << "First argument given but not a valid integer" << endl;
         return(1);
      }
   } else {    //argc == 1, i.e. no arguments given
      cerr << "Usage: fib n [base]    with n >= 0" << endl;
      return(1);
   }

   cout << "Clock ticks per second: " << sysconf(_SC_CLK_TCK) << endl;
   cout << "Clocks per second via sysconf: " << sysconf(CLOCKS_PER_SEC) << endl;
   cout << "Clocks per second without it : " << CLOCKS_PER_SEC << endl;

   double t = 0.0;
   HiResTimer* timer = new HiResTimer();
   if (n <= 30) {
      BigInt dfn = dumbFib(n);
      t = timer->elapsedTime();
   } else {
      cout << "Now allowing 'dumb' call on n <= 30 only, sorry." << endl;
   }

   cout << fixed << setprecision(3) << endl;
   cout <<"Time for double-branch recursion for fib(" << n << "), in "
        << timer->getUnits() << ": "<< t << endl;
   timer->reset();
   //BigInt sfn = smartFib(n);
   BigInt ssfn = smarterFib(n);   //Dr. Ngo's notes give same thing.
   t = timer->elapsedTime();
   cout << "Time for single-branch recursion for fib(" << n << "), in "
        << timer->getUnits() << ": " << t << endl;
   cout << "F_" << n << " = " << ssfn << endl;
   cout << "Count of 'dumb calls: " << countDF << endl;
   cout << "Count of smart calls: " << countSF << endl;
   delete(timer);
   return(0);
}
