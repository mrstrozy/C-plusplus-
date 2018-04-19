/** File "LinkArg.h", by KWR for CSE250, Fall 2009.
    Argument for LinkTemplate<T>, but with a dreadful typo!
    Question: does YOUR compiler generate an error before linking?

    Also illustrates incoming and outgoing conversions, friending a function,
    and overloading a stream operator to emulate Java's implicit "toString()"
    Note that operator<< is not a member of the class, and (hence) is public.
    The code is also "const correct", including "const &" parameters.
 */
#ifndef LINKARG_H_
#define LINKARG_H_

#include<iostream>

using namespace std;

class LinkArg {
   int x;
 public:
   explicit LinkArg(const int& x);                   //should have "explicit"
   //int dompare(const LinkArg& rhs) const;   //oops!
   int compare(const LinkArg& rhs) const;
   operator string() const;      //analogue of Java toString()?  Not quite!

   friend ostream& operator<<(ostream& out, const LinkArg& item);
};

ostream& operator<<(ostream& out, const LinkArg& item);   //true analogue

#endif
