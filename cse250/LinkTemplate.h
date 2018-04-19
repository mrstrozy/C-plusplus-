/** File "LinkTemplate.h", by KWR for CSE250, Fall 2009.
    Illustrates a template class that *assumes* its argument classes
    define a particular member function, here "compare"---see the .cpp file.
    Question: does YOUR compiler generate an error before linking?

    Also illustrates how to do ".h, .cpp" for a template class, and the
    "ifndef" directive with the all-caps+underscore_H naming convention
 */
#ifndef LINKTEMPLATE_H_
#define LINKTEMPLATE_H_

using namespace std;

/** Requires template argument to define: int compare(const T&) const
    ^^^A "requirement comment".
 */
template <class T>     //"class" not "typename" since we assume a method(!)
class LinkTemplate {   //class LinkTemplate<T> is a horrible error! Try it!
 public:
   LinkTemplate();     //Here <T> is optional; text leaves it out.

   bool lessThan(const T& lhs, const T& rhs) const;
};


// CSE250: Owing to g++ linker quirks, we will put implementation
// code for templates in the .h file, not in a separate .cpp file.
// As in the text, it is AOK to inline *short* bodies inside the 
// class braces, but long ones should go outside, like this:

/** Requires template client type to define int compare(const T&) const
 */
template <class T>
LinkTemplate<T>::LinkTemplate() { } //first <T> required, second <T> error!

template <class T>
bool LinkTemplate<T>::lessThan(const T& lhs, const T& rhs) const {
   return (lhs.compare(rhs) < 0);
}

#endif
