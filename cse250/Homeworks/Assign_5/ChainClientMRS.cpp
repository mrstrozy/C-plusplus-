/*********************************************************************
*FileName: ChainClientMRS.cpp made by Matthew Strozyk for CSE250, 
*          assignment 5.
*
***********************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "StringWrap.h"
#include "PeekDeque3MRS.h"
using namespace std;

bool hd1(string,string); 
bool ed1(const string&,const string&);
bool testLegalChain(PeekDeque<StringWrap>*);
bool findChain(vector<PeekDeque<StringWrap> >*,StringWrap);
void findLongestChain(vector<PeekDeque<StringWrap> >*);
void findChainWithLongestWord(vector<PeekDeque<StringWrap> >*);
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




bool testLegalChain(PeekDeque<StringWrap>* pd){

   pd->setPeekIndexToFront(); 
   string s1;
   string s2;
   s1 = (pd->peek()).str();
   pd->moveRearward();
   s2 = (pd->peek()).str();
   pd->moveRearward();
   while(!pd->endOfPeek()){
      if(!ed1(s1,s2)){
         cout << "This is not a legal chain." << endl;
         return false;
    } else {
         s1 = s2;
         s2 = (pd->peek()).str();
         pd->moveRearward();
      }
   }
   cout << "This is a valid chain." << endl;
   return true;
}

bool findChain(vector<PeekDeque<StringWrap> >* pd, StringWrap sw){
   
   for(int i = 0; i < pd->size();i++){
      pd->at(i).setPeekIndexToRear();
      if(ed1(pd->at(i).peek().str(),sw.str()) &&
              pd->at(i).peek().str().size() < sw.str().size()){//does not allow smaller words
         if(!pd->at(i).full()){
            pd->at(i).pushRear(sw);
         }
         return true;
         }//sw did not find have an edit distance of 1 with the rear item
      /*if(pd->at(i).peek().str() == sw.str()){
         return false;
      }*/
      pd->at(i).setPeekIndexToFront();
      if(ed1(pd->at(i).peek().str(),sw.str()) && 
              pd->at(i).peek().str().size() > sw.str().size() )//does not allow larger words
         {//if it does have an edit distance of 1
         if(!pd->at(i).full()){
            pd->at(i).pushFront(sw);
         }  
         return true;
         }
      /*if(pd->at(i).peek().str() == sw.str()){
         return false;
      }*/
     
   }//did not find a matching edit distance of 1, need to create a new peekdeque to hold this
   

   pd->push_back(PeekDeque<StringWrap>(100));
   pd->at(pd->size()-1).pushRear(sw);
   return true;
}

void findLongestChain(vector<PeekDeque<StringWrap> >* pd){
   vector<PeekDeque<StringWrap> >* longest = new vector<PeekDeque<StringWrap> >();
   //longest->push_back(pd->at(0));
   
   int max = 0;
   for(int i = 0; i < pd->size(); i++){//find largest chain size
      if(pd->at(i).size() > max){  
         max = pd->at(i).size();
         longest->clear(); 
         longest->push_back(pd->at(i));
}     else if(pd->at(i).size() == max){ //if the peekdeque size is equal to the max size found so far
         longest->push_back(pd->at(i)); //then add it to the "longest" vector
      }  
   }
   
   /*for(int i = 0; i < pd->size(); i++){//find the actual largest chain
      if(pd->at(i).size() == max)
         longest->push_back(pd->at(i));
   }*/
   cout << endl;
   cout << "Longest chain(s): " << endl;
   for(int i = 0; i < longest->size(); i++)
      cout << longest->at(i).toString() << endl << endl;
}
void findChainWithLongestWord(vector<PeekDeque<StringWrap> >* pd){
   int longest = 0;
   int longest2 = 0;
   int currentStringWrapSize, peekDequeSize;
   //bool hasLongerWord = false;
   vector<PeekDeque<StringWrap> >* temp = new vector<PeekDeque<StringWrap> >();
   vector<PeekDeque<StringWrap> >* temp2words = new vector<PeekDeque<StringWrap> >();

   for(int i = 0; i < pd->size(); i++){            //loop through each PeekDeque 
      pd->at(i).setPeekIndexToFront();      
      while(!pd->at(i).endOfPeek()){               //loop through each StringWrap in current PeekDeque

         currentStringWrapSize = pd->at(i).peek().str().size();
         peekDequeSize = pd->at(i).size();

         if(currentStringWrapSize >= longest2 && peekDequeSize > 1){

            if(currentStringWrapSize > longest2){
               temp2words->clear();
               temp2words->push_back(pd->at(i));
               longest2 = currentStringWrapSize;
          } else{
               temp2words->push_back(pd->at(i));
            }
       
       } else if(currentStringWrapSize > longest && peekDequeSize == 1){ //if this word is longer
                                                                     // than the current longest                                                                                      //clear the vector and start a new set of 
            temp->clear();                            //peekdeques that contain the longest StringWrap  
            temp->push_back(pd->at(i));
            longest = currentStringWrapSize;
            //hasLongerWord = true;

     }   else if(currentStringWrapSize == longest/* && !hasLongerWord*/){
            temp->push_back(pd->at(i));
         }
      pd->at(i).moveRearward();
      }

      //hasLongerWord = false;
   }

   //Print out the chains with the longest word(s)
   cout << "Chain(s) with longest word: " << endl;
   for(int i = 0; i < temp->size();i++){
      cout << temp->at(i).toString() << endl;
   }
   cout << "Chain(s) with longest word(minimum chains of 2 words): " << endl;
   for(int i = 0; i < temp2words->size(); i++){
      cout << temp2words->at(i).toString() << endl;
   }           
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
   vector<PeekDeque<StringWrap> >* chainsp = new vector<PeekDeque<StringWrap> >();//vector that holds all the word chains
   
   int wordCount = 0;
   string s1;

   while(*infilep >> s1 && wordCount < desiredWords ){
      
      if(s1.length() > 2){
         StringWrap sw(s1);
         sw.makeLower();      //format the string in StringWrap so it has no punctuation and is all lowercase letters
         sw.punctCorrect();
         findChain(chainsp,sw);
      }         

      wordCount++;

      }
   /*for(int i = 0; i < chainsp->size(); i++){
      cout << chainsp->at(i)->toString() << endl;
   } */  
   findLongestChain(chainsp);//outputs what the longest word chain is
   findChainWithLongestWord(chainsp); //outputs the chain with the longest words
      
   /*while(!pd->empty()){
      cout << (pd->popRear()).str() << endl;
   }
   //pd->setPeekIndex();
   */
   //testLegalChain(chainsp->peek());
   
   return 0;
}

