/**File HelloJava.cpp, by KWR for CSE250, Fall 2009.
   Exact (pretty much) translation of the Java code.
   Is also "const-correct".
 */

#if(0)
-------------------------------------------------------*/
class Base {
   public String greet(String first) {
      return first + " World!";
   }
}
class Derived extends Base {
   public String greet(String ignored) {
      return "Hello World!!";
   }
}
class HelloWorld {
   public static void main(String[] args) {
      StringBuffer a = new StringBuffer("Jello");
      StringBuffer b = a;
      b.setCharAt(0,'H');
      Derived der = new Derived();
      Base foo = der;
      System.out.println(foo.greet(a.toString()));
   }
}
/*-------------------------------------------------------*/
#endif

#include<iostream>
using namespace std;
class Base {
 public:
   virtual string greet(const string* first) const {
      return (*first) + " World!";
   }
};
class Derived : public Base {
 public:
   virtual string greet(const string* ignored) const {
      return "Hello World!!";
   }
};
int main() {
   string* a = new string("Jello");
   string* b = a;
   b->at(0) = 'H';
   //Derived der;
   //Derived& der;  //allowed by Sun CC, nixed by g++
   //const Derived& der = Derived();
   //Base& foo = der;
   //Base& foo = (Base&)der;    //cast away const, needed by g++
   Derived* der = new Derived();
   Base* foo = der;
   //cout << foo.greet(a) << endl;
   cout << foo->greet(a) << endl;
}
//---------------------------------------------------*/
