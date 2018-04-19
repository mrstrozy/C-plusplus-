/** File "StringClient.cpp", by KWR for CSE250, Fall 2009.
    Answer Key for Assignment 1, part (4)---with one thematic twist:
    Six lines, all in the StringStack class, are changed from what the
    Java version had in /meaning/, not just syntax.  Can you find them?

    Some alternative translation choices as-noted were also fine, but
    (to save room), the "const string*" option is not shown.
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

   // CLASS INV': top indexes the /top element/, so empty stack is top == -1;

 public:

   /** Create empty stack
    */
   StringStack() : top(-1), maxSize(101),
                   elements(new vector<string>(maxSize)) { }

   virtual ~StringStack() { cout << "Hi There!" << endl; delete(elements); }   //AOK to omit this line, despite warning
   virtual void push(string c) { elements->at(++top) = c; }
   virtual string pop() {
      if (top == -1) {
         cerr << "Attempt to pop from empty stack." << endl;
         return "";  //System.err.print ~= cerr << in C++
      } else {
         return elements->at(top--); 
      }                             
   }                               
   virtual int size() const { return top+1; }
};

//Extra Credit answer is in StringClientXC.cpp

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
   //delete(testStack);
   StringStack test2 = (*testStack);
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
