#include <iostream>
#include <string>
#include "MovieBaseMRS.h"
using namespace std;

int main(){

   MovieBase test("u.item","u.genre","u.data");
   cout << test << endl;
   return 0;
}
