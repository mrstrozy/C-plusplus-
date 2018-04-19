/** File "StringClientXXC.cpp", by KWR for CSE250, Fall 2009.
    Answer Key for Assignment 1, part (4)---going beyond extra credit.
    Illustrates solution (c) to managing a class hierarchy, kind-of
    in line with the text chapter 3.  Will be covered in lectures.

    Also illustrates using an osstringstream to simulate streaming an
    int and converting it into a string.  This enables us to append the 
    current value of the loop variable to the string being pushed.
    This trick replaces older functionc called "itoa" and "atoi" (etc.).

    **For a further exercise**, we will code operator= and a copy
      constructor, so please read this file with that in mind.
 */

#include <iostream>
#include <vector>       
#include <sstream>   //would be needed for int-to-string conversion...

using namespace std;

class StringStack {
 //protected:                               //no longer protected! PRIVATE
   int top; 
   const int maxSize;                       //initialized by constructor
   vector<string>* elements;

   // CLASS INV: top indexes first free cell, so empty stack is top == 0;

 public:

   /** Create empty stack
    */
   StringStack() : top(0), maxSize(101),
                   elements(new vector<string>(maxSize)) { }

   virtual ~StringStack() { }  

   virtual void push(string c) { elements->at(top++) = c; }
   virtual string pop() {
      if (empty()) {
         cerr << "Attempt to pop from empty stack." << endl;
         return "";  
      } else {
         return elements->at(--top); 
      }                             
   }                               
   virtual int size() const { return top; }
   virtual bool empty() const { return top == 0; }
   virtual bool full() const { return top == maxSize; }
};

class MyStringStack : public StringStack {    //Extra Credit---
 public:
   MyStringStack() : StringStack() { }
   virtual ~MyStringStack() { }

   virtual void push(string c) {
      if (full()) {
         cerr << "Attempt to push onto full stack, doing nothing..." << endl; 
         return;
      } else {
         StringStack::push(c);  //better than duplicating base-class body.
      }
   }
};
   
/** Test-driving code for StringStacks.
 */
int main() {
   StringStack* testStack = new StringStack();
   cout << "Pushing \"AAA\" ... ";     //use cout << ... 
   testStack->push("AAA"); 
   cout << "Pushing \"BBB\" ... " << endl;   //this tacks on ...<< endl;
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

   //now to test the derived class, add 101 strings.
   //yes, 101 is a "magic constant", but it might be a system-limitation...

   cout << endl << "Now pushing 100 strings..." << endl;
   testStack = new MyStringStack();
   for (int i = 0; i < 100; i++) {
      ostringstream oss;        //See String Conversion slide notes.
      oss << i;                 //Used in "StringClientXXC.cpp".
      string pushMe = "filler " + oss.str();
      cout << "Pushing " << pushMe << endl;
      testStack->push(pushMe);
   }
   cout << "Done." << endl;
   cout << "Pushing 101st string \"fuller\"...is it safe?" << endl;
   testStack->push("fuller");
   cout << "Yes!  Now what happens if we try a 102nd string \"faller\"?..."
        << endl;
   testStack->push("faller");
   cout << "Top of stack was still: " << testStack->pop() << endl;
   cout << "Had override not been called, we would have had an "
        << "out-of-range exception." << endl;
   return (0);
}

