/** File "StringClient.java".  Java version of the "Stack<T>" class in a
    textbook by Ravi Sethi, but with the argument type T fixed as String.
    By KWR for CSE250, Fall 2009, to translate into C++ as-is (Assignment 1)
    CSE250 Fall 2010-->this became a recitation exercise.
    Later we will turn it into a C++ template class Stack<T>.
 */


import java.io.*;   // C++: use #include <iostream>
                    // Also #include <vector> and #include <string>

class StringStack {
   int top; 
   final int maxSize = 101;                 //C++: must init by constructor?
   String elements[] = new String[maxSize]; //C++: use vector<string>*
                                            //Nerdy: vector<const string*>* !
   //C++: ^^^^must initialize in constructor!: new vector<string>(maxSize)


   //CLASS INV: top is the /first free cell/, empty stack is top == 0;


   /** Create empty stack
    */
   public StringStack() {top = 0;}          

   public void push(String c) {
      elements[top++] = c;        //C++: elements->at(top++) = c;  is OK
   }
   public String pop() {
      if (top == 0) {
         System.err.println("Attempt to pop from empty stack."); 
         return "";               //System.err.print ~= cerr << in C++
      } else {
         return elements[--top];  //Is [--top] bad style per text, page 22?
      }                           //Well, as we'll see , it *is* STL-style!
   }                              //But you need the CLASS INV to be sure...
   public int size() { return top; }
}

public class StringClient {               //use just "int main()" in C++
   /** Test-driving code for StringStacks
    */
   public static void main(String args[]) {
      StringStack testStack = new StringStack();
      System.out.print("Pushing \"AAA\" ... ");     //use cout << ... 
      testStack.push("AAA"); 
      System.out.println("Pushing \"BBB\" ... ");   //this tacks on ...<< endl;
      testStack.push("BBB"); 
      System.out.println("Size is now " + testStack.size());
      testStack.pop();               // ^ chain with "<<" instead in C++
      System.out.println("Pop---size is now " + testStack.size());
      String c = testStack.pop();
      System.out.print("I popped the string \"");
      System.out.println(c + "\", size now " + testStack.size());
      System.out.println("Can I pop again?");
      String d = testStack.pop();
      System.out.println("Oops!  I got: \"" + d + "\"");
   }
}
