#include <iostream>
#include <fstream>

using namespace std;

int main(){

   ifstream input("sample.txt");

   if(!input){
      cerr << "File could not be opened or read." << endl;
      return 1;
   }


   string str;
   while(input){
   getline(input,str);
   //if(str.at(0) == 's')
   cout << str << endl;
   }

  return 0;
}
