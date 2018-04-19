/** File "npos.cpp", by KWR for CSE250, Fall 2009.
    Illustrates actual C++ standard library usage of a "magic number".
    The actual number even has different +ve values on different CSE machines!
    But it's "int" value is always supposed to be -1, IMHO dangerously...
    Also illustrates prefixes when you don't use "using" statements.
    
 */

#include<iostream>
#include<string>

int main() {
   int n = std::string::npos;
   std::cout << "npos as raw size_t value: " << std::string::npos << std::endl;
   std::cout << "npos as signed int value: " << n << std::endl;
   if (std::string::npos == -1) {
      std::cout << "It's a Magic Number!" << std::endl;
   }
   return(0);
}

