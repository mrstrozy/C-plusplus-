/** File "SeqClient.cpp", by KWR for CSE250, Fall 2009.
    Extra driver file going with Assignment 2 answer key.

    Compile:
        g++ -Wall -o seqClient SeqClient.cpp,   OR with a make file,
        make -f SeqClient.make 

    Usage: seqClient file [n]

    Reads n strings from file (default n = 10000), and returns the
    average value of seq over those strings.  
    Here "seq" is the length of a sequence of chars in a word being
    in (forward or reverse) alphabetical order.

    Can be modified to trim off non-alphabetic characters and/or
    make strings all-lowercase---such methods are provided in
    class StringWrap.  (If you want to use these methods for Assignment 3,
    please copy them textually into your Phrase class---don't replace
    the "string" type by "StringWrap" in your code.)
    The first 64 lines of "main", originally in "stringsorts.cpp",
    were taken from my own PhraseClient.cpp Assgt. 3 answer key.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "StringWrapKey.h"
//#include "StringWrapKey.cpp"

using namespace std;

int main(int argc, char** argv) {
   // transfer command-line arguments to string array
   // remember unlike Java the executable name is the first argument
   //
   vector<string>* args = new vector<string>(argc);
   for (int i = 0; i < argc; i++) {
      args->at(i) = *(argv + i);         //equivalent to argv[i]
   }

   const int DEFAULT_NUM_STRINGS = 10000;//arbitrary
   
   istringstream INS;
   int n = DEFAULT_NUM_STRINGS;
   string infileName;                    // no default for file name.
   ifstream* infilep;   
   
   if (argc >= 3) {                      // numerical argument "n" exists
      INS.str(args->at(2));              // safe since argc >= 3
      if (INS >> n) {
         //OK 
      } else {
         cerr << "Second argument given but not a valid integer" << endl;
         return(1);
      }
   }
   if (argc >= 2) {   //note that this is *not* an "else" of the first "if"
      infileName = args->at(1);
      infilep = new ifstream(infileName.c_str(), ios_base::in);
      if (! infilep->is_open()) {
         cerr << "Unable to open file: " << infileName << endl;
         return(1);
      }
   } else {    //argc == 1, i.e. no arguments given
      cerr << "Usage: seqClient file n    with n >= 0" << endl;
      return(1);
   }

   vector<string> items(n);

   int numItems = 0; //means # of strings stored thus far AND next free index
   string temp;
   //while (numItems < n && *infilep >> temp) {    //compare "Fubar" note in 
   while(*infilep >> temp && numItems < n) {       //stringsorts.cpp
      // control here means read was good, so store item
      items[numItems++] = temp;
   }
   //now test state of stream upon termination

   if (infilep->eof()) {
      cout << "Read all " << numItems << " whitespace-separated items"
           << " in file " << infileName << endl;
   } else if (infilep->bad()) {
      cerr << "Unrecoverable i/o error, sorry, after " << numItems
           << " items." << endl;
   } else {
      // POST: stream is still good, so we must have hit n items
      cout << "Read " << numItems << " whitespace-separated items from file "
           << infileName << endl;
   }

   // In case numItems is (much) less than n, we resize the vector.
   // (An alternative would have been to create an empty vector and use
   // items.push_back(item) to store items read by (*infilep) >> item.)

   if (numItems < n) {
      items.resize(numItems);
   }



   int numValidWords = 0;   //exclude words with no letters and ALL-CAPS
   int longestSeqLength = 0;
   int totalLengthOfSeqs = 0;
   string wordWithLongestSeq = "";

   for (int i = 0; i < numItems; i++) {
      StringWrap sw(items[i]);
      sw.trimNonAlpha();
      if (sw.size() > 0 && !sw.isAllCaps()) {
         numValidWords++;
         sw.makeLower();
         int seqL = sw.seq();
         totalLengthOfSeqs += seqL;
         if (seqL > longestSeqLength) {
            longestSeqLength = seqL;
            wordWithLongestSeq = sw.str();
            cout << "Found " << wordWithLongestSeq << " : "
                 << sw.longestProgressionSafer() << endl;
         }
      }
   }
   cout << endl << "Number of valid words: " << numValidWords << endl;
   cout << "Average seq in valid word from " << infileName << ": " 
        << (totalLengthOfSeqs / double(numValidWords)) << endl;

         
   return (0);
         
}
