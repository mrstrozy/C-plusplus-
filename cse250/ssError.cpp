/** File "stringsorts.cpp", by KWR for CSE250, Fall 2009.  Still "mutable"...
    Compares real-CPU running times for two user-defined (non-templated)
    sorting algorithms.  Main purpose is to give an example from
    actual code of the "tradeoff" or "crossover" point between a
    quadratic-time algorithm with small leading constant and a log-linear one
    that has a bigger leading constant (for recursion, copying, etc.).
    
    Compile:
            g++ -O5 -o stringsorts stringsorts.cpp -lrt
    Usage:
            stringsorts foo n     ---where foo is a file
    Output:
            - Creates foo.out with the first n strings in foo alpha-sorted
            - Outputs timing data to std::cout
   
    Note the "-O5" (capital-Oh) flag, which gives high(est) optimization
    on g++.  On my home Macintosh, the flag is "g++ -fast".  The trailing
    -lrt tells the linker to find an applicable RealTime library; on
    timberlake the actual name of the library is "librt.a".  
    (Hester Prynne: "Give me librt or give me A.")  
    This is a necessity of the microsecond timer which I'd like to avoid...

    Note that all whitespace-separated strings are picked up from file foo; 
    --no effort is made to limit e.g. to alphanumeric strings only.
    The built-in operator< on the C++ STL string type is used to compare them.

    Illustrates ** call-by-reference ** in the sorting algorithms,
    which not only avoids copying the passed-in vector, but is necessary
    to get it sorted at all!  (The trickiness of this is one reason why
    Java followed raw C/C++ arrays in passing them as pointers only.)

    Also illustrates file I/O, use of "CPUTimer.h", stream manipulators
    (from the <iomanip> system header), and REQ/ENS/INV comments.

    Final version will differ only in having the sorts in separate file(s)
    and using a Makefile to supply all the needed flags...
 */

#include <iostream>
#include <iomanip>        //for setprecision(n)
#include <fstream>        //for streaming file I/O
#include <sstream>        //for string streams
#include <algorithm>      //for std::sort
#include "CPUTimer.h"     //see note in that class about self-study revision
#include <vector>

//using namespace std;    //frowned upon in large projects
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::istream;
using std::ifstream;
using std::setprecision;
using std::fixed;
using std::ios_base;
using std::istringstream;
using std::ofstream;
using std::endl;
using std::cerr;

//Because such "using" lists get long, the ultimate habit is to use
//the "std::" and other prefixes at each point of use...

inline void simpleInsertionSort(vector<string>& vec) {
   const int n = vec.size();
   if (n == 0) return;  //else
   string temp;         //for swapping
   for (int nextPos = 1; nextPos < n; nextPos++) {
      // LOOP INV 1: Elements [first..nextPos-1] are sorted.
      // True at start since [first] is sorted
      // Truth at end says [first...last-1] is sorted, which is the goal.

      int nextTarget = nextPos - 1;

         // LOOP INV 2: the element we're trying to place is at nextTarget + 1.
         // If the target is greater, then we have to swap them.  If not, stop.
         // Swapping puts the element we're trying to place at nextTarget,
         // so we have to do nextTarget-- in order to try the next element and
         // restore LOOP INV for the next iteration of the inner loop.

         // BOUNDARY: cannot allow nextTarget < first---if this happens,
         // it means the element we're trying to place was < all others so far,
         // and since it has already been swapped into the first cell, we
         // simply stop.  Thus the loop condition also needs to test
         // nextTarget >= first.  Difference from text p584 is that
         // nextTarget is the index 1 less than "next_pos" in text's "insert".

      while (nextTarget >= 0 && vec[nextTarget+1] < vec[nextTarget]) {
         temp = vec[nextTarget];
         vec[nextTarget] = vec[nextTarget+1];
         vec[nextTarget+1] = temp;
         nextTarget--;
      }
      // LOOP INV 1 holds for the start of the next outer-loop iteration,
      // so this inner-loop iteration has no more to do
   }
}

/** REQ: "out" has (at least) as many places as the input vectors!
 */
