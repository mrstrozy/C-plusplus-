/*********************************************************************
*FileName: PeekClientMRS.cpp made by Matthew Strozyk for CSE250, 
*          assignment 4.
*
***********************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include "PeekDeque2MRS.h"

using namespace std;

bool hd1(string,string); 
bool ed1(const string&,const string&);
bool testLegalChain(PeekDeque*);

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
              cout << "Temp: " << temp << " xc: " << xc << endl;
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

/********************************************************************************************
*I think it would be really nice having a peek index variable at both the front and the rear
*of the PeekDeque as it would allow you to see both from what you put in first and what was
*put in last. In order to do this, I would just have to create another variable and give it 
*it's own functions that would be able to move it both frontward and rearward. Along with this
*I would make it so that one follows where the frontItem is and the other variable follows where 
*the rear item is. If the peekIndex were an object that would be much more convenient. I would 
*be able to manipulate it much more as well as be able to see, as the end user, where exactly 
*I am peeking.
*
*********************************************************************************************/ 
