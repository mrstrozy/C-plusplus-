#include <iostream>
#include <string>

using namespace std;

bool test(string,string);
bool test(string x,string y){
   string a,b;
   x.length() > y.length() ? (b = x , a = y) : (a =x, b = y);

   cout << "a is: " << a << " and b is: " << b << endl;
   return true;
}




int main(){
   string x = "hello";
   string y = "mell";
   test(x,y);
   return 0;
}
