#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ofstream outf("sample.txt");

  if(!outf){
    
    cerr << "File could not be created" << endl;
    return 1;
  }

  outf << "I am testing to see if this is writing" << endl;
  outf << "If this is writing then it is working" << endl;
  
  //If you do not close the opened file, you will not be able to open
  //it from anywhere else until it is closed
  outf.close();

  return 0;

}
