/**File HelloWorld.cpp, by KWR for CSE250, Fall 2009.
   Java and C++ code, illustrates behavioral differences.
   This time the C++ code has been modified to emulate the Java code,
   by declaring methods "virtual" and invoking them thru /pointers/.
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
   virtual string greet(string first) {
      return first + " World!";
   }
};
class Derived : public Base {
 public:
   virtual string greet(string ignored) {
      return "Hello World!!";
   }
};
int main() {
   string a = "Jello";
   string b = a;
   b[0] = 'H';
   Derived der;
   //Derived& der;  //allowed by Sun CC, nixed by g++
   //const Derived& der = Derived();
   Base foo = der;
   //Base& foo = der;   //KISS: No Top-Level Aliases---& in Params Only
   //Base& foo = (Base&)der;    //cast away const, needed by g++
   Derived* derp = new Derived();
   Base* foop = derp;
   cout << foo.greet(a) << endl;
   cout << foop->greet(a) << endl;
}
//---------------------------------------------------*/
