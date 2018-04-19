C++: file Complex.h shown here;
#include <cmath> ///needed only in .cc file with .sqrt 
class Complex{                                               
private: ///top of class automatically private
   double r; //radius
   double theta;//angle
public:
   Complex(double x, double y)
      : xx(x), yy(y)  ///constructor initializer syntax...
   {}
   double getxx() const {return r*cos(theta)}; /// only need to change the implementation
   double getyy() const {return r*sin(theta)};  /// only need to change the implementation
   double norm() const{ return r}; /// only need to change the implementation 
   Complex operator+(y: Complex) const; /// only need to change the implementation
   
}; 
