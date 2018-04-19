/** File "wordturn2KWR.cpp", by KWR for CSE250, Spring 2013.
    Assignment 4(5) answer key, together with StackPairKWR.h
    Does not need makefile, compile as g++ -o wordturn2 wordturn2KWR.cpp
 */

#include <vector>
#include <string>
#include <iostream>
#include "StackPairKWR.h"

using namespace std;


int main(int argc, char** argv) {
   if (argc != 2) {
      cout << "Usage: wordturn2 word" << endl;
      return 1;
   }
   string word(argv[1]);
   StackPair<char> sp(100);
   
   size_t n = word.size();
   size_t left = 0;
   size_t right = n-1;
   while (left < right) {    //leaves middle char un-pushed
      sp.pushA(word[left]);
      sp.pushB(word[right]);
      left++; right--;
   }
   //POST: left==right if word has odd length, else right==left-1
   string result = word;  //to be overwritten
   size_t left2 = 0;
   size_t right2 = n-1;
   while (left2 < right2) {  //note similarity of loop but inside-out results
      result[left2] = sp.popA();
      result[right2] = sp.popB();
      left2++; right2--;
   }
   //middle char of odd-length word will be same as before.

   cout << "Inside-out(" << word << ") = " << result << endl;
   return 0;
}
   
      
   
