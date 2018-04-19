/// Java: file Complex.java, by KWR for CSE250, Spring'00.
/// import java.Math.*;  //doesn't work---Math is a class not a package.  
/// Hence you have to write "Math.sqrt", not just "sqrt" as in C++.

class Complex{
/// in Java, "private" must go with each item.
   private double xx;
   private double yy;
///end of class data
   public Complex(double x, double y){
      xx = x; yy = y;   ///...which Java lacks!
   }
   public double getxx(){return xx;}  ///Java lacks "const".
   public double getyy(){return yy;}
   public double norm(){        ///(*)
      return Math.sqrt(xx*xx + yy*yy);
   } ///Java has no operator overloading---write "x.add(y)".
   public Complex add(Complex y){
      return new Complex(xx+y.getxx(), yy+y.getyy());
   }
} ///in Java, class does NOT end with a ";'!
