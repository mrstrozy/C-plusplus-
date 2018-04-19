/** File "StackTest.java", by KWR for CSE250, Fall 2011.  Practice example
for Assignment 2.  Translate this file into equivalent C++ code.
Used in Week 3 recitations.
 */

import java.io.*;

class StringStack {
   String elements[];
   int frontSpace;  //first free cell, after top-of-stack
   int maxAdds;

   //CLASS INV: top indicates first empty cell for pushFront

   public StringStack(int maxAdds) {
      elements = new String[maxAdds];
      frontSpace = 0;
      this.maxAdds = maxAdds;
   }
   public boolean isEmpty() { return frontSpace == 0; }
   public boolean isFull() { return frontSpace == maxAdds; }
   public int size() { return frontSpace; }
   public void pushFront(String newItem) {
      elements[frontSpace++] = newItem;
   }
   public String popFront() {
      if (isEmpty()) {
         System.err.println("We *could* define and throw an EmptyStackException");
         return "";
      } else {
         return elements[--frontSpace];
      }
   }
   public String toString() { 
      String out = "";
      for (int i = 0; i < frontSpace; i++) {
         out += elements[i] + " ";
      }
      return out;
   }
}

public class StackTest { //later we'll write more-interesting test code
   public static void main(String[] args) {
      StringStack sq = new StringStack(100);
      sq.pushFront("oh");
      sq.pushFront("say");
      sq.pushFront("can");
      sq.pushFront("you");
      sq.pushFront("see");
      System.out.println(sq.toString());
      String pop2 = sq.popFront() + " " + sq.popFront();
      System.out.println(pop2 + ", did this print in the right order?");
      sq.pushFront("me?");
      System.out.println("Final stack: " + sq.toString());
   }
}
