/** File "LinkMain.cpp", by KWR for CSE250, Fall 2009.  
    Compile using the makefile "LinkMain.make", via make -f LinkMain.make
    Also try these commands separately, from timberlake's command line:
    g++ -c LinkArg.cpp
    # g++ -c LinkTemplate.cpp  //We will not do---just have LinkTemplate.h
    g++ -c LinkMain.cpp
    g++ LinkArg.o LinkTemplate.o LinkMain.o (or g++ -o LinkMain LinkArg.o etc.)
    Then try to build this mini-project in your IDE at home.
    See if your IDE has an option to "Build" just the individual .cpp files
    first.  Do you get the error before or after linking?  Can you tell?
    Finally, fix the typo "dompare" and check that all is well.
    If you still get errors (especially with templates),  tell us!
 */
#include<iostream>
#include "LinkArg.h"
#include "LinkTemplate.h"  //Foo<T> in notes

using namespace std;

int main(void) {
   LinkArg b1(7);  //called Bar in notes
   LinkArg b2(5);
   //b1 = 2;         //do you want this behavior?  If not, use "explicit"!
   b1 = LinkArg(2);  //value assignment, compare to pointer assgt using "new"
   string s = b1;    //legal because of operator string converter.

   LinkTemplate<LinkArg>* nonce = new LinkTemplate<LinkArg>();
   if (nonce->lessThan(b1,b2)) {
      cout << "The lesser is " << b1.operator string() << endl;
   } else {                   
      cout << "b2 = " << b2 << " is no bigger" << endl;
   }               // ^^^^^ OK via operator<<(ostream&, LinkArg)
   cout << "And the string form of b1 is " << s << endl;
}


