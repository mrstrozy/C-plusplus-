#include <iostream>
#include <string>
#include "GPA.h"
using namespace std;
   //If a letter is given
GPA::GPA(string newLetter,double weight):weight(weight),letter(newLetter){ 
      setValue(newLetter);//Give value from letter grade
      calculatePoints();
   } 

   //if a value is given
GPA::GPA(double newValue,double weight):weight(weight),value(newValue){
      checkValue(newValue); //Set a correct value
      setLetter(value);  //Give the letter grade per value
      calculatePoints();
   }
void GPA::calculatePoints(){
   gpaPoints = value*weight;
}
double GPA::getPoints(){return gpaPoints;}
double GPA::getValue(){return value;}
double GPA::getWeight(){return weight;}      
void GPA::setValue(string testLetter){
      if(testLetter == "A"){
         value = 4;;
    } else if(testLetter == "A-"){
         value = 3.7;;
    } else if(testLetter == "B+"){
         value = 3.33;;
    } else if(testLetter == "B"){
         value = 3.0;
    } else if(testLetter == "B-"){
         value = 2.7;
    } else if(testLetter == "C+"){ 
         value = 2.33;
    } else if(testLetter == "C"){
         value = 2.0;
    } else if(testLetter == "C-"){
         value = 1.7;
    } else if(testLetter == "D"){
         value = 1.0;
    } else if(testLetter == "F"){
         value = 0;
    } else{
         value = 0;
         letter = "ERROR";
         cout << "\"" << letter << "\" is not a valid letter score." << endl;
      }
   }

//makes sure the value is in a correct range
double GPA::checkValue(double check){
      if(check >= 4.0){
         value = 4.0;
    } else if(check > 3.7){
         value = 3.7;
    } else if(check > 3.33){
         value = 3.33;
    } else if(check > 3.0){
         value = 3.0;
    } else if(check > 2.7){
         value = 2.7;
    } else if(check > 2.33){
         value = 2.33;
    } else if(check > 2.00){
         value = 2.0;
    } else if(check > 1.7){
         value = 1.7;
    } else if(check > 1.0){
         value = 1.0;
    } else {
         value = 0;
    }
      return value;
   }
         
//REQ: Must first be run through checkValue
void GPA::setLetter(double value){
      if(value == 4.0){
         letter = "A";
    } else if(value == 3.7){
         letter = "A-";
    } else if(value == 3.33){
         letter = "B+";
    } else if(value == 3.0){
         letter = "B";
    } else if(value == 2.7){
         letter = "B-";
    } else if(value == 2.33){
         letter = "C+";
    } else if(value == 2.0){
         letter = "C";
    } else if(value == 1.7){
         letter = "C-";
    } else if(value == 1.0){
         letter = "D";
    } else {
         letter = "F";
      }
   } 





