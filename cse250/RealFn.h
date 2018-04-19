/** File "RealFn.h", by KWR for CSE250, Fall 2009. 
    Real-valued functions f of a single variable "X", and derivatives df/dX.
    Illustrates functions objects, with an abstract base class having
    three null virtual functions.  Goes with text ch. 4, pages 303--306, but:
    Whenever one has a *hierarchy* of function-object classes, they 
    should have an abstract base class and use pointers [or references].

    It is OK to use the (*f).(arg) form rather than f->operator()(arg); i.e.,
    de-referencing and using the dot . does not prevent virtual dispatch.
    However, one /must/ put parens around the *f, because . binds tighter
    than unary (de-referencing) *.  [Here, as with any operator, there
    is an "invisible ." for accessing it as a member.]

    Also illustrates classes with virtual destructors (even in the abstract
    base class!) but which do not need the user to specify copy constructor
    or operator=, because all the underlying data held is constant!
    Finally illustrates "dynamic_cast<Foo*>(p)", which is the C++ analogue
    of the Java "p instanceof Foo" test, in the to-string str() methods.

 */

#include <cmath>     // for log, pow, exp etc.
#include <sstream>   // for double-to-string conversion

using std::log;
using std::exp;
using std::pow;
using std::string;
using std::ostringstream;

namespace Real {
   class MonicFn {
    public:
      virtual ~MonicFn() { }
      virtual double operator() (double x) const = 0;
      virtual MonicFn* dfdx() const = 0;
      virtual string str() const = 0;
   };

   class Constant : public MonicFn {
      const double value;
    public:
      Constant(double value) : value(value) { }
      virtual ~Constant() { }  //OK, value reclaimed
      virtual double operator() (double x) const { 
         return value;  // ignore x
      }
      virtual MonicFn* dfdx() const {
         return new Constant(0.0);
      }
      virtual string str() const {
         ostringstream oss;
         oss << value;
         return oss.str();
      } 
   };

   /** Represents the identity function x.
    */
   class X : public MonicFn {
    public:
      X() { }
      virtual ~X() { }
      virtual double operator() (double x) const {
         return x;
      }
      virtual MonicFn* dfdx() const {
         return new Constant(1.0);
      }
      virtual string str() const { return "x"; }
   };

   class Plus : public MonicFn {
      const MonicFn* const lhs;
      const MonicFn* const rhs;
    public: 
      Plus(const MonicFn* lhs, const MonicFn* rhs) : lhs(lhs), rhs(rhs) { }
      virtual ~Plus() { }
      virtual double operator() (double x) const {
         return (*lhs)(x) + (*rhs)(x);
      }
      virtual MonicFn* dfdx() const {
         return new Plus(lhs->dfdx(), rhs->dfdx());
      }
      virtual string str() const { 
         return lhs->str() + " + " + rhs->str();
      }
   };

   class Minus : public MonicFn {
      const MonicFn* const lhs;
      const MonicFn* const rhs;
    public:
      Minus(const MonicFn* lhs, const MonicFn* rhs) : lhs(lhs), rhs(rhs) { }
      virtual ~Minus() { }
      virtual double operator() (double x) const {
         return (*lhs)(x) - (*rhs)(x);
      }
      virtual MonicFn* dfdx() const {
         return new Minus(lhs->dfdx(), rhs->dfdx());
      }
      virtual string str() const {
         //if rhs is a Plus or Minus, need to put parens around it.
         const MonicFn* p = dynamic_cast<const Plus*>(rhs);
         const MonicFn* q = dynamic_cast<const Minus*>(rhs);
         if (p || q) {
            return lhs->str() + " - (" + rhs->str() + ")";
         } else {
            return lhs->str() + " - " + rhs->str();
         }
      }
   };


   class Times : public MonicFn {
      const MonicFn* const lhs;
      const MonicFn* const rhs;
    public:
      Times(const MonicFn* lhs, const MonicFn* rhs) : lhs(lhs), rhs(rhs) { }
      virtual ~Times() { }
      virtual double operator() (double x) const {
         return (*lhs)(x) * (*rhs)(x);
      }
      virtual MonicFn* dfdx() const {
         return new Plus(new Times(lhs->dfdx(),rhs),
                         new Times(lhs, rhs->dfdx()) );
      }
      virtual string str() const {
         // if rhs or lhs is a Plus or Minus, need to put parens around it.
         //const MonicFn* lp = dynamic_cast<Plus* const>(lhs);
         const MonicFn* lp = dynamic_cast<const Plus*>(lhs);
         const MonicFn* lq = dynamic_cast<const Minus*>(lhs);
         const MonicFn* rp = dynamic_cast<const Plus*>(rhs);
         const MonicFn* rq = dynamic_cast<const Minus*>(rhs);
         string llp = (lp || lq) ? "(" : "";
         string lrp = (lp || lq) ? ")" : "";
         string rlp = (rp || rq) ? "(" : "";
         string rrp = (rp || rq) ? ")" : "";

         return llp + lhs->str() + lrp + "*" + rlp + rhs->str() + rrp;
      }
   };


