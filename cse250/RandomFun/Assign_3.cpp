#include <iostream>
#include <string>
using namespace std;

bool hd1(string,string);
bool xd1(const string&,const string&);
bool ed1(const string&, const string&);

bool hd1(string x,string y){
    
    int diff = 0;
    for(int i = 0; i < x.length(); i++){
       if(x[i] != y[i])
         diff++;
    }
    cout << "x: " << x << " y: " << y << endl;
    cout << "Diff: " << diff << endl;
    return diff == 1;
}
bool xd1(const string& x, const string& y){
    if(x == "" || y == "")
       return false;
    string xcp, ycp;
    
    if(x.length() > y.length()){
       xcp = x;
       ycp = y;
  } else {
       xcp = y;
       ycp = x;
  }
    if(xcp.length() - ycp.length() > 1)
       return false;

    if(xcp.length() == ycp.length())
       return hd1(xcp,ycp);
    else if(xcp[0] == ycp[0]){
       ycp += '!';
       return hd1(xcp,ycp);
  } else {
       string temp = "!";
       temp += ycp;
       cout << "Temp: " << temp << endl;
       return hd1(xcp,temp);
  }
}
bool ed1(const string& x,const string& y){
    string xc, yc;
    if(x.size() > y.size()){
       xc = x;
       yc = y;
  } else {
       xc = y;
       yc = x;
    }
    if(xc == "" || yc == "")
       return false;
    if(xc.size() - yc.size() > 1)
       return false;
    if(xc.size() == yc.size())
       return hd1(xc,yc);
    
    
    //strings are exactly 1 char apart with xc being the larger string
    
    if(xc[0] == yc[0] && xc[xc.size()-1] == yc[yc.size()-1]){
       for(int i = 1; i < xc.size()-1; i++){
          if(xc[i] != yc[i]){
             string temp = "";
             for(int j = 0; j < yc.size(); j++){
                if(j != i){
                   temp += yc[j];
              } else {
                   temp += '!';
                   temp += yc[j];
                } 
             }//Both strings have the same size          
             return hd1(temp,xc);
          }
       }//First and Last Char were not the same
  } else if(xc[0] == yc[0]){
       string temp = yc;
       temp += '!';
       return hd1(temp,xc);
  } else {
       string temp = "!";
       temp += yc;
       return hd1(temp,xc);
    }  
}   
     

int main(){

    cout << "The result of ed1 is: " << hd1("Rain","Cawn") << endl << endl;
    cout << "The result for xd1 of \"Rain\" and \"Rains\" is: " << xd1("Rain","Rains") << endl << endl;
    cout << "The result for xd1 of \"Rain\" and \"Raids\" is: " << xd1("Rain","Raids") << endl << endl;  
    cout << "The result for xd1 of \"rain\" and \"grain\" is: " << xd1("rain","grain") << endl << endl;
    cout << "The result for xd1 of \"rains\" and \"grain\" is: " << xd1("rains","grain") << endl << endl;
    cout << "The result for xd1 of \"rain\" and \"grains\" is: " << xd1("rain","grains") << endl << endl;
    cout << "The result for xd1 of \"rainings\" and \"grainings\" is: " << xd1("rainings","grainings") << endl << endl;
   

    cout << endl << endl << endl  << endl << endl << endl; 
    cout << "ed1: " << endl << endl;
    cout << "Rain , Cawn =  " << ed1("Rain","Cawn") << endl << endl;
    cout << "Rain , Rains = " << ed1("Rain","Rains") << endl << endl;
    cout << "Rain , Raids = " << ed1("Rain","Raids") << endl << endl;
    cout << "Rain , Rabin = " << ed1("rain","rabin") << endl << endl;
    cout << "Rains , Rain = " << ed1("rains","rain") << endl << endl;
    cout << "Rain , Raisns = " << ed1("rain","raisns") << endl << endl;
    cout << "qwertyuip , qwertbyuip  " << ed1("qwertyuiop","qwertbyuiop") << endl << endl;


    return 0;
}
