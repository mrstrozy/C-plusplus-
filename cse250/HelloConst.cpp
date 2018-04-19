/** File "HelloConst.cpp", by KWR for CSE250, Fall 2009.
    Illustrates C++ pointer types combined with "const".
    Which combinations correspond to Java String and StringBuffer?

    Also illustrates various g++ compiler errors.
 */

#include<iostream>
using namespace std;

int main() {

   //Pointers to Anonymous (Heap) Objects
   string* xp = new string("Jello");
   string* yp = new string("Bello");
   yp = xp;
   xp->at(0) = 'H';
   cout << "As unqualified pointers: " << *xp << " " << *yp << endl;

   //Pointers to Constant Data
   const string* xpcd = new string("Jello");
   const string* ypcd = new string("Bello");
   //const string* zpcd = ypcd;
   //ypcd = xpcd;
   //cout << "Value of zpcd before change: " << *zpcd << endl;
   //ypcd->at(0) = 'Z';
   cout << "\nAs constant pointers: " << *xpcd << " " << *ypcd << endl;

   //Constant Pointers
   string* const xcp = new string("Jello");
   string* const ycp = new string("Bello");
   //string* ycp const = new string("Jello");  //allowed by some compilers?
   //ycp = xcp;
   xcp->at(0) = 'H';
   cout << "\nAs pointers to const: " << *xcp << " " << *ycp << endl;

   //Const Pointers to Const
   const string* const xcpc = new string("Jello");
   const string* const ycpc = new string("Bello");
   //ycpc = xcpc;
   //xcpc->at(0) = 'H';
   cout << "\nAs const pointers to const: " << *xcpc << " " << *ycpc << endl;

   return(0);
}
   
