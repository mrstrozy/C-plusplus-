/**File HelloWorld.java, by KWR for CSE250, Fall 2009.
   Java and C++ code, illustrates behavioral differences.

// #if(0)
/*-------------------------------------------------------*/
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
      Base foo = der;  //new Base();
      System.out.println(foo.greet(a.toString()));
   }
}
/*-------------------------------------------------------
//#endif

#include<iostream>
using namespace std;
class Base {
 public:
   string greet(string first) {
      return first + " World!";
   }
};
class Derived : public Base {
 public:
   string greet(string ignored) {
      return "Hello World!!";
   }
};
int main() {
   string a = "Jello";
   string b = a;
   b[0] = 'H';
   Derived der;
   Base foo = der;
   cout << foo.greet(a) << endl;
}
//---------------------------------------------------*/
