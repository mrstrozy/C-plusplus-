#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

int main(){
   
   //string test = "245";
   int test = 7;
   double value = (double)test/3;
   cout << "This is to test a double. Here: " << setprecision(3) << value  << endl;
   return 0;
}
