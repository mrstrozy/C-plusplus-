/** File "PeekDequeKWR.cpp", by KWR for CSE250 Spring 2014.  Assignment 3+4 answer.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

//#include <cmath>   //for fabs

using std::vector;
using std::endl;
using std::cerr;
using std::ostringstream;
using std::string;
using std::cout;


class PeekDeque;

class Deque {
   friend class PeekDeque;

   vector<string>* elements;
   int rearSpace;
   int frontItem;
   int upperBound;

   //CLASS INV: frontSpace indicates first empty cell for pushFront
   //           rearItem designates rear item (not space) for popRear---
   //           ---or if there is no such item, rearItem == frontSpace;

 public: 

   explicit Deque(int guaranteedCapacity) 
    : elements(new vector<string>(2*guaranteedCapacity)),
      frontItem(guaranteedCapacity),
      rearSpace(guaranteedCapacity),
      upperBound(2*guaranteedCapacity) 
   { }

   virtual ~Deque() { delete elements; cout << "It's Deque Season!" << endl; }

   virtual bool empty() const { return frontItem == rearSpace; }

   virtual bool full() const { return rearSpace == upperBound; }

   virtual size_t size() const { return rearSpace - frontItem; }

   virtual void pushFront(string newItem) {
      if (full()) {
         cerr << "Are you playing with a full Deque?" << endl;
         cerr << toString() << endl;
      } else {
         elements->at(--frontItem) = newItem;
      }
   }

   virtual void pushRear(string newItem) {
      if (full()) {
         cerr << "Are you playing with a full Deque?" << endl;
         cerr << toString() << endl;
      } else {
         elements->at(rearSpace++) = newItem;
      }
   }

   virtual string popFront() {
      if (empty()) {
         cerr << "Too lazy to throw an EmptyDequeException." << endl;
         return "";
      } else {
         return elements->at(frontItem++);
      }
   }

   virtual string popRear() {
      if (empty()) {
         cerr << "Too lazy to throw an EmptyDequeException." << endl;
         return "";
      } else {
         return elements->at(--rearSpace);  //translates Java "next()"
      }
   }

   virtual string toString() const { 
      ostringstream OUT;
      //string out = "";
      for (int i = frontItem; i < rearSpace; i++) {
         //out += elements->at(i).str() + " ";
         OUT << elements->at(i) << " ";
      }
      //return out;
      return OUT.str();
   }

};



class PeekDeque : public Deque {

   int peekIndex;

 public:

   explicit PeekDeque(int guaranteedCapacity)
    : Deque(guaranteedCapacity), peekIndex(frontItem) { }

   virtual ~PeekDeque() { cerr << "No peeking..."; } //automatically calls ~Deque()

   virtual void moveFrontward() { peekIndex--; }

   virtual void moveRearward() { peekIndex++; }

   virtual string peek() const { return elements->at(peekIndex); }

   virtual string popFront() { 
      if (empty()) { cerr << "Pop attempt from empty PeekDeque" << endl; }
      else return Deque::popFront();
   }

   virtual string popRear() {
      if (empty()) { cerr << "Pop attempt from empty PeekDeque" << endl; }
      else return Deque::popRear();
   }

   //Extra functionality

   virtual void setPeekToFront() { peekIndex = frontItem; }

   virtual bool atRear() const { return peekIndex == rearSpace; }

};