inline void simpleMerge(vector<string>& lhs, vector<string>& rhs, 
                        vector<string>& target) {
   int left = 0;
   const int endLeft = lhs.size();
   int right = 0;
   const int endRight = rhs.size();
   int out = 0;
   while (left != endLeft && right != endRight) {
      if (lhs[left] < rhs[right]) {
         target[out++] = lhs[left++];  //the ++ side-effects are traditional..
      } else {                         //..though technically bad style since
         target[out++] = rhs[right++]; //they do two things at once.
      }
   }

   // NB: Exactly one sequence will have items left over.  We don't care which
   // By INV, those elements are >= those written so far, so just append them

   while (left != endLeft) {
      target[out++] = lhs[left++];
   }
   while (right != endRight) {
      target[out++] = rhs[right++];
   }
}


/** Mergesort sorts slice from [first..last) IN-PLACE, destructively!
    Makes separate copies of "left table" and "right table" to sort
    recursively and finally feed to "merge".
    REQ: standard conventions on "first" and "last"/"end()".
 */
inline void simpleMergeSort(vector<string>& items) {

   const int size = items.size();
   if (size <= 1) { return; }   //nothing to do
      //else
   int middle = items.size() / 2;   //rounding down doesn't matter

   // Now, we need fresh copies of the two halves.

   vector<string> leftTable(middle);      
   vector<string> rightTable(size - middle);  
   for (int i = 0; i < middle; i++) {
      leftTable[i] = items[i];
   }
   for (int i = middle; i < size; i++) {
      rightTable[i-middle] = items[i];
   }

   simpleMergeSort(leftTable);
   simpleMergeSort(rightTable);

   // REC INV: leftTable and rightTable are now sorted.
   // Now leftTable and rightTable have always been separate copies from
   // our original array, so no problem zapping our original by
   // passing "first" as the parameter "out" in the merge function.

   simpleMerge(leftTable, rightTable, items);
}

   

   
int main(int argc, char** argv) {
   // transfer command-line arguments to string array
   // remember unlike Java the executable name is the first argument
   vector<string>* args = new vector<string>(argc);
   for (int i = 0; i < argc; i++) {
      args->at(i) = *(argv + i);         //equivalent to argv[i]
   }

   istringstream INS; //string stream used just for string-to-int conversion
   int n = 10000;			//arbitrary default value
   string infileName;   //we will not use a default for the file name.
   istream infilep;

   if (argc >= 3) {   //a numerical argument "n" is provided
      INS.str(args->at(2));             //safe since argc >= 3
      if (INS >> n) {
         //OK
      } else {
         cerr << "Second argument given but not a valid integer" << endl;
         return(1);
      }
   }


   if (argc >= 2) {   //note that this is *not* an "else" of the first "if"
      infileName = args->at(1);
      infilep = ifstream(infileName.c_str(), ios_base::in);
      if (! infilep.is_open()) {
         cerr << "Unable to open file: " << infileName << endl;
         return(1);
      }
   } else {    //argc == 1, i.e. no arguments given
      cerr << "Usage: stringsorts file n    with n >= 0" << endl;
      return(1);
   }


   const string outinfileName = infileName + ".out";
   //Create output file in "out" mode, which zaps previous contents
   //To preserve and append after previous contents, use ios_base:app


   ofstream* outfilep = new ofstream(outinfileName.c_str(), ios_base::out);
   if (! outfilep->is_open()) {
      cerr << "Unable to create and stat output file " << outinfileName
           << endl;
      return(1);
   }


   //Control here means input & output file streams are OK.
   //Now we create the arrays of (up to) n strings.
   //BECAUSE we want five separate copies, we use C++ VALUES, not pointers!

   vector<string> itemsCopy1(n);
   
   //Now n might be bigger than the number of strings in the file, so
   //we also need to test the input stream for end-of-file etc.

   int numItems = 0; //means # of strings stored thus far AND next free index
   string temp;
   while (numItems < n && infilep >> temp) {           //see "Fubar?" note
   //while(infilep >> temp && numItems < n) {
      // control here means read was good, so store item
      itemsCopy1[numItems++] = temp;
   }
   //now test state of stream upon termination

   if (infilep.eof()) {
      cout << "Read all " << numItems << " whitespace-separated items"
           << " in file " << infileName << endl;
   } else if (infilep.bad()) {
      cerr << "Unrecoverable i/o error, sorry, after " << numItems 
           << " items." << endl;
   } else {
      // stream is still good, so we must have hit n items
      cout << "Read " << numItems << " whitespace-separated items from file "
           << infileName << endl;
   }

   //"Fubar"?  The <iostream> library has been criticized for its feature
   //that the eof flag is not set after reading the last item in a file,
   //even when there is no (other) whitespace between it and EOF.
   //The flag is set only after the next attempted read.  Thus in case 
   //n is exactly the # of items in the file, the stream will exit with
   //eof() *false*, here causing the message *without* "all" to be displayed.
   //This can be fixed (if you think it needed) by switching the conditions:
   // while(*infile >> temp && numItems < n) { ... }
   //Half the people think this difference in behavior is OK, half don't.
   //Factor in 9-or-so independent similar controversies, and you get
   //that only 1/1024 of the people---less than 0.1%---think the library
   //isn't fubar ;->.
   //[The main objection actually is the "Pitfall" with "getline" described on
   //p47 of the K-W text.  The second is the presence of a function "good()"
   //which is not the negation of "bad()", nor of "fail()", nor of eof(),
   //but rather == !bad() && !fail() && !eof().  Whereas the stream's <<
   //operator itself returns a reference that == !fail() as a Boolean.
   //It turns out that !fail is the best while-loop condition, so
   //people avoid "good()"---our text doesn't even mention it!]

   //In case numItems is (much) less than n, we resize the vector.
   //(An alternative would have been to create an empty vector and use
   //itemsCopy1.push_back(item) to store items read by (infilep) >> item.)

   if (numItems < n) {
      itemsCopy1.resize(numItems);
   }
   vector<string> itemsCopy2 = itemsCopy1;   //see vector-value note at end

   // ENS: itemsCopy1 and itemsCopy2 etc. hold just the actually-read items.
   // Hence itemsCopy1.end() etc. will delimit those items correctly.

   CPUTimer* timer = new CPUTimer();

   cout << "Doing non-templated insertion sort..." << endl;

   timer->reset();
   simpleInsertionSort(itemsCopy1);
   double timeForSimpleInsertionSort = timer->elapsedTime();

   cout << "Doing non-templated user MergeSort..." << endl;

   timer->reset();
   simpleMergeSort(itemsCopy2);
   double timeForSimpleMergeSort = timer->elapsedTime();


   cout << fixed << setprecision(3);
   cout << "Time for non-templated insertion sort, in " << timer->getUnits()
        << ": " << timeForSimpleInsertionSort << endl;
   cout << "Time for non-templated user mergesort, in " << timer->getUnits()
        << ": " << timeForSimpleMergeSort << endl;

   for (int i = 0; i < numItems; i++) {
      (*outfilep) << itemsCopy1[i] << endl;
   }
   infilep.close();   //could also do delete(infilep) and delete(outfilep),
   outfilep->close();  //which (should!) call close on the files.
   delete(timer);
      //the vectors automatically get destructed since they are by-value
   return(0);
}

