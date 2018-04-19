/** File "PointerDangers2.cpp" by KWR for CSE250, Spring 2013.
    Example of a dangling pointer error---an uncaught one, which is worse.
    Note the warning you get when you compile, at least on timberlake...
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



int main() {
    Point* cat1 = disappoint(2.0,3.0);
    Point* cat2 = disappoint(6.5,7.5);

    //cout << "cat1 = " << cat1 << "; and cat2 = " << cat2 << endl;
    //Commenting-in this bad line as per Assgt. 1 shows a clue!

    cout << "cat1 = " << (*cat1) << "; and cat2 = " << (*cat2) << endl;
    cout << "Copycats?  More like alley cats digging \"garbage\"!" << endl;

    cat1 = onpoint(2.0,3.0);
    cat2 = onpoint(6.5,7.5);
    cout << endl << "Cool cats now: " << endl;
    cout << "cat1 = " << (*cat1) << "; and cat2 = " << (*cat2) << endl;

    return 0;
}
   
