#include <iostream>
#include <string>
#include "FlexArrayMRS.h"

using namespace std;

int main(){
   FlexArray<string> flex(40);
   FlexArray<string>::iterator it = flex.begin();
   
   for(int i = 0; i < 10; i++){
      it = flex.insert(it,"hey");
   }
   cout << "the size is: " << flex.size() << endl;
   return 0;
   }
