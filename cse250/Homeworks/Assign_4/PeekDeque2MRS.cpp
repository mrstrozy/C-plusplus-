/*********************************************************************
*FileName: PeekDeque2MRS.cpp made by Matthew Strozyk for CSE250, 
*          assignment 4.
*
***********************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include "PeekDeque2MRS.h"

using namespace std;

StringDeque::StringDeque(int guaranteedCapacity): frontItem(guaranteedCapacity),
               rearSpace(guaranteedCapacity), upperBound(2*guaranteedCapacity),
               elements(new vector<string>(upperBound)){}

const bool StringDeque:: empty(){return rearSpace == frontItem;}//
const bool StringDeque::full(){
       return rearSpace == upperBound || frontItem == 0;
     }
const int StringDeque::size(){return rearSpace - frontItem;}
string StringDeque::popRear(){
  if(empty()){
    cerr << "Later we'll define and throw an EmptyQException" << endl;
    return "";
} else { return elements->at(--rearSpace);}
}
string StringDeque::popFront(){
  if(empty()){
    cerr << "Later we'll define and throw an EmptyQException" << endl;
    return "";
} else { return elements->at(frontItem++);}
}
void StringDeque::pushFront(string newItem){
  if(full()){
    cerr << "No more room to add more items" << endl;
} else {
    elements->at(--frontItem) = newItem;
  }
}
void StringDeque::pushRear(string newItem){
  if(full()){
    cerr << "No more room to add more items" << endl;
} else { elements->at(rearSpace++) = newItem;}
}
const string StringDeque::toString(){
  string out = "";
  for(int i = frontItem; i < rearSpace; i++) {
 }
  return out;
}


PeekDeque::PeekDeque(int guaranteedCapacity) : StringDeque(guaranteedCapacity) , peekIndex(guaranteedCapacity){}
const string PeekDeque::peek(){ return elements->at(peekIndex);}
void PeekDeque::moveFrontward(){
   if(peekIndex < 1){
      cout << "Cannot move any farther frontward." << endl;
 } else {
      peekIndex--;
 }
}
void PeekDeque::moveRearward(){
   if(peekIndex > (upperBound - 2)){
      cout << "Cannot move any farther rearward." << endl;
 } else {
      peekIndex++;
 }
}
string PeekDeque::popFront(){
   if(empty()){
      cerr << "Attempt to pop from empty PeekDeque." << endl;
      return "";
 } else {
     return elements->at(frontItem++);
  }
}
string PeekDeque::popRear(){
    if(empty()){
      cerr << "Attempt to pop from empty PeekDeque." << endl;
      return "";
  } else { return elements->at(--rearSpace);}
 }
const bool PeekDeque::endOfPeek(){ return peekIndex == rearSpace;}
void PeekDeque::setPeekIndex(){peekIndex = frontItem;}
                                                            


