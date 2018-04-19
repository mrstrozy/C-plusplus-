#include <iostream>
#include <string>
#include "MovieBaseMRS.h"
using namespace std;

int main(){
   MovieBase base("u.item","u.genre","u.data");
   cout << base << endl;
   return 0;
}
