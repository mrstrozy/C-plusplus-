/** File "StringClientError.cpp", by KWR for CSE250, Fall 2009.
    Illustrates "gotcha" that the order in a constructor's initializer
    section doesn't matter---instead, the order of fields determines the
    order of events.  Hence C++ silently initializes "maxSize" to 0
    before creating the vector.  The unguarded base-class version of "push"
    immediately throws an out-of-range exception when "->at" is called
    on the resulting empty vector!  (If you used [] rather than "at", you'd
    get no error but would write to a "garbage" location!)
    This is warned about only when you do g++ -Wall StringClientError.cpp
 */

#include <iostream>
#include <vector>       

using namespace std;

class StringStack {
   int top; 

   vector<string>* elements;
   const int maxSize;           //order-inversion error, dastardly subtle!

   // CLASS INV': top indexes the /top element/, so empty stack is top == -1;

 public:

   /** Create empty stack
    */
   StringStack() : top(-1), maxSize(101),   //OOPS! out-of-field-order!
                   elements(new vector<string>(maxSize)) { }

   virtual void push(string c) { elements->at(++top) = c; }
   virtual string pop() {
      if (top == -1) {
         cerr << "Attempt to pop from empty stack." << endl;
         return "";  
      } else {
         return elements->at(top--); 
      }                             
   }                               
   virtual int size() const { return top+1; }
};


/** Test-driving code for StringStacks.
 */
int main() {
   StringStack* testStack = new StringStack();
   cout << "Pushing \"AAA\" ... ";        //no "endl", keep next on same line
   testStack->push("AAA"); 
   cout << "Pushing \"BBB\" ... " << endl;
   testStack->push("BBB"); 
   cout << "Size is now " << testStack->size() << endl;
   testStack->pop();
   cout << "Pop---size is now " << testStack->size() << endl;
   string c = testStack->pop();
   cout << "I popped the string \""
        << c << "\", size now " << testStack->size() << endl;
   cout << "Can I pop again?" << endl;
   string d = testStack->pop();
   cout << "Oops!  I got: \"" << d << "\"" << endl;
   return (0);
}
   
/*------------------------------------------------------------------
Alternative: one could place a trailing "\n" in the strings, e.g.
   ...
   cout << "Pushing \"BBB\" ... \n";
   ...
   cout << "Size is now " << testStack->size() << "\n";

But in the former, doing \n might add to the confusion of the escaped quotes.
And in the latter, some think tacking a single "\n" like that looks tacky.
Generally, using "endl" is preferred.
*///----------------------------------------------------------------
