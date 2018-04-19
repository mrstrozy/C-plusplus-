/** File "HelloString.cpp", by KWR for CSE250, Fall 2009.
    Illustrates value, pointer, and reference types, with & without const.
    Which combinations correspond to Java String and StringBuffer?
    Also illustrates various g++ compiler errors.
 */

#include<iostream>
using namespace std;

int main() {
   // Values
   string xv = "Jello";
   string yv = "Bello";
   yv = xv;
   xv[0] = 'H';
   cout << "As values: " << xv << " " << yv << endl;

   // References   //DON'T do this---except for reference parameters
   //string& xr = "Jello";
   //string& yr = "Bello";
   string xhost = "Jello";
   string yhost = "Bello";
   string& xr = xhost;  //creates an alias, does *not* copy the value
   string& yr = yhost;
   yr = xr;    //copies the *value* "Jello", overwriting "Bello"
   xr[0] = 'H';
   cout << "\nAs C++ references: " << xr << " " << yr << " " << xhost;
   cout << " And yhost = " << yhost << endl;

   // Const references
   const string& xcr = "Jello";//Why is this legal when inits of xr,yr are not?
   const string& ycr = "Bello";
   //ycr = xcr;   //const ref can't change its host
   //xcr[0] = 'H';//and can't be used to mutate either.
   cout << "\nAs C++ const refs: " << xcr << " " << ycr << endl;

   //Pointers to Named (Stack) Objects
   string xsphost = "Jello";   //could have done same thing with xhost
   string ysphost = "Bello";   //and yhost; "sph" == "stack pointer host"
   string* xsp = &xsphost;     //points at existing object, not "new" object
   string* ysp = &ysphost;     // & is read "address of" or "alias of"
   ysp = xsp;  //copies the address value, "5004" in slides
   xsp->at(0) = 'H';
   cout << "\nAs stack pointers: " << xsp << " " << ysp << endl;
   cout << "Oops!---forgot to de-reference the pointers..." << endl;
   cout << "As stack pointers: " << *xsp << " " << *ysp << endl;

   //Pointers to Anonymous (Heap) Objects
   string* xp = new string("Jello");
   string* yp = new string("Bello");
   yp = xp;  //copies the pointer value, i.e. Java reference, not object itself
   xp->at(0) = 'H';   //xp[0] is a sometimes-indulged error.
   cout << "\nAs heap pointers: " << xp << " " << yp << endl;
   cout << "Oops!---forgot to de-reference the pointers..." << endl;
   cout << "As heap pointers: " << *xp << " " << *yp << endl;

   return (0);
}
   
