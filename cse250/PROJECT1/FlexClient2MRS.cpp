/*********************************************************************
*FileName: FlexClientMRS.cpp made by Matthew Strozyk for CSE250, 
*          assignment 7(Project 1).
*
***********************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//#include "StringWrap.h"
#include "StringWrap.cpp"
#include "FlexArray2MRS.h"
using namespace std;

bool hd1(string,string); 
bool ed1(const string&,const string&);
bool dd1(string,string);
bool transpose(string,string);
bool findChain(FlexArray<FlexArray<StringWrap> >*,StringWrap);
bool dd1(string x,string y){
   return ed1(x,y) || transpose(x,y);
}
bool transpose(string x,string y){
   bool foundOne = false;
   if(x.length() != y.length()) {
      return false;
   }
   // we now know that both strings are the same length
   
   for(int i = 0; i < x.length();i++){

      if(x[i] != y[i] && foundOne){
         return false;
      }
      if(x[i] != y[i] && !foundOne){
         if((i + 1) != x.length()){
            if(x[i] == y[i+1]){
               foundOne = true;
               i = i + 2;
          } else {
               return false;
            }
       } else {
            return false; 
         }
      } 
   }
   //only one instance of a swap was found
   
   return foundOne;       
}
   
bool hd1(string x,string y){
    int diff = 0;
    for(int i = 0; i < x.length(); i++){
       if(x[i] != y[i])
         diff++;
    }
    //cout << "x: " << x << " y: " << y << endl;
    //cout << "Diff: " << diff << endl;
    return diff == 1;
}

bool ed1(const string& lhs, const string& rhs) {
   int left = 0;
   int right;
   if (lhs.size() == rhs.size()) {
      return hd1(lhs,rhs);
   } else if (lhs.size() == 1 + rhs.size()) {  //check for delete in first string
      //LOOP INV: All chars to left of "left" match, and all to right of "right".
      //Hence an extra char in lhs will eventually give right <= left.
      right = lhs.size() - 1;
      while (left < right && lhs.at(left) == rhs.at(left)) { left++; }
      while (right > left && lhs.at(right) == rhs.at(right-1)) { right--; }
      return right == left;  //all chars matched except this extra one.
   } else if (1 + lhs.size() == rhs.size()) {  //check for delete in first string
      //LOOP INV: All chars to left of "left" match, and all to right of "right".
      //Hence an extra char in rhs will eventually give right <= left.
      right = rhs.size() - 1;
      while (left < right && lhs.at(left) == rhs.at(left)) { left++; }
      while (right > left && lhs.at(right-1) == rhs.at(right)) { right--; }
      return right == left;  //all chars matched except this extra one.
   } else {
      return false;
   }
}

bool findChain(FlexArray<FlexArray<StringWrap> >* flexp, StringWrap sw){
   FlexArray<FlexArray<StringWrap> >::iterator it = flexp->begin();
   if(flexp->empty()){
      FlexArray<StringWrap> temp(40);
      temp.insert(temp.begin(),sw);
      flexp->insert(it,temp);
      return true;
 } else {
      
      while(it != flexp->end()){
         bool foundDup = false;
         bool foundChain = false;
         FlexArray<StringWrap>::iterator* here;
         FlexArray<StringWrap>::iterator insIter = (*it).begin();



         while(insIter != (*it).end()){
            if((*insIter).str() == sw.str()){
               foundDup = true;
            }
            if(ed1((*insIter).str(),sw.str()) && !foundDup && !foundChain){
               here = &insIter;
               foundChain = true;
               
          } else if(!foundDup && !foundChain) {
               FlexArray<StringWrap>::iterator temp = insIter;
               if((*insIter).size() > 1 && insIter != ++insIter && dd1((*(insIter)).str(),sw.str()) && dd1((*insIter).str(),sw.str())){
                  here = &insIter;
                  foundChain = true;
                  insIter = temp;
               }
            }
            insIter++;    
         } 
         if(foundChain && !foundDup){
            (*it).insert((*here),sw);
            return true;
         }
         it++;
      }
      
   }
   FlexArray<StringWrap> tempFlex(40);
   tempFlex.insert(tempFlex.begin(),sw);
   flexp->insert(flexp->begin(),tempFlex);
   return true;
      
}



int main(int argc,char** argv){


   vector<string>* args = new vector<string>(argc);
   for (int i = 0; i < argc; i++) {
      args->at(i) = *(argv + i);         //equivalent to argv[i]
   }

   const int DEFAULT_NUM_STRINGS = 10000;//arbitrary

   istringstream INS;
   int desiredWords = DEFAULT_NUM_STRINGS;
   string infileName;                    // no default for file name.
   ifstream* infilep;

   if (argc >= 3) {                      // numerical argument "n" exists
      INS.str(args->at(2));              // safe since argc >= 3,,, WHAT does this do??
      if (INS >> desiredWords) {
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
      cout << " Usage: [Fully-qualified file name] [Number of words to input]" << endl;
      return(1);
   }
   //File is valid and has been opened for reading 


   //TODO:Write the client file here that:
   //       ->[]makes chains inside of the flex array
   //       ->[]tests to see if there are repeat words, if there are then do nothing
   //       ->[]tests to see if the word can go in between any two words
   //       ->[]finds chains with the longest growth in words from smallest to largest
   //       ->STANDARD: []make chains out of the inputted words
   //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
   FlexArray<FlexArray<StringWrap> >* flexp = new FlexArray<FlexArray<StringWrap> >(40);
   string s;
   int wordCount = 0;
   while(*infilep >> s && wordCount < desiredWords){
      StringWrap sw(s);
      sw.makeLower();
      sw.punctCorrect();
      findChain(flexp,sw);
      wordCount++;
   }
   FlexArray<FlexArray<StringWrap> >::iterator test = flexp->begin();
   while(test != flexp->end()){
      cout << *test;
      test++;
   } 
   return 0;
}
/******************************************************
I was unable to get the first code to work fully so I
cannot comment on whether or not the iterators made
finding the longest word and the best-growth chains.
I can imagine that it would help a ton as you could
keep a reference of an iterator on the longest word and you 
could keep comparing it to rest of the words. If there is
a longer word, just re-assign the iterator to that iterator
and then continue on until the end from there.
**********************************************************/
