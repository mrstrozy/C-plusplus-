#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char*argv[]){
    int countl = 0;
    if(argc <= 1){
       cerr << "Usage: Enter name of file after executable." << endl;
       exit(1);
    }
    ifstream in(argv[1]);

    if(!in){
       cerr << "File not found." << endl;
       exit(1);
    }
    string str;
    while(in){
    getline(in,str);
    countl++;
    } 
    cout << "number of lines is: " << countl << endl;
    return 0;
}
      