/** Vector-Value Note: Treating vectors by-value, rather than by-pointer
    as in Java (and frankly as in raw C/C++ arrays) is a big step.
    Even a "small" text file like Hamlet.txt gives over 30,000 entries,
    for big-enough vectors that indiscriminately copying them comes with
    a real cost.  Here we needed separate copies to run the 2 sorting
    algorithms on, and we also needed to copy during mergeSort.  As Wikipedia
    http://en.wikipedia.org/wiki/Merge_sort (scroll to "Analysis") says:

      ...Merge sort's most common implementation [== the above in this
      code file] does not sort in place; therefore, the memory size of
      the input must be allocated for the sorted output to be stored in...

    This ultimately means copying from input to output, and you can see
    this communicated by my "/**" comments above.
        What you should reflect on is that the designers of Java
    deliberately aimed to make copying hard to do (needing to override
    a "clone()" method) and non-default behavior---especially for arrays.
    But the art of C++ is using "value types" (and sometimes non-"virtual"
    method behavior) wisely.  See, for instance, how eliminating one
    heap-object pointer can make the whole "CPUTimer" class simpler...if
    not more efficient.  The new language "C#" tries to do this by making
    value-types a whole different class category, recycling the keyword
    "struct" for them.  I'm not saying to dump C++ for C#, but rather to
    reflect on that the designers of C# deliberately aimed to make copying
    easy to do, especially (not!!) for arrays.  In C++ you can have both...
 */
