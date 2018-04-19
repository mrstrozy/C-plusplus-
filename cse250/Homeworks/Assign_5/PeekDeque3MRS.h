/*********************************************************************
*FileName: PeekDeque3MRS.h made by Matthew Strozyk for CSE250, 
*          assignment 5.
*
***********************************************************************/
#ifndef DEQUETEMPLATETEST_H_
#define DEQUETEMPLATETEST_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


template <typename T>
class PeekDeque;

template <typename T>
class Deque{

int frontItem, rearSpace, upperBound;
vector<T> elements;

public:
  

   friend class PeekDeque<T>;
   explicit Deque<T> (int guaranteedCapacity): frontItem(guaranteedCapacity),
               rearSpace(guaranteedCapacity), upperBound(2*guaranteedCapacity),
              elements(upperBound){}

   Deque<T>(vector<T>* elem) : elements(elem->size()) {
      for(int i = 0; i < elem->size();i++){
         elements.push_back(elem->at(i));
      }
   }
   const bool empty(){return rearSpace == frontItem;}//
   const bool full(){
       return rearSpace == upperBound || frontItem == 0;
     }
   const int size(){return rearSpace - frontItem;}
   T popRear(){
     if(empty()){
       cerr << "Later we'll define and throw an EmptyQException" << endl;
       return "";
   } else { return elements.at(--rearSpace);}
   }
   T popFront(){
     if(empty()){
       cerr << "Later we'll define and throw an EmptyQException" << endl;
       return "";
   } else { return elements.at(frontItem++);}
   }
   void pushFront(T newItem){
     if(full()){
       cerr << "No more room to add more items" << endl;
   } else {
       elements.at(--frontItem) = newItem;
     }
   }
   void pushRear(T newItem){
     if(full()){
       cerr << "No more room to add more items" << endl;
       //cout << "Resizing..." << endl;
       //elements.resize(2*elements.size());
       //upperBound = elements.size();
       //elements.at(rearSpace++) = newItem; 
   } else { 
       elements.at(rearSpace++) = newItem;}
   }
   const string toString(){
     ostringstream OUT;
     for(int i = frontItem; i < rearSpace; i++) {
        OUT << elements.at(i) << " ";
     }
     return OUT.str();
   }
      
};

template <class T>
class PeekDeque : public Deque<T> {

int peekIndex;

public:

   explicit PeekDeque<T>(int guaranteedCapacity) : Deque<T>(guaranteedCapacity) , peekIndex(guaranteedCapacity){}
   const T peek(){ return this->elements.at(peekIndex);}
   void moveFrontward(){
      if(peekIndex < 1){
         cout << "Cannot move any farther frontward." << endl;
    } else {
         peekIndex--;
    }
   }
   void moveRearward(){
      if(peekIndex == this->upperBound){
         cout << "Cannot move any farther rearward." << endl;
         cout << this->elements.at(peekIndex) << endl;
    } else {
         peekIndex++;
    }
   }
   T popFront(){
      if(this->empty()){
         cerr << "Attempt to pop from empty PeekDeque." << endl;
         return "";
    } else {
        return this->elements.at((this->frontItem)++);
     }
   }
   T popRear(){
       if(this->empty()){
         cerr << "Attempt to pop from empty PeekDeque." << endl;
         return T("Heyu");//WHAT DO I DO HERE???????***********************************************
     } else { return this->elements.at(--(this->rearSpace));}
    }
   const bool endOfPeek(){ return peekIndex == this->rearSpace;}
   void setPeekIndexToFront(){peekIndex = this->frontItem;}
   void setPeekIndexToRear(){peekIndex = (this->rearSpace) - 1;} 

};                                                            

#endif
/*int main(){
   
   PeekDeque<StringWrap>* pd = new PeekDeque<StringWrap>(50);
   while(!pd->full()){
      pd->pushRear(StringWrap("hey"));
   }
   int i = 1;
   while(!pd->empty()){
   //StringWrap sw(pd->popRear()); 
   cout << (pd->popRear()).str() << " : " << i <<  endl;
   i++;
   }
  while(!pd->empty()){
      cout << pd->popRear() << " :  " << i << endl;
      i++;
   }

   cout << "Processes completed." << endl;
   return 0;
}*/
