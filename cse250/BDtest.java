// File "BDtest.java".  By KWR.  Illustrates pointer semantics, inheritance,
// and dynamic dispatch ("virtual functions" in C++ lingo).  For CSE250 S'00.
// In conjunction with "bdtest.cc", shows many Java-to-C++ translation points.

import java.io.*;   // for PrintStream class.

class Base {
   int value = 0;              ///can do this in Java but NOT? in C++
   Base() {}                   ///yes, constructors can have empty code! 
   Base(int v) { value = v; }  ///C++ initializer syntax not legal in Java.
   public int getValue() { return value; }
   public void setValue(int v) { value = v; }
   /** toString() overrides "public String toString()" in class Object. */
   public String toString() { return "I'm from Base Class! "; }
   public static String greeting() { return "Hello from Base"; }
}  //^^^^ try compiling with "public" deleted.

class Derived extends Base {
   Derived() {super();}        ///can omit "super();"---happens by default.
   Derived(int v) {super(v);}  ///But here call to superclass constructor is
      ///only way to init private "value" field.  C++ /names/ the superclass.
   /** This toString() overrides the one in Base. */
   public String toString() {return "I'm from Derived Class! ";}
   public String derivedOnly() {
      return "Method \"derivedOnly\" is not defined in the base class."; 
   }
   public static String greeting() {return "Hello from Derived"; }
}

public class BDtest{
   public static void main(String args[]) { ///"String[] args" needed in Java
      stringTest(); System.out.println("");
      Base base1,base2;   ///can declare class objects without initializing
      base1 = new Base(); ///in C++ one can do this only with pointers, hmm...
      Derived derived = new Derived();  ///Can declare and init in both J&C++
      base2 = derived;
      System.out.println("base1 says: " + base1); ///base1.toString() called.
      System.out.println("base2 says: " + base2); ///base2.toString() called--
      ///since base2 holds a Derived instance, the Derived version is /run/.

      System.out.println("Note-(Derived)base2 prints: " + (Derived)base2);
      System.out.println("but (derived)+base2 prints: " + (derived)+base2);
      System.out.println("and (derived)+base1 prints: " + (derived)+base1);
      
      System.out.println("Now, \"base2 = derived\" uses pointer semantics:");
      System.out.println("Value of \"derived\" now: " + derived.getValue());
      System.out.println("Executing derived.setValue(1); ");
      derived.setValue(1);
      System.out.println("Now base2.getValue() = " + base2.getValue());

      System.out.print("base2 whispers: ");
      castCheck(base2);
      System.out.print("base1 screams:  ");
      castCheck(base1);

      System.out.println("Can we make a derived class object say \"base\"?");
      System.out.println(Base.greeting());
      
   }  //end of main

   public static void castCheck(Base base){//must be "static" for main to call
      if (base instanceof Derived) {
         //System.out.println(base.derivedOnly()); //try commenting this in...
            ///..."promotion cast" to Derived needed to call derivedOnly().
         System.out.println(((Derived)base).derivedOnly());
      } else {
         System.out.println("Duck! A run-time \"bad cast\" error is coming!");
         for (int i = 0; i <= 49994999; i++) {}    //just for visual delay
         System.out.println(((Derived)base).derivedOnly());
      }
      System.out.println("Call to castCheck has terminated OK.");
   }

   public static void stringTest() {  ///Shows impt String operations
      String str1 = "New "; String str2 = new String("James"); ///equivalent
      String str3 = " Bond: ";
      PrintStream OUT = System.out;   ///just to save some letters...
      OUT.println(str1 + str2 + str3 + 200 + 7); /// no quotes needed in Java!
      OUT.println(200 + 7 + str2 + str3); /// + cascades left-to-right
      OUT.println(02000 + 007 + str2 + str3); /// is output what you expect?
      //str1.append(str2) ///Legal only for String*Buffer* strings in Java!
      str1 = str1 + str2; ///but this is fine.
      OUT.println("With Java's substring indexing convention you get in a \""
         + str1.substring(4,7) + "\"");
      ///substring(i,j) means positions i through j-1, i.e. not including j!
      if (str1 == "New James") {
         OUT.println(str1 + "== \"New James\" as expected of objects.");
      } else {
         OUT.println(str1 + "!= \"New James\" because both are pointers!");
      }
      if (str3.compareTo(str2) < 0) {  ///"lessThan" and "<" are NOT available.
         OUT.println("Compare " + str3 + str2 + "= " + str3.compareTo(str2));
      }
      OUT.println("\"" + str3 + "\" gets a trim: \"" + str3.trim() + "\"");
      OUT.println( (str3.startsWith("Bond") ? "Java strings are mutable"
                                            : "Java strings are immutable")
         + ", and the length of " + str3 + " is still " + str3.length()   );
         ///Note: "___?___:___" binds least tight, so the () are needed.
   }
   public static void vectorTest() {  //Shows impt Vector operations
   }
      
}  // end of class BDtest.  
