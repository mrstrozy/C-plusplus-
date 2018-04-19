/** File "StringWrap.h", by KWR for CSE250, revised by MRS for Spring 2014
    CSE250 assignment 5.
 */

#ifndef STRINGWRAP_H_
#define STRINGWRAP_H_

#include<string>
#include <vector>
#include <iostream>

using namespace std;

class StringWrap {
   string st;             // this is called "wrapping" a single object.
 public:
   explicit StringWrap(string s);      
   StringWrap();          // zero-parameter constructor
    
   //virtual ~StringWrap() { }    //this class intends no inheritance

   void trimNonAlpha();   // not const---it modifies st
   bool isAlpha() const;
   bool isAllCaps() const;
   void makeLower();      // ASCII-specific!
   void punctCorrect();
 
   string str() const;
   int size() const;
};
ostream& operator<< (ostream& out, const StringWrap& item);


#endif
