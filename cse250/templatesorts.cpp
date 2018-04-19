/** File "templatesorts.cpp", by KWR for CSE250, Fall 2009.  May change...
    Includes slightly-modified versions of K-W text code from Chapter 10.
    Illustrates and times calls to various sorting functions, including
    the STL's "sort" function---the one that assumes operator< is already
    defined for the client type.  Main purpose is to give an example from
    actual code of the "tradeoff" or "crossover" point between a
    quadratic-time algorithm with small leading constant and a log-linear one
    that has a bigger leading constant (for recursion, copying, etc.).
    A second theme is that "templated" code really can be fast.
    Compile:
            g++ -O5 -o templatesorts templatesorts.cpp -lrt
    Usage:
            templatesorts foo n     ---where foo is a file
    Output:
            - Creates foo.out with the first n strings in foo alpha-sorted
            - Outputs timing data to std::cout
   
    Note that all whitespace-separated strings are picked up from file foo; 
    --no effort is made to limit e.g. to alphanumeric strings only.
    The built-in operator< on the C++ STL string type is used to compare them.

    Also note that the use of iterators in the templated code removes the
    possibility of forgetting to use call-by-reference in the "simple" sorts.

    Also illustrates file I/O, use of "HiResTimer.h", stream manipulators
    (from the <iomanip> system header), and REQ/ENS/INV comments.

    Final version will differ only in having the sorts in separate file(s)
    and using a Makefile to supply all the needed flags...
 */

#include <iostream>
#include <iomanip>        //for setprecision(n)
#include <fstream>        //for streaming file I/O
#include <sstream>        //for string streams
#include <algorithm>      //for std::sort
#include "HiResTimer.h"     //see note in that class about self-study revision
#include <vector>
#include <string>

//using namespace std;    //frowned upon in large projects
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::ifstream;
using std::setprecision;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::ios_base;
using std::istringstream;
using std::ofstream;
using std::endl;
using std::cerr;

//Because such "using" lists get long, the ultimate habit is to use
//the "std::" and other prefixes at each point of use...


//---------------------STL-Style Template Versions----------------------------

/** Sort the elements [first..last), !!not including last!!, in nondescending
    order according to bool operator< (const Bar&, const Bar&), where Bar
    is the type the iterators first and last are pointing at.  
    Code based on text, p583, but not making "insert" a separate function,
    calling the template RAI not RI for RandomAccessIterator, and avoiding
    the text's multiple use of "nextPos".  Instead, we use a separate
    named index variable "nextTarget" initialized to nextPos - 1.
    [Note that the dependences on operator< and on RAI meeting the 
    requirements of a true "RAI" are implicit, not explicit as in Java.]

    STL CONVENTION: "end()" and "last" always mean one-place PAST the
    final element, like "n" in a loop for(int i = 0; i < n; i++) {...}
 */
template<typename RAI>
inline void insertionSort(RAI first, RAI last) {
   for (RAI nextPos = first + 1; nextPos != last; nextPos++) {
      // LOOP INV 1: Elements [first..nextPos-1] are sorted.
      // True at start since [first] is sorted
      // Truth at end says [first...last-1] is sorted, which is the goal.

      RAI nextTarget = nextPos - 1;  

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

      while (nextTarget >= first && operator<(*(nextTarget+1), *nextTarget)) {
         std::iter_swap(nextTarget,nextTarget+1);
         nextTarget--;
      }
      // LOOP INV 1 holds for the start of the next outer-loop iteration, 
      // so this inner-loop iteration has no more to do
   }
}

/** Merge and Mergesort, based on text, section 10.7
    COPIES the m first inputs and n second inputs OVER the target.
    REQ: target has m+n free spaces from param out onward.
    REQ: [left...endLeft) and [right...endRight) are already nondecr. sorted.
    INV: Elements not-yet-read are >= all elements written so far.
    ENS: The m+n cells starting from out hold exactly the m+n elements
         marked off by the input iterators, in nondecreasing sorted order.
 */
template<typename RAI>
inline void merge(RAI left, RAI endLeft, RAI right, RAI endRight,
                  RAI out) {
   while (left != endLeft && right != endRight) {
      if (*left < *right) {
         *out++ = *left++;    //the "++" side-effects are traditional...
      } else {                //...though technically bad style since they
         *out++ = *right++;   //do two things at once.  
      }
      //*out++ = (*left < *right ? *left++ : *right++);  //truly bad style...
   }

   // NB: Exactly one sequence will have items left over.  We don't care which
   // By INV, those elements are >= those written so far, so just append them
   while (left != endLeft) {
      *out++ = *left++;
   }
   while (right != endRight) {
      *out++ = *right++;
   }
}

