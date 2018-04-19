/**************************************************
* File "PeekDequeMRS.cpp", by MRS for CSE250, Spring 2014.  
**************************************************/



#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

bool hd1(string,string);
bool ed1(const string&,const string&);
bool ed1(const string& x,const string& y){
    string xc, yc;
    if(x.size() > y.size()){
       xc = x;
       yc = y;
  } else {
       xc = y;
       yc = x;
    }
    if(xc == "" || yc == "")
       return false;
    if(xc.size() - yc.size() > 1)
       return false;
    if(xc.size() == yc.size())
       return hd1(xc,yc);


    //strings are exactly 1 char apart with xc being the larger string

    if(xc[0] == yc[0] && xc[xc.size()-1] == yc[yc.size()-1]){
       for(int i = 1; i < xc.size()-1; i++){
          if(xc[i] != yc[i]){
             string temp = "";
             for(int j = 0; j < yc.size(); j++){
                if(j != i){
                   temp += yc[j];
              } else {
                   temp += '!';
                   temp += yc[j];
                }
             }//Both strings have the same size          
             return hd1(temp,xc);
          }
       }//First and Last Char were not the same
  } else if(xc[0] == yc[0]){
       string temp = yc;
       temp += '!';
       return hd1(temp,xc);
  } else {
       string temp = "!";
       temp += yc;
       return hd1(temp,xc);
    }
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
    bool endOfPeek(){ return peekIndex == rearSpace;}
    void setPeekIndex(){peekIndex = frontItem;}
};
bool testLegalChain(PeekDeque*);
bool testLegalChain(PeekDeque* pd){

   string s1;
   string s2;
   s1 = pd->peek();
   pd->moveRearward();
   s2 = pd->peek();
   pd->moveRearward();

   while(!pd->endOfPeek()){
      cout << s1 << " " << s2 << endl;
      if(!ed1(s1,s2)){
         cout << "This is not a legal chain." << endl;
         return 0;
    } else {
         s1 = s2;
         s2 = pd->peek();
         pd->moveRearward();
      }
   }
   cout << "This is a valid chain." << endl;

}
int main(){
   
/*   StringDeque* sd = new StringDeque(100);
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
  */
   PeekDeque* pd = new PeekDeque(100);       
   ifstream in("words.txt");

   if(!in){
      cerr << "The file could not be opened." << endl;
      return 1;
   } 
   //File is valid and has been opened for reading 
   
   string s1;
   while(in){
      in >> s1;
      pd->pushRear(s1);
      }
   testLegalChain(pd);
   return 0;
}






