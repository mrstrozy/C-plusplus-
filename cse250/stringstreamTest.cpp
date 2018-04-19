/** File "stringstreamTest.cpp", by KWR for CSE250, Spring 2013.
    Illustrates a case where you might use a stringstream to convert an int
    to a string.  In C there is a function "itoa" to do this, but the
    "ostringstream" method shown here is more general---it works for any type
    for which an operator<< has been defined.  (In C++ it is traditional to
    overload << rather than write "toString()" functions like in Java.)
 */

#include <string>
#include <iostream>

#include <sstream>

//  #include <random>   //part of std:: namespace, but only in C++11
#include <cstdlib>  //yuck

using namespace std;

int randInt() {
   //std::default_random_engine mygen;
   //uniform_int_distribution<int> distribution(1,600);
   //int result = distribution(mygen);
   int result = rand();  //works deterministically!
   return result;
}


int main() {
   string foostr = "Log(";
   int i = randInt();
   ostringstream ossi;  //value
   ossi << i;
   //string out = foostr + 3 + ")";  //Java; illegal in C++
   string out = foostr + ossi.str() + ")";
   //string out = foostr + ossthree.str() + ')'; //bad on some older compilers?
   cout << out << endl;
}

