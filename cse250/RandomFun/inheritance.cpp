#include <iostream>

using namespace std;


class Square{
  
  friend class Rectangle;
  private:
    int side;

  public:

    Square(int x):side(x){}
    int area(){return side*side;}
}
class Rectangle{
  private:
  int length , width;
  public:
    Rectangle(int x, int y):length(x) , width(y){}
  int area(){return x*y;}
}
