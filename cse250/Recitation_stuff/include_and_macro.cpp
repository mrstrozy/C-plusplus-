#include <iostream>
#define N 5
#define MAX(x,y) ((x)>(y) ? (x) : (y) )


using namespace std;

int main(){

   cout << "max(2,3) : " << MAX(2,3) << endl;
   int a = 9, b = 4, sum = 0;
   cout << "Max(" << a <<"," << b << ") = " << MAX(a,b) << endl;
   for(int i = 1; i < N; i++){
      cout << "Enter a Number: ";
      cin >> a;
      sum += a;
   }
   cout << "sum of those numbers comes out to be: " << sum << endl;
 
   return 0;
}
