#include <iostream>
#include <string>
using namespace std;

int main(){

   cout << "Enter your name: ";
   string name;
   getline(cin,name);
   cout << "Hello " << name << " - welcome to C++" << endl;
  
   return 0;
}
