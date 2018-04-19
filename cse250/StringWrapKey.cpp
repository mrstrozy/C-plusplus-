/** File "StringWrapKey.cpp", by KWR for CSE250, Fall 2009.  
    Coded answer to Assignment 2, problem (3), together with "StringSeqs.cpp"
 */

#include "StringWrapKey.h"

StringWrap::StringWrap(string s) : st(s) { }   //no "explicit" here

void StringWrap::trimNonAlpha() {              //no "virtual" here
   int sz = st.size();
   int left = 0;
   int right = sz-1;

   // LOOP INV: all alpha chars are between left and right.
   // Note: right is on-end, rather than past-the-end, of this range

   while ((left < sz)
           && !( ('a' <= st[left] && st[left] <= 'z')
                || ('A' <= st[left] && st[left] <= 'Z') ) ) {
      left++;
   }
   // POST: if there are any alpha characters, left is on one
   while ((right >= 0)
           && !( ('a' <= st[right] && st[right] <= 'z')
                || ('A' <= st[right] && st[right] <= 'Z') ) ) {
      right--;
   }
   // POST: if any alpha chars, right is on one and >= left.
   // But if st is all-non-alpha, then right < left is possible.
   // Since the behavior of substr with a negative length is 
   // **formally undefined** in the C++ standard, we need one more test.

   int alphaLength = right - left + 1;  // + 1 since on-end

   st = (alphaLength <= 0) ? "" : st.substr(left,alphaLength);
}

void StringWrap::makeLower() {
   int sz = st.size();
   for (int i = 0; i < sz; i++) {
      if ('A' <= st[i] && st[i] <= 'Z') {
         st[i] += 32;
      }
   }
}

bool StringWrap::isAlpha() const {
   int sz = st.size();
   for (int i = 0; i < sz; i++) {
      if (!( ('a' <= st[i] && st[i] <= 'z')
            || ('A' <= st[i] && st[i] <= 'Z') ) ) {
         return false;
      }
   }
   return true;
}

bool StringWrap::isAllCaps() const {
   int sz = st.size();
   for (int i = 0; i < sz; i++) {
      if (! ('A' <= st[i] && st[i] <= 'Z') ) {
         return false;
      }
   }
   return true;
}


/** Find longest prefix in alpha or reverse-alpha order, by the
    ASCII collating sequence.  Does not force st to be alphabetic.
    REQ: st.size() >= 2;
    ENS: returned string has size >= 2.
 */
string StringWrap::longestProgression() const {
   int i = 1;
   int sz = st.size();
   // PRE: i-1 is a valid index

   while (i < sz && st[i] == st[i-1]) {
      i++;  // LOOP INV: All chars up thru i=1 are equal.
   }
   // POST: i marks the first char different from its predecessor.

   if (i == sz) {           // sequence is all equal, e.g. "aaaa"
      return st;
   } else if (st[i] < st[i-1]) {   // sequence is descending
      i++;
      while (i < sz && st[i] <= st[i-1]) {
         i++;
      }
      // now either i is past-the-end or i marks the char that
      // stops the descent.  Either way, we want to return i-many chars.
   } else if (st[i] > st[i-1]) {   // sequence is ascending
      i++;
      while (i < sz && st[i] >= st[i-1]) {
         i++;
      }
   }  // ditto
   return st.substr(0,i);
}
   

string StringWrap::longestProgressionSafer() const {
   int sz = st.size();
   if (sz <= 1) {
      return st;
   } else {
      return longestProgression();
   }
}

int StringWrap::seq() const {
   return longestProgression().size();
}

string StringWrap::str() const {
   return st;
}

int StringWrap::size() const {
   return st.size();
}

bool operator<(const StringWrap& lhs, const StringWrap& rhs) {
   return lhs.st < rhs.st;
}
