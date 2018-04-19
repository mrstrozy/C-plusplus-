/** File "PhraseDriverKWR.cpp", by KWR for CSE250, Fall 2011. 
    Assignment 5 answer
    Usage: PhraseDriver fooPhrases
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>        //aliases operator< to "less<...>", may use later
#include "PhraseKWR.h"
//#include "PhraseKWR.cpp"   //comment-in this and other to compile w/o make
#include "StringWrapKWR.h"
//#include "StringWrapKWR.cpp"  //ditto

int main(int argc, char** argv) {
   if (argc != 2) {
      cerr << "Sorry, A5 answer doesn't read a textfile too, just one file.";
      cerr << endl << "Usage: phrasedriver phraseFile" << endl;
      return 1;
   }
   ifstream PHRASES(argv[1], ios::in);

   vector<Phrase> phrases;   //value-construction, not just declaration.
   string line;              //ditto: line = "" now by default.
   while(getline(PHRASES,line)) {
      Phrase phr(line);      //calls the explicit constructor.
      phrases.push_back(phr);
      cout << "Read this phrase with " << phr.numWords() << " words and "
           << phr.numChars() << " chars: " << endl << line << endl;
   }
   int numPhrases = phrases.size();
   if (numPhrases <= 1) {
      cout << "Read fewer than two phrases, so no comparison done." << endl;
   } else {
      Phrase phr1 = phrases.at(numPhrases-2);  //Phrase::operator= used here.
      Phrase phr2(phrases.at(numPhrases-1));   //Phrase copy-ctor used here.
      //Phrase phr3(phrases.at(numPhrases-1).str());  //avoids calling either.
      cout << endl << endl;
      cout << "Last two phrases are: " << endl << phr1.str() << endl 
           << phr2.str() << endl;

      //Example of an if-then-else expression, just to be geeky.
      string whichIsLess = (phr1.lessThan(phr2)) ? "former" : "latter";
      cout << "The " << whichIsLess << " comes first alphabetically." << endl;
   }
   return 0;
}

