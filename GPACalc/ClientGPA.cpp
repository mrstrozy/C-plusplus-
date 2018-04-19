#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include "GPA.cpp"
using namespace std;

int main(int argc,char** argv){



   cout << endl <<  "FORMAT FOR FILE INPUT: [LETTER] [CREDITS]" << endl << endl;;


   double totalSum = 0;//total sum of all the credits
   double gpaSum = 0;  //total points received     GPA == gpaSum/totalSum
   vector<GPA>* gpaBase = new vector<GPA>();
   vector<string>* args = new vector<string>(argc);
   string inGrade = "";
   string inCredit = "";

   for(int i = 0; i < argc; i++) {
      args->at(i) = *(argv + i);
   }
   
   istringstream INS;
   string infileName;
   ifstream* infilep;



   if(argc >= 2) {//if they DO input a file name
      infileName = args->at(1);
      infilep = new ifstream(infileName.c_str(), ios_base::in);
      if (! infilep->is_open()) {
         cerr << "Unable to open file: " << infileName << endl;
         return(1);
      }


   *infilep >> inGrade;
   while(*infilep >> inCredit){
      gpaBase->push_back(GPA(inGrade,atof(inCredit.c_str())));
      *infilep >> inGrade;
   }

   for(int i = 0; i < gpaBase->size();i++){
      totalSum += gpaBase->at(i).getWeight();
      gpaSum += gpaBase->at(i).getPoints();
      cout << gpaBase->at(i) << endl;
   }
   GPA final(gpaSum/totalSum , 0);
   cout << endl <<  "Final GPA----> Value: "
        << setprecision(2) << fixed << gpaSum/totalSum << endl << endl;


//if the user DOESN'T input a file name
    } else {
      string choice = "";
      
      
      while(choice != "no"){
         if(choice == "yes" || choice == ""){
            cout << "Please input a grade letter: ";
            cin >> inGrade;
            cout << "Please input credit value: ";
            cin >> inCredit;
            cout << endl;
            gpaBase->push_back(GPA(inGrade,atof(inCredit.c_str()))); 
       } else {
         cout << "Invalid input." << endl;
         }
         cout << "Enter another grade?(yes/no): ";
         cin >> choice;
         cout << endl;
      }
      for(int i = 0; i < gpaBase->size();i++){
         totalSum += gpaBase->at(i).getWeight();
         gpaSum += gpaBase->at(i).getPoints();
         cout << gpaBase->at(i) << endl;
      }
      cout << endl << "Final GPA----> Value: " << setprecision(2) << fixed
           << gpaSum/totalSum << endl << endl;
      
   } 
   return 0;
}
