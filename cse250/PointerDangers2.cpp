/** File "PointerDangers2.cpp" by KWR for CSE250, Spring 2013.
    Example of a dangling pointer error---an uncaught one, which is worse.
    Adds to the basic file a test of whether your compiler allows 
    operator<< to take a pointer argument.
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Point {   //plain old data
   double x;
   double y;
   Point(double gx, double gy) : x(gx), y(gy) { }
   //no need to "friend" an operator as everything is public.
};

ostream& operator<< (ostream& out, const Point& pt) {
   out << "Point(" << pt.x << "," << pt.y << ")";
   return out;
}

/** Return dangling pointer to a disappearing Point.
 */
Point* disappoint(double gx, double gy) { 
    Point cheshireCat(gx,gy);
    return &cheshireCat;
}

/** Return valid pointer to "new"ed object on heap
    ---which is what you do whenever you return an object in Java.
 */
Point* onpoint(double gx, double gy) {
    Point* cheshireCat = new Point(gx,gy);
    return cheshireCat;
}

/** Calling this MAY change the values of the cats...
 */
void overwriteStack() {
   double a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8;
   cout << "int(3)/int(5) = " << int(c)/int(e) << endl;   //just for an effect.
}



//#if(0)
/** Comment this in to test your compiler just-because...  This will not
    be important in any assignment, and should be regarded as dicey.
 */
ostream& operator<< (ostream& out, const Point* pt) {
   out << "Point(" << pt->x << "," << pt->y << ")";
   return out;
}
//#endif


int main() {
    Point* cat1 = disappoint(2.0,3.0);
    overwriteStack();
    Point* cat2 = disappoint(6.5,7.5);

    //cout << "cat1 = " << cat1 << "; and cat2 = " << cat2 << endl;
    //Does this line still show the addresses of your pointers?  See below.

    overwriteStack();  //once upon a time this made a difference...

    cout << "cat1 = " << (*cat1) << "; and cat2 = " << (*cat2) << endl;
    cout << "Copycats?  More like alley cats digging \"garbage\"!" << endl;

    cat1 = onpoint(2.0,3.0);
    cat2 = onpoint(6.5,7.5);
    cout << endl << "Cool cats now: " << endl;
    cout << "cat1 = " << (*cat1) << "; and cat2 = " << (*cat2) << endl;

    cout << endl << "What if I try the overloaded pointer version of op<<?"
         << endl;
    cout << "cat1 = " << cat1 << "; and cat2 = " << cat2 << endl;

    return 0;
}
   
