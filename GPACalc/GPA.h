#ifndef GPA_H_
#define GPA_H_

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class GPA{
   friend ostream& operator<< (ostream&,const GPA);
   double value,weight,gpaPoints;
   string letter;
  public:
   GPA(string,double);
   GPA(double,double);
   double getPoints();
   double getValue();
   double getWeight();
   void calculatePoints();
   void setValue(string);
   double checkValue(double);
   void setLetter(double);
};

ostream& operator<< (ostream& out, const GPA gpa){
   out << "Letter: " << gpa.letter << " || Value: " 
       << setprecision(2) << fixed <<  gpa.value;
   return out;
}
#endif
