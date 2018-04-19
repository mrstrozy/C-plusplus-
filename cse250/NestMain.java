// File "NestMain.java, by KWR for CSE250, Spr'00.  Goes with NestPack/
// Illustrates nested interfaces in Java.  And also ugly "promotion casts"!
// Compiler odditity: gives error on first pass, *fine* on second pass!

import NestPack.BST;
//import NestPack.BST.Sortable;
//import NestPack.*;

class MySortableItem implements BST.Sortable {
   String key;
   public boolean lessThan(BST.Sortable rhs) {
      return key.compareTo(((MySortableItem)rhs).key) < 0;
   }  //need promotion cast ^^^^^^^^^^^^^^^^^^^ to see "key" field.
   public boolean lteq(BST.Sortable rhs) {
      return key.compareTo(((MySortableItem)rhs).key) <= 0;
   }
   public int compareTo(BST.Sortable rhs) {
      return key.compareTo(((MySortableItem)rhs).key);
   }
   public MySortableItem() {}
}

public class NestMain {
   public static void main(String[] args) {
      //NestTest neededToCompile = new NestTest();
      MySortableItem ii = new MySortableItem();
      if (ii.compareTo(ii) != 0) {
         System.out.println("Something is weird!");
      } else {
         System.out.println("Compiles and runs OK.");
      }
   }
}
