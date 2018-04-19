/** File "LinkArg.cpp", by KWR for CSE250, Fall 2009.
    Argument for LinkTemplate<T>, but with a dreadful typo!
    Question: does YOUR compiler generate an error before linking?

    Also illustrates incoming and outgoing conversions, friending a function,
    and overloading a stream operator to emulate Java's implicit "toString()"
    Note that operator<< is not a member of the class, and (hence) is public.
    The code is also "const correct", including "const &" parameters.
 */

using namespace std;

#include<sstream>  //string stream hierarchy
#include "LinkArg.h"

LinkArg::LinkArg(const int& gx) : x(gx) {
   //this->x = x;  //legal but don't do
}

/** Uses trichotomy of integers. */
int LinkArg::compare(const LinkArg& rhs) const {   
//int LinkArg::dompare(const LinkArg& rhs) const {          //oops!
   return this->x < rhs.x ? -1 : (this->x > rhs.x ? 1 : 0);
}

LinkArg::operator string() const {
   ostringstream out;   //a default value construction, not just a declaration  
   out << this->x;      //a kind-of assignment to a stream
   return out.str();
}

/** Not a member of class LinkArg, but associated to it; friended in the .h file
 */
ostream& operator<<(ostream& out, const LinkArg& item) {
   out << item.x;   //which is why the "friend" decl was needed
   return out;      //need to return reference-to-stream to chain
}
