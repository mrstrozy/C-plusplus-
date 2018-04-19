#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

int main(){

Node<string>* head = new Node<string>("sam");
head = new Node<string>("matt",head);


cout << "Data: " << head->data << endl;
cout << "NextData: " << head->next->data << endl;
return 0;
}
