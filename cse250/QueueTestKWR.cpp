/** File "QueueTest.cpp", by KWR for CSE250, Fall 2010.  Assignment 2 answer.
    Also has lines of possible relevance to Assignment 3 (from its answer key)
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>  //for Assgt. 3, actually

#include <cmath>    //for "fabs" on Assgt. 3, if you use it (note: it's wonky)
                    //you may need to do fabs(double(-------)) to disambiguate

using namespace std;

//class StringDeque;//You MAY need this for Assgt. 3 on your home compiler

class StringQueue {
 public:
   //class StringDeque;  //Causes weird errors on "timberlake"; don't know why
   friend class StringDeque;

 private:
   vector<string>* elements;
   int frontSpace;
   int rearItem;
   int maxAdds;

   //CLASS INV: frontSpace indicates first empty cell for pushFront
   //           rearItem designates rear item (not space) for popRear---
   //           ---or if there is no such item, rearItem == frontSpace;

 public: 

   StringQueue(int maxAdds) 
    : elements(new vector<string>(maxAdds)),
      frontSpace(0),
      rearItem(0),
      maxAdds(maxAdds) 
   { }

   virtual bool isEmpty() const { return frontSpace == rearItem; }

   virtual bool isFull() const { return frontSpace == maxAdds; }

   virtual int size() const { return frontSpace - rearItem; }

   virtual void pushFront(string newItem) {
      elements->at(frontSpace++) = newItem;
   }

   virtual string popRear() {
      if (isEmpty()) {
         cerr << "Later we'll define and throw an EmptyQException" << endl;
         return "";
      } else {
         return elements->at(rearItem++);  //translates Java "next()"
      }
   }

   virtual string toString() const { 
      string out = "";
      for (int i = rearItem; i < frontSpace; i++) {
         out += elements->at(i) + " ";
      }
      return out;
   }
};

      

int main() {
   StringQueue* sq = new StringQueue(100);
   sq->pushFront("oh");
   sq->pushFront("say");
   sq->pushFront("can");
   sq->pushFront("you");
   sq->pushFront("see");
   cout << sq->toString() << endl;
   string pop2 = sq->popRear() + " " + sq->popRear();
   cout << pop2 + ", did this print in the right order?" << endl;
   sq->pushFront("me?");
   cout << "Final queue: " + sq->toString() << endl;


   //Extra lines, as on Assignment 3 (delete above lines of course)
   //...declare and construct an empty StringDeque.

   string infileName = "words.txt";
   ifstream* INFILEp = new ifstream(infileName.c_str(), ios_base::in);
   string word;

   while(getline(*INFILEp, word)) {
      //...
      //you write the loop body.
      //...
   }
   //...other lines if you desire
   //call toString() on your final deque and print it out.
   INFILEp->close();
}
