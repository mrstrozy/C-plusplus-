#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ofstream out("Testfile.txt");

  if(!out){
    cerr << "The file could not be created." << endl;
    return 1;
  }

  out << "This is working" << endl;
  out << "I hope that this is all working" << endl;
  out.close();

  ifstream in("Testfile.txt");

  if(!in){
    cerr << "The file could not be opened" << endl;
    return 1;
  }

  string str;

  while(in){
  getline(in,str);
  cout << str << endl;
  }

  return 0;
}