/** Mergesort sorts slice from [first..last) IN-PLACE, destructively!
    Makes separate copies of "left table" and "right table" to sort
    recursively and finally feed to "merge".
    REQ: standard conventions on "first" and "last"/"end()".
 */
template<typename RAI>
inline void mergeSort(RAI first, RAI last) {

   typedef typename std::iterator_traits<RAI>::value_type ValueType;

   // ^^^ allows us to deduce the vector client type from the RAI type;
   //this is easier and safer than examining an element's type via RTTI
   //See http://www.boost.org/community/generic_programming.html
   //below "Anatomy of a Concept" for how "traits" work.

   if (last - first > 1) {
      RAI middle = first + (last - first) / 2;    //integer-div 2 is AOK.
      vector<ValueType> leftTable(first, middle); //COPIES elements!
      vector<ValueType> rightTable(middle, last); 

      mergeSort(leftTable.begin(), leftTable.end()); 
      mergeSort(rightTable.begin(), rightTable.end());

      // REC INV: leftTable and rightTable are now sorted.
      // Now leftTable and rightTable have always been separate copies from
      // our original array, so no problem zapping our original by
      // passing "first" as the parameter "out" in the merge function.

      merge(leftTable.begin(), leftTable.end(),
            rightTable.begin(), rightTable.end(),
            first);
   }
}


//---------------------Raw-Array Pointer Versions----------------------------

/** Sorts raw array from item first up to, not including, last.
 */
inline void pointerInsertionSort(string* first, string* last) {
   for (string* nextPos = first + 1; nextPos != last; nextPos++) {
      // LOOP INV 1: Elements [first..nextPos-1] are sorted.
      // True at start since [first] is sorted
      // Truth at end says [first...last-1] is sorted, which is the goal.

      string* nextTarget = nextPos - 1;

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

      while (nextTarget >= first && operator<(*(nextTarget+1), *nextTarget)) {
         string temp = *nextTarget;
         *nextTarget = *(nextTarget+1);
         *(nextTarget+1) = temp;
         nextTarget--;
      }
      // LOOP INV 1 holds for the start of the next outer-loop iteration, 
      // so this inner-loop iteration has no more to do
   }
}


/** Merge and MergeSort with raw-array pointers.  All I did was change
    the template parameter "RAI" to "string*" everywhere!
    This is what is meant by saying that templates can be treated as macros...
 */
inline void pointerMerge(string* left, string* endLeft,
                         string* right, string* endRight,
                         string* out) {
   while (left != endLeft && right != endRight) {
      if (*left < *right) {
         *out++ = *left++;    //the "++" side-effects are traditional...
      } else {                //...though technically bad style since they
         *out++ = *right++;   //do two things at once.  
      }
      //*out++ = (*left < *right ? *left++ : *right++);  //truly bad style...
   }
   
   // NB: Exactly one sequence will have items left over.  We don't care which
   // By INV, those elements are >= those written so far, so just append them
   while (left != endLeft) {
      *out++ = *left++;
   }
   while (right != endRight) {
      *out++ = *right++;
   }
}  

/** Mergesort sorts slice from [first..last) IN-PLACE, destructively!
    Makes separate copies of "left table" and "right table" to sort
    recursively and finally feed to "merge".
    REQ: standard conventions on "first" and "last"/"end()".
 */
inline void pointerMergeSort(string* first, string* last) {

   // ^^^ allows us to deduce the vector client type from the string* type;
   //this is easier and safer than examining an element's type via RTTI
   //See http://www.boost.org/community/generic_programming.html
   //below "Anatomy of a Concept" for how "traits" work.
   
   if (last - first > 1) {
      string* middle = first + (last - first) / 2;    //integer-div 2 is AOK.
      string leftTable[middle - first];
      string rightTable[last - middle];   //need to COPY elements b4 merging

      string* source;
      string* target;
      
      for (source = first, target = leftTable; source != middle;
           source++, target++) {
         *target = *source;
      }
      for (source = middle, target = rightTable; source != last;
           source++, target++) {
         *target = *source;
      }

      string* leftTableEnd = leftTable + (middle - first);
      string* rightTableEnd = rightTable + (last - middle);

      pointerMergeSort(leftTable, leftTableEnd);
      pointerMergeSort(rightTable, rightTableEnd);

      // REC INV: leftTable and rightTable are now sorted.
      // Now leftTable and rightTable have always been separate copies from
      // our original array, so no problem zapping our original by
      // passing "first" as the parameter "out" in the merge function.

      pointerMerge(leftTable, leftTableEnd,
                   rightTable, rightTableEnd,
                   first);
   }
}

