/** File "PhraseKWR.h", by KWR for CSE250, Fall 2011.  Assignment 5 answer.
 */

#ifndef PHRASE_KWR_H_
#define PHRASE_KWR_H_

#include <vector>
#include <string>

using namespace std;  //eventually we will avoid this line

class Phrase { 
   string origForm;
   vector<string> elements;

   void makePhrase(string line);          //AOK
   void makePhrase2(const string& line);  //avoids copying "line"

   //CLASS INV: words in "elements" are trimmed and lowercased.
 public:
   Phrase();
   explicit Phrase(string line);   //explicit since a single parameter

   ~Phrase() { }

   bool lessThan(const Phrase& rhs) const;

   int numWords() const;  //useful extra methods
   int numChars() const;
   string str() const;    //returns original form---you could add a 
                          //method to return the lowercased words.

   //note: you will likely want to add other methods besides "prefixOf"
};

#endif
   
   

