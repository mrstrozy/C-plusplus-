/** File "StringWrapKey.h", by KWR for CSE250, Fall 2009.  Coded answer to
    Assignment 2, problem (3)---with code in StringWrapKey.cpp.
    May become useful for bundling other string functions---could be
    "purely functional" rather than wrap data mutable by void methods; then
    all the methods would become static and this would go as a namespace.
    For now: this is TO BE CANNIBALIZED, not subclassed or wrapped further!
 */

#ifndef STRINGWRAPKEY_H_
#define STRINGWRAPKEY_H_

#include<string>

using std::string;

class StringWrap {
   friend bool operator<(const StringWrap& lhs, const StringWrap& rhs);
   string st;             // this is called "wrapping" a single object.
 public:
   explicit StringWrap(string s);      
   //virtual ~StringWrap() { }         //this is intended as POD
   void trimNonAlpha();   // not const---it modifies st
   bool isAlpha() const;
   bool isAllCaps() const;
   void makeLower();      // ASCII-specific!
   
   /** Returned strng = maximal prefix of st in nondescending or
       nonascending alphabetical (ASCII) order.
       REQ: st.size() >= 2;
       ENS: st.size() >= 2;
    */
   string longestProgression() const;

   /** Allows strings of length 0 or 1, returning themselves.
       Hence does not have REQ or ENS, but runs slower with an extra test.
    */
   string longestProgressionSafer() const;

   /** Length of longest progression, as actually asked for.
    */
   int seq() const;

   string str() const;
   int size() const;
};

bool operator<(const StringWrap& lhs, const StringWrap& rhs);

#endif