   class Div : public MonicFn {
      const MonicFn* const num;
      const MonicFn* const denom;
    public:
      Div(const MonicFn* num, const MonicFn* denom)
       : num(num), denom(denom) { }
      virtual ~Div() { }
      virtual double operator() (double x) const {
         return (*num)(x) / (*denom)(x);
      }
      virtual MonicFn* dfdx() const {
         return new Div(new Minus(new Times(denom,num->dfdx()),
                                  new Times(denom->dfdx(),num)),
                        new Times(denom,denom));
      }
      virtual string str() const {
         // compared to Times, we must also bracket a Times or Div on rhs.
         const MonicFn* lp = dynamic_cast<const Plus*>(num);
         const MonicFn* lq = dynamic_cast<const Minus*>(num);
         const MonicFn* rp = dynamic_cast<const Plus*>(denom);
         const MonicFn* rq = dynamic_cast<const Minus*>(denom);
         const MonicFn* rt = dynamic_cast<const Times*>(denom);
         const MonicFn* rd = dynamic_cast<const Div*>(denom);
         string llp = (lp || lq) ? "(" : "";
         string lrp = (lp || lq) ? ")" : "";
         string rlp = (rp || rq || rt || rd) ? "(" : "";
         string rrp = (rp || rq || rt || rd) ? ")" : "";

         return llp + num->str() + lrp + "/" + rlp + denom->str() + rrp;

      }
   };

   class Exp : public MonicFn {   //e^{f(x)}
      const MonicFn* const exponent;
    public:
      Exp(const MonicFn* exponent) : exponent(exponent) { }
      virtual ~Exp() { }
      virtual double operator() (double x) const {
         return std::exp((*exponent)(x));
      }
      virtual MonicFn* dfdx() const {
         return new Times(this, exponent->dfdx());
      }
      virtual string str() const {
         //Put parens around any compound exponent.
         const MonicFn* p = dynamic_cast<const Constant*>(exponent);
         const MonicFn* q = dynamic_cast<const X*>(exponent);
         if (p || q) {
            return "e^" + exponent->str();
         } else {
            return "e^(" + exponent->str() + ")";
         }
      }
   };

   class Ln : public MonicFn {   //ln(f(x))
      const MonicFn* const arg;
    public:
      Ln(const MonicFn* arg) : arg(arg) { }
      virtual ~Ln() { }
      virtual double operator() (double x) const {
         return std::log((*arg)(x));
      }
      virtual MonicFn* dfdx() const {
         //return new Times(arg->dfdx(),new Div(new Constant(1.0),this));
         return new Div(arg->dfdx(), arg);  //line above needs arg^^^^here
      }
      virtual string str() const {
         //Put parens around argument regardless
         return "ln(" + arg->str() + ")";
      }
   };

   class Log : public MonicFn {
      const double base;
      const MonicFn* const arg;
    public:
      Log(double base, const MonicFn* arg) : base(base), arg(arg) { }
      virtual ~Log() { }
      virtual double operator() (double x) const {
         return std::log((*arg)(x)) / std::log(base);
      }
      virtual MonicFn* dfdx() const {
         return new Times(new Constant(1/std::log(base)),
                          new Div(arg->dfdx(), arg) );
      }
      virtual string str() const {
         //Put parens around every argument
         ostringstream oss;
         oss << base;
         return "log_" + oss.str() + "(" + arg->str() + ")";
      }
   };

   class Pow : public MonicFn {   //f(x)^{g(x)}, == e^{g(x)ln(f(x))}
      const MonicFn* const base;
      const MonicFn* const exponent;
    public:
      Pow(const MonicFn* f, const MonicFn* g) : base(f), exponent(g) { }
      virtual ~Pow() { }
      virtual double operator() (double x) const {
         return std::pow((*base)(x), (*exponent)(x));
      }
      virtual MonicFn* dfdx() const {
         MonicFn* lazy = new Exp(new Times(exponent, new Ln(base)));
         return lazy->dfdx();
      }
      virtual string str() const {
         return "(" + base->str() + ")^{" + exponent->str() + "}";
      }
   };

   class PowB : public MonicFn {   //f(x)^{g(x)}, == e^{g(x)ln(f(x))}
      const MonicFn* const base;
      const MonicFn* const exponent;
    public:
      PowB(const MonicFn* f, const MonicFn* g) : base(f), exponent(g) { }
      virtual ~PowB() { }
      virtual double operator() (double x) const {
         return std::pow((*base)(x), (*exponent)(x));
      }
      virtual MonicFn* dfdx() const {
         MonicFn* lhs = new Times(new Div(base->dfdx(), base), exponent);
         MonicFn* rhs = new Times(new Ln(base), exponent->dfdx());
         return new Times(this, new Plus(lhs, rhs));
      }
      virtual string str() const {
         return "(" + base->str() + ")^{" + exponent->str() + "}";
      }
   };


};  //end of namespace Real



