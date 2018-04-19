#include <iostream>
#include <string>
#include <vector>
using namespace std;

class StringDeque{
    protected: 
      int frontItem, rearSpace, upperBound; //INV:frontItem is always on the first item in elements, rearSpace is always one space past the rear item 
      vector<string>* elements;

    public:
  
      StringDeque(int guaranteedCapacity): frontItem(guaranteedCapacity),
          rearSpace(guaranteedCapacity), upperBound(2*guaranteedCapacity),
          elements(new vector<string>(upperBound)){} 
     
      ~StringDeque(){
         cout << "Deconstructor called" << endl;
         delete elements;
      }
      virtual const bool empty(){return rearSpace == frontItem;}//
      virtual const bool full(){return rearSpace == upperBound || frontItem == 0;}
      virtual const int size(){return rearSpace - frontItem;}         
      virtual string popRear(){
        if(empty()){
          cerr << "Later we'll define and throw an EmptyQException" << endl;
          return "";
      } else { return elements->at(--rearSpace);}
     }
      virtual string popFront(){
        if(empty()){
          cerr << "Later we'll define and throw an EmptyQException" << endl;
          return "";
      } else { return elements->at(frontItem++);}
     }
      virtual void pushFront(string newItem){
        if(full()){
          cerr << "No more room to add more items" << endl;
      } else {
          elements->at(--frontItem) = newItem;
        }
      }
      virtual void pushRear(string newItem){
        if(full()){
          cerr << "No more room to add more items" << endl;
      } else { elements->at(rearSpace++) = newItem;}
     }
      virtual const string toString(){
        string out = "";
        for(int i = frontItem; i < rearSpace; i++) {
           out += elements->at(i) + " ";
        }
        return out;
     }   
 
};
/****
class PeekDeque : public StringDeque{

  private:
     int peekIndex;
  public:

    PeekDeque(int guaranteedCapacity) : StringDeque(guaranteedCapacity) , peekIndex(guaranteedCapacity){}
    const string peek(){ return elements->at(peekIndex);}
    void moveFrontward(){
       if(peekIndex < 1){
          cout << "Cannot move any farther frontward." << endl;
     } else {
          peekIndex--;
     }
    }
    void moveRearward(){
       if(peekIndex > (upperBound - 2)){
          cout << "Cannot move any farther rearward." << endl;
     } else {
          peekIndex++;
     }
    }   
   
    string popFront(){
       if(empty()){
          cerr << "Attempt to pop from empty PeekDeque." << endl;
          return "";
     } else {
         return elements->at(frontItem++);
      }
    }
    string popRear(){
        if(empty()){
          cerr << "Attempt to pop from empty PeekDeque." << endl;
          return "";
      } else { return elements->at(--rearSpace);}
     }
    void setPeekIndex(){peekIndex = frontItem;}
};
******/
int main(){
   
   StringDeque* sd = new StringDeque(100);
   sd->pushFront("oh");
   sd->pushFront("say");
   sd->pushFront("can");
   sd->pushFront("you");
   sd->pushFront("see");
   sd->pushRear("any");
   sd->pushRear("bad bugs");
   sd->pushRear("on");
   sd->pushRear("me?");
   cout << sd->toString() << endl;
   string pop2 = sd->popRear() + " " + sd->popRear();
   cout << pop2 + ", did this print in the right order?" << endl;
   sd->pushFront("I");
   cout << "Final deque: " + sd->toString() << endl;

/**
   PeekDeque* pd = new PeekDeque(100);
   pd->pushFront("oh");
   pd->pushFront("say");
   pd->pushFront("can");
   pd->pushFront("you");
   pd->pushFront("see");
   pd->pushRear("any");
   pd->pushRear("bad bugs");
   pd->pushRear("on");
   pd->pushRear("me,");
   pd->pushRear("Shoot");
   pd->pushRear("sammy");
   pd->pushRear("saints");
   pd->pushRear("Shall");
   pd->pushRear("strengthen");
   pd->setPeekIndex();  

   while(!pd->empty()){
   if((pd->peek()).at(0) == 's'){
     cout << pd->popFront() << endl;
      }
   else {
     pd->popFront();
      }
   pd->moveRearward();
   }    
         
********/   
   return 0;
}


//*************************************************
// After running both of the files I found that
// there was not much of a difference between the
// two. The only difference that I saw was that
// the c++ code had "on me?," and the java code
// had "me? on,". Other than that, there were no
// more differences.
//************************************************* 




