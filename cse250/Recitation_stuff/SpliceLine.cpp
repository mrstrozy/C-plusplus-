#include <iostream>
#include <string>
#define MAX(x,y) \
        ((x)>(y) ? (x) : (y))
using namespace std;

int main(){

   string str = "today is "\
                "wednesday";
                      
   // "\" acts as a line splice that continues onto the next line
   cout << str;
   for(int i = 0; i<\
             10; i++){
   cout << i << " ";
   }
   cout << endl;
   cout << MAX(2,3) << endl;

   return 0;
}
