/** File "PhraseKWR.cpp", by KWR for CSE250, Fall 2011.  Assignment 5 answer.
    Augmented as Assignment 6 answer.
 */


#include <vector>
#include <string>
#include <sstream>
#include "PhraseKWR.h"
#include "StringWrapKWR.h"
//#include "StringWrapKWR.cpp"  //comment in to do g++ -c PhraseKWR.cpp

using namespace std;

//CLASS INV: All stored words of phrases are lowercase and trimmed

void Phrase::makePhrase(string line) {
   string word = "";    
   int i = 0;                   
   while (i < line.size()) {
      //LOOP INV: "word" has all chars since last space (or start of line)
      if (line[i] == ' ') {     //space found---could check for tabs too
         StringWrap sw(word);   
         sw.trimNonAlphaNum(); 
         if (sw.size() > 0) {
            sw.makeLower();
            elements.push_back(sw.str());
         }
         word = "";          //VITAL to "restore" LOOP INV
      } else {
         word += line[i];
      }
      i++;                   //when using while-loop, easy to forget this.
   }
   if (word != "") {         //Alas, must repeat code for last word read.
      StringWrap sw(word);   //Can avoid by first adding a "sentinel space"
      sw.trimNonAlphaNum();  //to "line" by "line += ' ';" as first statement.
      if (sw.size() > 0) {
         sw.makeLower();
         elements.push_back(sw.str());
      }
   }

   //ENS: all words are lowercase and trimmed.
}

void Phrase::makePhrase2(const string& line) { //Neater code, but above was AOK.
   string word = "";
   istringstream iss(line);   //Using these lines avoids the other lines
   while(iss >> word) {       //that refer to the "line" variable or to "i"
      StringWrap sw(word);   
      sw.trimNonAlphaNum(); 
      if (sw.size() > 0) {
         sw.makeLower();
         elements.push_back(sw.str());
      }
   }
}

Phrase::Phrase(): origForm(""), elements(vector<string>()) { }
Phrase::Phrase(string line) :
   origForm(line),
   elements(vector<string>())
{
   makePhrase(line);  //by ENS, this sets up CLASS INV
}
   

/** REQ---does not care whether phrases are empty or have empty strings.
 */
bool Phrase::lessThan(const Phrase& rhs) const {
   int m = numWords();
   int n = rhs.numWords();
   int minmn = m < n ? m : n;
   for (int i = 0; i < minmn; i++) {
   //LOOP INV: Words 0..i-1 are equal
      if (!(elements.at(i) == rhs.elements.at(i))) {
         return elements.at(i) < rhs.elements.at(i);
      }
   }
   //By LOOP INV, control here means one phrase is prefix of other
   return m < n;
}


int Phrase::numWords() const { return elements.size(); }


/** Number of chars includes one space between words
 */
int Phrase::numChars() const {
   int sz = elements.size();
   int c = 0;
   for (int i = 0; i < sz; i++) {
      c += elements.at(i).size();
   }
   if (c > 0) { c += sz - 1; }
   return c;
}

string Phrase::str() const { return origForm; }
