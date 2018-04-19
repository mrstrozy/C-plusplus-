#include <iostream>
#include <string>
using namespace std;




class Computer{
   

   protected: int size;

public:
   Computer(int x):size(x){} 
   virtual int getSize(){return size;}
};

class Lap_Top : Computer{

   double weight;
public:
   Lap_Top(int z, double w) : Computer(z), weight(w){}
   
   double getWeight(){return weight;}
   int getSize() {return size;}
};

int main(){

   Computer cp(5);
   Lap_Top ltp(10,43.5);
   //cp = new Computer(5);
   //ltp = new Lap_Top(10,43.5);

   cout << "The size of the computer is: " << cp.getSize() << endl;
   cout << "The size of the Lap Top is: " << ltp.getSize() << endl;
   cout << "The weight of the Lap top is: " << ltp.getWeight() << endl;

}
