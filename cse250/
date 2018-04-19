/** File "DequeTest.java", by KWR for CSE250, Spring 2013 and 2014.  For 
Assignment 2.  Translate this file into equivalent C++ code.
NOTE: This is different from a similarly-titled assignment in Fall 2010.
 */

import java.io.*;

class StringDeque { //Front of deque is toward 0, but need not be 0.
   String elements[];
   int frontItem;   //CLASS INV: indexes item with least index
   int rearSpace;   //CLASS INV: indexes space after item with greatest index
   int upperBound;  //For array[0..n-1] this is "n" not "n-1".

   //CLASS INV: frontSpace indicates first empty cell for pushFront
   //           rearSpace designates rear item (not space) for popRear---
   //           ---or if there is no such item, rearSpace == frontItem;

   public StringDeque(int guaranteedCapacity) {
      elements = new String[2*guaranteedCapacity];
      frontItem = guaranteedCapacity;
      rearSpace = guaranteedCapacity;
      upperBound = 2*guaranteedCapacity;
   }
   /** C++ lingo: call the first two "empty" and "full".  Remember "const"!
    */
   public boolean isEmpty() { return frontItem == rearSpace; }
   public boolean isFull() { return rearSpace == upperBound || frontItem == 0; }
   public int size() { return rearSpace - frontItem; }
   
   public String popRear() {
      if (isEmpty()) {
         System.err.println("Later we'll define and throw an EmptyQException");
         return "";
      } else {
         return elements[--rearSpace];
      }
   }
   public String popFront() {
      if (isEmpty()) {
         System.err.println("Later we'll define and throw an EmptyQException");
         return "";
      } else {
         return elements[frontItem++];
      }
   }

   /** Directions include similarly testing for "full" in the C++ code.
    */
   public void pushFront(String newItem) {
      elements[--frontItem] = newItem;
   }
   public void pushRear(String newItem) {
      elements[rearSpace++] = newItem;
   }


   public String toString() { 
      String out = "";
      for (int i = frontItem; i < rearSpace; i++) {
         out += elements[i] + " ";
      }
      return out;
   }
}

public class DequeTest { //later we'll write more-interesting test code
   public static void main(String[] args) {
      StringDeque sd = new StringDeque(100);
      sd.pushFront("oh");
      sd.pushFront("say");
      sd.pushFront("can");
      sd.pushFront("you");
      sd.pushFront("see");
      sd.pushRear("any");
      sd.pushRear("bad bugs");
      sd.pushRear("on");
      sd.pushRear("me?");
      System.out.println(sd.toString());
      String pop2 = sd.popRear() + " " + sd.popRear();
      System.out.println(pop2 + ", did this print in the right order?");
      sd.pushFront("I");
      System.out.println("Final deque: " + sd.toString());
   }
}
