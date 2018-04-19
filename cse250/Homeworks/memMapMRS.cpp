/**
 File "memMapMRS.cpp", by Matthew Strozyk for CSE250
*/




#include <string>
#include <iostream>
using namespace std;

int main(){

   string xsphost = "Jello";
   string ysphost = "Mello";
   string* xsp = &xsphost;
   string* ysp = &ysphost;
   ysp = xsp;
   xsp->at(0) = 'H';
   cout << "\nAs stack pointers xsp = " << xsp << " and ysp = " << ysp << endl; 
   cout << "Oops!---forgot to de-reference the pointers..." << endl;
   cout << "As stack pointers: *xsp = " << *xsp << " and *ysp = " << *ysp
        << endl;

   //Pointers to Anonymous (Heap) Objects
   string* xp = new string("Jello");
   string* yp = new string("Yello");
   yp = xp;
   xp->at(0) = 'H';
   cout << "\nAs heap pointers: xp = " << xp << " and yp = " <<  yp << endl;
   cout << "Oops!---forgot to de-reference the pointers..." << endl;
   cout << "As heap pointers: *xp = " << *xp << " and *yp = " << *yp << endl;

   return (0);
}


