///C++: file Complex.h shown here;
#include <cmath> ///needed only in .cc file with .sqrt 
///ANSI revision of older library <math.h>

class Complex{                                               
private: ///top of class automatically private
   double xx;
   double yy;
public:
   Complex(double x, double y)
      : xx(x), yy(y)  ///constructor initializer syntax...
   {}
   double getxx() const {return xx;}
   double getyy() const {return yy;}
   double norm() const; ///  (*)
   Complex operator+(Complex y) const; 
   ///Usage: x + y or x.operator+(y).  C++ would automatically 
   ///understand the infix + as calling x's member function,, BUT
   ///also can write operators "outside the class" for symmetry.

}; ///Famous gotcha: in C++, classes must end with a ";"!