//---------------------Raw-Array Indexing Versions-------------------------

/** REQ: n is the true size of the array vec
 */
inline void rawInsertionSort(string vec[], const int n) {
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

/** REQ: At least lhsSize + rhsSize cells have been set aside for target.
 */
inline void rawMerge(string lhs[], const int endLeft,
                     string rhs[], const int endRight,
                     string target[]) {
   int left = 0;
   int right = 0;
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
inline void rawMergeSort(string items[], const int size) {

   if (size <= 1) { return; }   //nothing to do
      //else
   int middle = size / 2;       //rounding down doesn't matter

   // Now, we need fresh copies of the two halves.

   string leftTable[middle];
   int rightSize = size - middle;
   string rightTable[rightSize];
   for (int i = 0; i < middle; i++) {     //copy
      leftTable[i] = items[i];
   }
   for (int i = middle; i < size; i++) {
      rightTable[i-middle] = items[i];
   }

   rawMergeSort(leftTable, middle);
   rawMergeSort(rightTable, rightSize);

   // REC INV: leftTable and rightTable are now sorted.
   // Now leftTable and rightTable have always been separate copies from
   // our original array, so no problem zapping our original by
   // passing "first" as the parameter "out" in the merge function.

   rawMerge(leftTable, middle, rightTable, rightSize, items);

}

//---------------------Vector Indexing Versions----------------------------

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
inline void simpleMerge(vector<string> lhs, vector<string> rhs, 
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


//--------------------------main--------------------------------------
   
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
   ifstream* infilep;

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
      infilep = new ifstream(infileName.c_str(), ios_base::in);
      if (! infilep->is_open()) {
         cerr << "Unable to open file: " << infileName << endl;
         return(1);
      }
   } else {    //argc == 1, i.e. no arguments given
      cerr << "Usage: templatesorts file n    with n >= 0" << endl;
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

   // Control here means input & output file streams are OK.
   // Now we create the arrays of (up to) n strings.
   // BECAUSE we want five separate copies, we use C++ VALUES, not pointers!

   vector<string> itemsCopy1(n);
   
   // Now n might be bigger than the number of strings in the file, so
   // we also need to test the input stream for end-of-file etc.

   int numItems = 0; //means # of strings stored thus far AND next free index
   string temp;
   //while (numItems < n && *infilep >> temp) {    //compare "Fubar" note in 
   while(*infilep >> temp && numItems < n) {       //stringsorts.cpp
      // control here means read was good, so store item
      itemsCopy1[numItems++] = temp;
   }
   //now test state of stream upon termination

   if (infilep->eof()) {
      cout << "Read all " << numItems << " whitespace-separated items"
           << " in file " << infileName << endl;
   } else if (infilep->bad()) {
      cerr << "Unrecoverable i/o error, sorry, after " << numItems
           << " items." << endl;
   } else {
      // POST: stream is still good, so we must have hit n items
      cout << "Read " << numItems << " whitespace-separated items from file "
           << infileName << endl;
   }

   // In case numItems is (much) less than n, we resize the vector.
   // (An alternative would have been to create an empty vector and use
   // itemsCopy1.push_back(item) to store items read by (*infilep) >> item.)

   if (numItems < n) {
      itemsCopy1.resize(numItems);
   }
   vector<string> itemsCopy2 = itemsCopy1;   
   vector<string> itemsCopy3 = itemsCopy1;
   vector<string> itemsCopy4 = itemsCopy1;
   vector<string> itemsCopy5 = itemsCopy1;

   string itemsArray6[numItems];
   string* first6 = itemsArray6;
   string* last6 = first6 + numItems;
   int j;
   string* arrp;
   for (j = 0, arrp = first6; arrp != last6; arrp++, j++) {
      *arrp = itemsCopy1[j];
   }
   string itemsArray7[numItems];
   string* first7 = itemsArray7;
   string* last7 = first7 + numItems;
   for (j = 0, arrp = first7; arrp != last7; arrp++, j++) {
      *arrp = itemsCopy1[j];
   }
   //Worth studying why we couldn't combine these for-loops into one
   //for-loop, using the same arrp variable.  But using indexing we can:

   string itemsArray8[numItems];
   string itemsArray9[numItems];
   for (j = 0; j < numItems; j++) {
      itemsArray8[j] = itemsCopy1[j];
      itemsArray9[j] = itemsCopy1[j];
   }


   // ENS: itemsCopy1 and itemsCopy2 etc. hold just the actually-read items.
   // Hence itemsCopy1.end(), last6, etc. will delimit those items correctly.

   HiResTimer* timer = new HiResTimer();

   cout << "Doing insertion sort with raw-array pointers..." << endl;
   timer->reset();
   pointerInsertionSort(first6, last6);  //no need to mention itemsArray6
   double timeForPointerInsertionSort = timer->elapsedTime();

   cout << "Doing merge sort with raw-array pointers..." << endl;
   timer->reset();
   pointerMergeSort(first7, last7);  //no need to mention itemsArray7
   double timeForPointerMergeSort = timer->elapsedTime();


   cout << "Doing insertion sort with raw-array indices..." << endl;
   timer->reset();
   rawInsertionSort(itemsArray8, numItems); 
   double timeForRawInsertionSort = timer->elapsedTime();

   cout << "Doing merge sort with raw-array indices..." << endl;
   timer->reset();
   rawMergeSort(itemsArray9, numItems);  
   double timeForRawMergeSort = timer->elapsedTime();


   cout << "Doing non-templated insertion sort..." << endl;

   timer->reset();
   simpleInsertionSort(itemsCopy1);
   double timeForSimpleInsertionSort = timer->elapsedTime();

   cout << "Doing non-templated user MergeSort..." << endl;

   timer->reset();
   simpleMergeSort(itemsCopy2);
   double timeForSimpleMergeSort = timer->elapsedTime();

   cout << "Doing templated insertion sort (Ch. 10)..." << endl;

   timer->reset();
   insertionSort(itemsCopy3.begin(), itemsCopy3.end());
   double timeForInsertionSort = timer->elapsedTime();

   cout << "Doing templated user MergeSort (Ch. 10)..." << endl;

   timer->reset();
   mergeSort(itemsCopy4.begin(), itemsCopy4.end());
   double timeForMergeSort = timer->elapsedTime();

   cout << "Doing the official STL library sort..." << endl;

   timer->reset();
   std::sort(itemsCopy5.begin(), itemsCopy5.end());
   double timeForSTLSort = timer->elapsedTime();


   cout << fixed << setprecision(3);
   cout << endl;
   cout << "Times for insertion sorts and merge sorts of strings, in "
        << timer->getUnits() << ":" << endl;
   cout << setw(30) << left << "Container and access mode" 
        << setw(15) << right << "Insertion sort" 
        << setw(15) << right << "Merge sort" << endl;
   cout << setw(30) << left << "Raw arrays with indexing:"
        << setw(15) << right << timeForRawInsertionSort 
        << setw(15) << right << timeForRawMergeSort << endl;
   cout << setw(30) << left << "Raw arrays with pointers:"
        << setw(15) << right << timeForPointerInsertionSort 
        << setw(15) << right << timeForPointerMergeSort << endl;
   cout << setw(30) << left << "Vector with indexing:"
        << setw(15) << right << timeForSimpleInsertionSort
        << setw(15) << right << timeForSimpleMergeSort << endl;
   cout << setw(30) << left << "Vector with iterators:" 
        << setw(15) << right << timeForInsertionSort
        << setw(15) << right << timeForMergeSort << endl;
   cout << endl;
   cout << "Time for official STL sorting code: " 
        << timeForSTLSort << endl;

   int ii = 0;
   bool flag = true;
   for (ii = 0; flag && ii < numItems; ii++) {
      flag &= itemsCopy1[ii] == itemsCopy2[ii];
      flag &= itemsCopy1[ii] == itemsCopy3[ii];
      flag &= itemsCopy1[ii] == itemsCopy4[ii];
      flag &= itemsCopy1[ii] == itemsCopy5[ii];
      flag &= itemsCopy1[ii] == itemsArray6[ii];
      flag &= itemsCopy1[ii] == itemsArray7[ii];
      flag &= itemsCopy1[ii] == itemsArray8[ii];
      flag &= itemsCopy1[ii] == itemsArray9[ii];
   }
   cout << (flag ? "Sorts all agree" : ("Sorts disagree at " + itemsCopy1[ii]))
	   << endl;
   for (ii = 0; ii < numItems; ii++) {
      (*outfilep) << itemsCopy1[ii] << endl;
   }
   infilep->close();   //could also do delete(infilep) and delete(outfilep),
   outfilep->close();  //which (should!) call close on the files.
   delete(timer);
      //the vectors automatically get destructed since they are by-value
   return(0);
}

