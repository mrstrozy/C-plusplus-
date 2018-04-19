#include <iostream>
#include <string>

using namespace std;

int main() {
   cout << "Enter your name, followed by carriage return.\n";
   string name;
   getline(cin,name);
   cout << "Hello " << name << ", welcome to C++.\n";
   return 0;
}
