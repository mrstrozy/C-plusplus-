/** File "callbyref.cpp", by KWR for CSE250, Fall 2010.
    Illustrates call by reference, as a way to 'return" 2 or more values.
 */

#include <string>
#include <iostream>

void cbr(int& x, std::string& st) {  //absence of "const" means intent to modify
   x = 2;
   st = "Goodbye ";
}

int main() {
   int xArg = 1;
   std::string stArg = "Hello ";
   std::cout << stArg << xArg << std::endl;
   cbr(xArg,stArg);
   std::cout << stArg << xArg << std::endl;
}
