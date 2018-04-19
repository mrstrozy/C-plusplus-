// File "ListTest.java".  Java translation by KWR of C++ classes written by
// Ravi Sethi.  For CSE250 Spring'00: object is to translate 'em back!
// Few comments in this file, so you can compare syntax with the C++ version.

import java.io.*;

class Foo{
   String fooVal;
   Foo() { fooVal = "Empty"; }
   Foo(String str) { fooVal = str; }
   Foo(int x) { fooVal = "" + x; }
   String getFooVal() { return fooVal; }
   void setFooVal(String newFooVal) { fooVal = newFooVal; }
   public String toString() { return "My fooVal is " + fooVal; }
}

class FooList {   ///of course we will make "general" lists soon...
   class Cell {   ///nested Cell class---can do same way in C++.
      Foo info;   ///you will need a ~Cell() destructor to delete this field.
      Cell next;
      Cell(Foo info) { this.info = info; next = this; }
      Cell(Foo info, Cell n) { this.info = info; next = n; }
   }
   Cell rear;

   ///Note: Java "default" access must == "public" in C++, or use "friend".
   FooList()  { rear = new Cell(new Foo(0)); }
   boolean empty() { return rear == rear.next; }
   void add(Foo i) {
      rear.info = i;
      rear = rear.next = new Cell(new Foo(0), rear.next);
   }
   void push(Foo i) {
      rear.next = new Cell(i, rear.next);
   }
   Foo get() {
      if( empty() ) return new Foo();
      Cell front = rear.next;
      rear.next = front.next;
      return front.info;
   }
}

class Queue extends FooList {
   public Queue() {}
   public Foo get() { return super.get(); }  //See IMPT NOTE below.
   public void put(Foo x) { add(x); }
}

class Stack extends FooList {
   public Stack() {}
   public Foo pop() { return get(); }  
   public void push(Foo x) { super.push(x); }  //See IMPT NOTE below.
}

public class ListTest {     // Just a wrapper for "main", no constructors!
   public static void main(String ignored[]) {
      Stack s = new Stack();
      Queue q = new Queue();
      int n = 9;
      for(int i = 1; i <= n; i++) {
         s.push(new Foo(i)); q.put(new Foo(i));
      }
      PrintStream OUT = new PrintStream(System.out);//don't translate, use cout
      OUT.print("Stack\t\tQueue\n");
      for(int i = 1; i <= n; i++) {
         OUT.print(s.pop()); OUT.print("\t");  //uses automatic toString
         OUT.print(q.get()); OUT.print("\n");  //conversion in class Foo.
      }
   }
}

/* IMPT NOTE: Java forbids using the name of the immediate parent class
to qualify a method invocation.  Instead, use the prefix "super." to
refer to the immediate parent class, as done here.
*/
