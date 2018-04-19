/** File "StringClient10.cpp", by KWR for CSE250, Fall 2009.
    In Fall 2010---to work on during Week 3 recitations.
    Example of translating Java quasi-verbatim into C++.
    Later we will write C++ code "the C++ way", using fewer pointers.
 */

#include <iostream>
#include <vector>       
#include <string>    //not needed on timberlake, *is* needed in Visual C++

using namespace std;

class StringStack {
   int top; 
   //static const int maxSize = 101;        //AOK, but not what Java did
   const int maxSize;                       //initialized by constructor

   vector<string>* elements;


 public:

   /** Create empty stack
    */
   StringStack() : top(-1), maxSize(101),
                   elements(new vector<string>(maxSize)) { }


};

/** Test-driving code for StringStacks.
 */
int main() {


   return (0);
}
   
