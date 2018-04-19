/** File "StackPairKWR.h", by KWR for CSE250, Spring 2013.  Assignment 4 answer.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <cmath>

using std::vector;
using std::endl;
using std::cerr;
using std::ostringstream;
using std::string;

template <typename T> //REQ: T defines T() and has operator<< defined for it.
class StackPair {
   vector<T>* elements;
   size_t topSpaceA;  //lives at 0
   size_t topItemB;   //starts at n which means stack B is empty
   size_t capacity;

   //CLASS INV: topSpaceA denotes first free cell of StackA, initially 0
   //           topItemB denotes lowest-numbered item, initially n for empty
   //           Always topSpaceA <= topItemB; diff is # of free cells.

 public: 

   explicit StackPair<T>(size_t maxAdds) 
    : elements(new vector<T>(maxAdds)),
      topSpaceA(0),
      topItemB(maxAdds),
      capacity(maxAdds)
   { }

   StackPair<T>()
    : elements(new vector<T>(100)),
      topSpaceA(0),
      topItemB(100),
      capacity(100)
   { }


   virtual ~StackPair<T>() { delete elements; }

   //KWR: OK to have methods non-virtual; the course de-emphasizes inheritance.
   virtual bool emptyA() const { return topSpaceA == 0; }
   virtual bool emptyB() const { return topItemB == capacity; }

   virtual bool full() const { return topSpaceA == topItemB; }

   virtual size_t sizeA() const { return topSpaceA; }
   virtual size_t sizeB() const { return capacity - topItemB; }
   virtual size_t size() const { return sizeA() + sizeB(); }

   virtual void pushA(const T& newItem) {
      elements->at(topSpaceA++) = newItem;
   }

   virtual T popA() {
      return elements->at(--topSpaceA);
   }

   virtual void pushB(const T& newItem) {
      elements->at(--topItemB) = newItem;
   }

   virtual T popB() {
      return elements->at(topItemB++);
   }

   /** Optional: imposes REQ on T of printability (or stringability).
    */
   virtual string toString() const { 
      ostringstream OUT;
      //string out = "";
      for (int i = 0; i < capacity; i++) {
         //out += elements->at(i).str() + " ";
         OUT << elements->at(i) << " ";
      }
      //return out;
      return OUT.str();
   }
};

