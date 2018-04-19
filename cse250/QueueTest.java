/** File "QueueTest.java", by KWR for CSE250, Fall 2010.  For 
Assignment 2.  Translate this file into equivalent C++ code.
 */

import java.io.*;

class StringQueue {
   String elements[];
   int frontSpace;
   int rearItem;
   int maxAdds;

   //CLASS INV: frontSpace indicates first empty cell for pushFront
   //           rearItem designates rear item (not space) for popRear---
   //           ---or if there is no such item, rearItem == frontSpace;

   public StringQueue(int maxAdds) {
      elements = new String[maxAdds];
      frontSpace = 0;
      rearItem = 0;
      this.maxAdds = maxAdds;
   }
   public boolean isEmpty() { return frontSpace == rearItem; }
   public boolean isFull() { return frontSpace == maxAdds; }
   public int size() { return frontSpace - rearItem; }
   public void pushFront(String newItem) {
      elements[frontSpace++] = newItem;
   }
   public String popRear() {
      if (isEmpty()) {
         System.err.println("Later we'll define and throw an EmptyQException");
         return "";
      } else {
         return elements[rearItem++];
      }
   }
   public String toString() { 
      String out = "";
      for (int i = rearItem; i < frontSpace; i++) {
         out += elements[i] + " ";
      }
      return out;
   }
}

public class QueueTest { //later we'll write more-interesting test code
   public static void main(String[] args) {
      StringQueue sq = new StringQueue(100);
      sq.pushFront("oh");
      sq.pushFront("say");
      sq.pushFront("can");
      sq.pushFront("you");
      sq.pushFront("see");
      System.out.println(sq.toString());
      String pop2 = sq.popRear() + " " + sq.popRear();
      System.out.println(pop2 + ", did this print in the right order?");
      sq.pushFront("me?");
      System.out.println("Final queue: " + sq.toString());
   }
}
