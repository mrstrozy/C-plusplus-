/** File "StringClientXC.cpp", by KWR for CSE250, Fall 2009.
    Answer Key for Assignment 1, part (4)---with extra credit.
    There were various other ways to code the MyStringStack class, but all
    need the *main point* that you need /virtual/ in C++ to get overrides.
    And a base-class variable needs to call the override thru a pointer
    [or C++ reference/alias].

    Extra-credit coders faced the dilemma of the subclass needing to
    access the "top" and "maxSize" fields, and most importantly, the
    "elements" themselves!  Since C++ does not have Java "package scope",
    but rather defaults to "private", you had to choose an option:

    (a) Make the fields "protected".  This is what the code below does,
        along lines of the IntList2.java example in labs.  However, in
        large projects, "protected" often hurts modularity.
    (b) Do "friend class MyStringStack;" inside class StringStack.
        This was also shown in IntList2.java, and was AOK.  However,
        morally the writers of StringStack don't know about "My" versions
        in advance, so that "friend" line wouldn't be in their code.
    (c) Add public methods "empty()" and "full()" to the base class, whose
        bodies do the only needed tests "top == 0" and "top == maxSize".
        However, this does not solve the problem of the derived class
        wanting to access "elements"!  Providing a public "at(...)" method
        or operator[], one that makes a "wrapper call" to the same method
        on "elements" proper, would defeat the limitation of being a *stack*.

        Obeying this limitation, the idea is that MyStringStack::push
        can first do its check to see if the unguarded base-class method
        is safe to call, and then call it by StringStack::push(c);
        This is the *best* way, obeying the "Principle of Least Privilege".
        Commented-out below, but shown in file "StringClientXXC.cpp"
 */

#include <iostream>
#include <vector>       
//#include <sstream>   //would be needed for int-to-string conversion...

using namespace std;

class StringStack {
 protected:
   int top; 
   const int maxSize;                       //initialized by constructor
   vector<string>* elements;

   // CLASS INV: top indexes first free cell, so empty stack is top == 0;

 public:

   /** Create empty stack
    */
   StringStack() : top(0), maxSize(101),
                   elements(new vector<string>(maxSize)) { }

   virtual ~StringStack() { }  //included for benefit of extra-cr. subclass

   virtual void push(string c) { elements->at(top++) = c; }
   virtual string pop() {
      if (top == 0) {
         cerr << "Attempt to pop from empty stack." << endl;
         return "";  //System.err.print ~= cerr << in C++
      } else {
         return elements->at(--top); 
      }                             
   }                               
   virtual int size() const { return top; }
   //virtual bool empty() const { return top == 0; }
   //virtual bool full() const { return top == maxSize; }
};

class MyStringStack : public StringStack {    //Extra Credit---
 public:
   MyStringStack() : StringStack() { }
   virtual ~MyStringStack() { }

   virtual void push(string c) {
      if (top == maxSize) {
      //if (full()) {             //better!
         cerr << "Attempt to push onto full stack, doing nothing..." << endl; 
         return;
      } else {
         elements->at(top++) = c; //unwise duplication of code in base class
         //StringStack::push(c);  //better!
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
      testStack->push("filler");    
      //ostringstream oss;        //See String Conversion slide notes.
      //oss << i;                 //Used in "StringClientXXC.cpp".
      //testStack->push("filler " + oss.str());
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

