// File "IntList2.java".  Java translation of Sethi's "IntList2.cc".  By KWR
// Few comments in this file, so you can compare syntax with the C++ version.

import java.io.*;

class Cell {
   int info;
   Cell next;
   public Cell(int i) {
      info = i;
      next = this;
   }
   public Cell(int i, Cell n) {
      info = i;
      next = n;
   }
} 

class List {
   Cell rear;
   public List()  {
      rear = new Cell(0);
   }
   protected boolean empty() {
      return rear == rear.next;
   }
   protected void add(int x) {
      rear.info = x;
      rear = rear.next = new Cell(0, rear.next);
   }
   protected void push(int x) {
      rear.next = new Cell(x, rear.next);
   }
   protected int get() {
      if( empty() ) return 0;
      Cell front = rear.next;
      rear.next = front.next;
      return front.info;
   }
}

class Queue extends List {
   public Queue() {}
   public int get() {
      return super.get();  //Can't do "super" in C++, say List::get() here
   }                       //and in main, syntax like myQueue.List::get()  
   public void put(int x) {
      add(x);
   }
}

class Stack extends List {
// "default" inheritance in Java mediates between "public" and "private"
// inheritance as described in the text, pp282--284.  So same as for Queue.
   public         Stack() {}
   public int     pop() { return get(); }  
   public void    push(int x) { super.push(x); }  //See IMPT NOTE below.
   // List.empty() is "public" here, but automatically accessible
   // only within this package anyway.
}

public class IntList2 {        // Just a wrapper for "main", no constructors!
   public static void main(String ignored[]) {
      Stack s = new Stack();
      Queue q = new Queue();
      int n = 9;
      for(int i = 1; i <= n; i++) {
         s.push(i);
         q.put(i);
      }
      PrintStream OUT = new PrintStream(System.out);
      OUT.print("stack\tqueue\n");
      for(int i = 1; i <= n; i++) {
         OUT.print(s.pop()); OUT.print("\t");
         OUT.print(q.get()); OUT.print("\n");  
      }
   }
}

/* IMPT NOTE: Java forbids using the name of the immediate parent class
to qualify a method invocation.  Instead, use the prefix "super." to
refer to the immediate parent class, as done here.  Correspondingly, in
C++ one must insert the name of the desired parent class, followed by ::,
where Java uses "super" followed by .!
*/

