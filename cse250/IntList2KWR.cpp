/** File "IntList2.cpp", by KWR for CSE250, Fall 2009
    C++ translation of "IntList2.java", + across several files, with Makefile
    Few comments in the files, so you can just compare the syntax.
 */

#include<iostream>
using namespace std;

class Cell {
   int info;
   Cell* next;
   friend class List;
 public:
   Cell(int i) :
      info(i),
      next(this)
   { }
   Cell(int i, Cell* n) :
      info(i), 
      next(n)
   { }
}; 

class List {
 protected:    //C++ does not have Java package scope, so do this or "friend"
   Cell* rear;
 public:
   List() :
      rear(new Cell(0))
   { }
 protected:           
   bool empty() const {
      return rear == rear->next;
   }
   void add(int x) {   //not const!---it changes the "rear" field
      rear->info = x;
      rear = rear->next = new Cell(0, rear->next);
   }
   void push(int x) {
      rear->next = new Cell(x, rear->next);
   }
   int get() {         //!! Side-Effect !!---orphans first cell, eek!
      if( empty() ) return 0;
      Cell* front = rear->next;
      rear->next = front->next;
      return front->info;   //OK in Java, but memory leak in C++
      //int x = front->info;    //still following Ravi Sethi here
      //delete(front);
      //return x;
   }
};

class Queue : public List {
 public:
   Queue() :
      List()   //base-class constructor call should be explicit in C++
   { }         //though your compiler may allow omitting
   int get() {
      return List::get();  //Can't do "super" in C++, say List::get() here
   }                       //and in main, syntax like myQueue.List::get()  
   void put(int x) {
      add(x);              //since we renamed the method, not shadowed
   }
};

class Stack : public List {
 public:
   Stack() :
      List()
   { }
   int pop() {
      return get();
   }  
   void push(int x) {
      List::push(x);
   }
};

int main(void) {
   Stack* s = new Stack();
   Queue* q = new Queue();
   int n = 9;
   for(int i = 1; i <= n; i++) {
      s->push(i);
      q->put(i);
   }
   cout << "stack\tqueue\n";
   for(int i = 1; i <= n; i++) {
      cout << (s->pop()) << "\t";
      cout << (q->get()) << "\n";  
   }
   return(0);
}

/* IMPT NOTE: Java forbids using the name of the immediate parent class
to qualify a method invocation.  Instead, use the prefix "super." to
refer to the immediate parent class, as done here.  Correspondingly, in
C++ one must insert the name of the desired parent class, followed by ::,
where Java uses "super" followed by .!
*/

