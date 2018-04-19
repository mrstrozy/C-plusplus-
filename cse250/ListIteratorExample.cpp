/** File "ListIteratorExample.cpp", by Br, Stojkovic for CSE250, Fall 2011.
    Copies palindrome from vector to list using iterators, 
    then prints list in both directions.
 */
 
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

	vector<string> palindromeV;  // vector from STL
	list<string>   palindromeL; //  doubly linked list from STL
	
	//Populating the vector.
	palindromeV.push_back("You");
	palindromeV.push_back("can");
	palindromeV.push_back("cage");
	palindromeV.push_back("a");
	palindromeV.push_back("swallow");
	palindromeV.push_back("can't");
	palindromeV.push_back("you,");
	palindromeV.push_back("but");
	palindromeV.push_back("you");
	palindromeV.push_back("can't");
	palindromeV.push_back("swallow");
	palindromeV.push_back("a");
	palindromeV.push_back("cage");
	palindromeV.push_back("can");
	palindromeV.push_back("you?");
	
	
	//Copying words from vector to list
	vector<string>::const_iterator cvi;
    for(cvi = palindromeV.begin(); cvi!=palindromeV.end(); cvi++) {
	      palindromeL.push_front(*cvi); //
	}
	
	//Printing list from front to back
	cout << "-- List: front to back --"<<endl;
	list<string>::const_iterator cli;	 
	for(cli = palindromeL.begin(); cli != palindromeL.end(); cli++){ 
		cout << *cli << " ";
	}
	cout << endl;	 

	//Printing list in reverse order
	cout << "-- List: back to front --"<<endl;
	list<string>::reverse_iterator rli;	 
	for(rli = palindromeL.rbegin(); rli != palindromeL.rend(); rli++){ 
		cout << *rli << " ";
	}
	cout << endl;	 

	
	//Removing and altering elements that iterator is pointing to
	cout << "-- Altered list --"<<endl;
	for(list<string>::iterator itr = palindromeL.begin(); itr != palindromeL.end();){
        if ( !itr->compare("can't") || !itr->compare("can") || !itr->compare("you") || !itr->compare("you,")){			
            itr = palindromeL.erase(itr); 
        }else if(!itr->compare("but")){
			*itr = "###";
		}else{
			++itr;
		}	   
    }	
	
	//Removing and printing list elements.
	while (!palindromeL.empty()){     
		cout<< palindromeL.front()<<" ";
		palindromeL.pop_front();
	}
	cout<<endl;	
	
	return 0;

}
