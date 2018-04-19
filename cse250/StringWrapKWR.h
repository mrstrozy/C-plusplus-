/** File "StringWrapKWR.h", by KWR for CSE250, Fall 2011.
    Assignment 5 answer, changed to avoid trimming off numbers.
 */

#ifndef STRINGWRAP_H_
#define STRINGWRAP_H_

#include <string>
#include <iostream>

using std::string;
using std::ostream;

class StringWrap {
   string st;                // this is called "wrapping" a single object.
 public:
   explicit StringWrap(string s);      
   StringWrap();             // zero-parameter constructor
    
   //virtual ~StringWrap() { }    //this class intends no inheritance

   void trimNonAlphaNum();   // not const---it modifies st.  Leaves numbers.
   bool isAlpha() const;
   bool isAllCaps() const;
   void makeLower();         // ASCII-specific!
   
   string str() const;
   size_t size() const;
};

ostream& operator<< (ostream& out, const StringWrap& item);

#endif
