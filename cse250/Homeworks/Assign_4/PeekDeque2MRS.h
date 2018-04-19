/*********************************************************************
*FileName: PeekDeque2MRS.h made by Matthew Strozyk for CSE250, 
*          assignment 4.
*
***********************************************************************/
#ifndef PEEK_DEQUE_H
#define PEEK_DEQUE_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StringDeque{
    protected:
       int frontItem, rearSpace, upperBound;
       vector<string>* elements;

    public:

       StringDeque(int guaranteedCapacity);
       virtual const bool empty();
       virtual const bool full();
       virtual const int size();
       virtual string popRear();
       virtual string popFront();
       virtual void pushFront(string newItem);
       virtual void pushRear(string newItem);
       virtual const string toString();
};

class PeekDeque : public StringDeque{
    private:
       int peekIndex;
    public:
       PeekDeque(int guaranteedCapacity);
       const string peek();
       void moveFrontward();
       void moveRearward();
       string popFront();
       string popRear();
       const bool endOfPeek();
       void setPeekIndex();
};
#endif
