/** File "FlexArrayMRS.h", by MRS.
    Templated Data-structure file for Project 1.  Students need to add:
    (*) Iterator class---in labs from April 8 to 11

    (*) Methods T at(int j), iterator insert(iterator pos, const T& newItem), 
        iterator erase(iterator pos) due on April 14

    (*) Project with expanded client due Mon. April 21.
 */

#ifndef _FLEXARRAY_H_
#define _FLEXARRAY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>

using std::vector;
using std::endl;
using std::cerr;
using std::ostringstream;
using std::runtime_error;


template <typename T>    //REQ: T has T() and T.str()
class FlexArray;

//template <typename T>
//class FlexArray::iterator;

template <typename T>
class ChunkNode {
   vector<T>* elements;

   ChunkNode<T>* prev;          //optional, to make doubly-linked list
   ChunkNode<T>* next;       //typename is illegal here

   FlexArray<T>* myList;   //unnecessary? 
   size_t mySize;            //INV: # of elements actually stored
   friend class FlexArray<T>;
   friend class FlexArray<T>::iterator;   //begin lab with this line

 public:
   ChunkNode<T>(FlexArray<T>* myList, ChunkNode<T>* myPrev,
                                      ChunkNode<T>* myNext)
    : elements(new vector<T>(0)), prev(myPrev), next(myNext),
      myList(myList), mySize(0)
   { }
};

template <class T>
class FlexArray {
   ChunkNode<T>* firstNode;
   ChunkNode<T>* endNode;
   size_t nodeCap;
   size_t numNodes;
   //friend class ChunkNode<T>;   //IMHO not necessary

   //CLASS INV: endNode is a dummy node, used as target for iterations.
   //firstNode is a real node only when the FlexArray is nonempty (Optional change)
   //Empty is size() == 0, rather than endNode == firstNode.
   //Note: for empty FlexArray, rbegin() cannot assume endNode->prev is
   //non-NULL.  For empty FlexArray, both begin() and rbegin() should == end()
   //MOST IMPT: every non-dummy node is nonempty---empty elements means de-allocate node.

 public:
      
   explicit FlexArray<T>(size_t nodeCap) 
    : firstNode(new ChunkNode<T>(this,NULL,NULL))
    , endNode(firstNode)
    , nodeCap(nodeCap)
    , numNodes(1)
    {}

   explicit FlexArray<T>()
    : firstNode(new ChunkNode<T>(this,NULL,NULL))
    , endNode(firstNode)
    , nodeCap(40)
    , numNodes(1)
   { }
                       
   class iterator {                   //does not need "template <typename T>" since nested
                                      //CANNOT see (non-static) fields of FlexArray directly.
      FlexArray<T>* myList;           //Hence having a "myList" field might be a good idea.
      ChunkNode<T>* node;
      size_t localIndex;
      friend class FlexArray<T>;
      public:
      iterator(FlexArray<T>* myList, ChunkNode<T>* node, size_t li):
      myList(myList) , node(node) , localIndex(li) {}

      T& operator*() const{
         if(node == NULL || node == myList->endNode){
            cerr << "Local Index is out of bounds." << endl;
            return node->elements->at(myList->end().localIndex) ;
         }
         return node->elements->at(localIndex);
      }

      iterator& operator ++ (){ //pre-increment operator

         if(node == NULL || node == myList->endNode){
            cerr << "Out of range." << endl;
            return *this;
         }
         localIndex++;
         if(localIndex == node->elements->size()){
            node = node->next;
            localIndex = 0;
         }
         return *this;
      }
      iterator operator ++(int ignored){ //post-increment operator
      
         iterator copy = *this;
         operator ++();
         return copy;
      }
      bool operator ==(const iterator& rhs) const{
         return node == rhs.node && localIndex == rhs.localIndex
            && myList == rhs.myList;
      }
      bool operator !=(const iterator& rhs) const{
         return node != rhs.node || localIndex != rhs.localIndex
            || myList != rhs.myList;
      }

   };

   iterator begin(){
      return  iterator(this,firstNode,0);
   }
   iterator end(){
      return  iterator(this,endNode,0);
   }
   iterator rbegin(){
      return iterator(this,endNode->prev, endNode->prev->elements->size-1);
   }
   int size(){
      int size = 0;
      iterator it = begin();
      while(it != end()){
         size++;
         it++;
      }
      return size;
   }
   bool empty(){return firstNode == endNode;}

   T& at(size_t index){
      ChunkNode<T>* temp = firstNode;
      //size_t i = 0;

      while( temp != endNode && temp->mySize-1 < index){
         index = index - temp->mySize;
         temp = temp->next;
      }
      if(temp == endNode){
         throw std::out_of_range( "Index is out of bounds.");
    } else {
         return temp->elements->at(index);
      }
   } 



/*************************************************************************
**A couple cases to consider when inserting:
**
**--->[X]is the iterator over the same data?
**--->[X]are we inserting somewhere in the middle?
**--->[X]are we inserting to the end of a node that is full?      <---|Can we do these with the same code?
**--->[X]are we inserting to the very front when nodeCap is full? <---|
**--->[X]are we just inserting to the very front?
**--->[X]are we inserting to the back when the last node is full?
**--->[X]are we inserting in the middle of a node that is full?
**
**--->**Remember to increment mySize of ChunkNode after inserting
**
*************************************************************************/

   iterator insert(iterator pos, const T& newItem){

      iterator temp = begin();
      //Check to see if iterator is going over the same data
      if(this != pos.myList){
         std::cout << "Iterators are not over the same data" << endl;
         return pos;
      }
      /*if(empty){
         ChunkNode<T>* newNode = ChunkNode<T>(this,firstNode,NULL);
         
      }*/
      if(pos.node == endNode && !empty()){
         std::cout << "Cannot insert into the end node" << endl;
         return pos;
      }
      if(empty()){
         ChunkNode<T>* newNode = new ChunkNode<T>(this,NULL,endNode);
         firstNode = newNode;
         firstNode->elements->push_back(newItem);
         firstNode->mySize++;
         return begin();

      }

      //inserting into front of FlexArray      
      if(pos.node == firstNode && pos.localIndex == 0){ 
         if(nodeIsFull(firstNode)){//we need to create a new head node
          
            //INV:firstNode is always the first node of Flex Array
            ChunkNode<T>* newNode = new ChunkNode<T>(this,NULL,firstNode);
            firstNode->prev = newNode;
            firstNode = newNode;
           
            firstNode->elements->push_back(newItem);
            firstNode->mySize++;
            //temp = begin();  Not needed
            return begin();
       } else {
            typename vector<T>::iterator it = firstNode->elements->begin();
            firstNode->elements->insert(it,newItem);
            firstNode->mySize++;
            return begin();
         }
      }


      //inserting at local index 0 of a node and NOT at the firstNode
      if(pos.localIndex == 0 && pos.node != firstNode){
         if(nodeIsFull(pos.node) && nodeIsFull(pos.node->prev)){
               ChunkNode<T>* newNode = new ChunkNode<T>(this,pos.node->prev,pos.node);
               newNode->prev->next = newNode;
               pos.node->prev = newNode; 
               newNode->elements->push_back(newItem);
               newNode->mySize++;
               return iterator(this,newNode,0);

         }  else {//pos.prev is not full
               pos.node->prev->elements->push_back(newItem);
               pos.node->prev->mySize++;
               return iterator(this,pos.node->prev,pos.node->mySize-1);
         }
       } 
      

       //TO DO: Splicing node if you are trying to insert into the middle of a full node
       //TO DO: Last case that takes all other scenarios
      if(nodeIsFull(pos.node)){
         ChunkNode<T>* newNode = new ChunkNode<T>(this,pos.node,pos.node->next);
         pos.node->next = newNode;
         newNode->next->prev = newNode;
         typename vector<T>::iterator first = pos.node->elements->begin();//holds first position for elements to be erased         
         typename vector<T>::iterator last = pos.node->elements->begin();//holds last position for elements to be erased
         typename vector<T>::iterator insertLocation = pos.node->elements->begin();
         size_t insertIndex = 0;
         for(size_t i = 0; i < pos.node->mySize;i++){
            if(i < pos.localIndex){
               insertLocation++;
            } 
            if(i < (pos.node->mySize-1/2)){
            first++;
            last++;
         }  else {
            newNode->elements->push_back(pos.node->elements->at(i));
            newNode->mySize++;//increase size of new node by 1 after pushing to the back
            pos.node->mySize--;//decrease spliced node size by 1
            last++;
            } 
         }   
         pos.node->elements->erase(first,last);
         pos.node->elements->insert(insertLocation,newItem);
         return pos;
    } else {
         typename vector<T>::iterator position = pos.node->elements->begin();
         for(int i = 0; i < pos.localIndex;i++){
            position++;
         }
         pos.node->elements->insert(position,newItem);
         pos.node->mySize++;
         return pos;  
      } 
         
            
   }

/**********************************************************************
**
**Things to consider when writing erase:
**
**--->[X]iterator on the same flex array?
**--->[X]is the flex array empty?
**--->[]re-assigning after erasing from a vector causes it to become empty
**--->[X]iterator pos is at endNode
**--->[X]erasing from the back of the vector
**--->[]erase only item from vector and thus have to reassign pointers
**
**
**--->Don't forget to decrement mySize after erasing
**********************************************************************/


   //REQ:Iterator is over the same flex array, flex array is not empty,
   //    and pos is not on the end node.
   iterator erase(iterator pos){
      
      if(this != pos.myList){
         std:: cout << "Iterator doesn't go over same data." << endl;
         return pos;
      } 
      if(empty()){
         std::cout << "Cannot erase from an empty FlexArray" << endl;
         return pos;
      }
      if(pos.node == endNode){
         std:: cout << "Cannot erase from the end node." << endl;
         return pos;
      }
    
      
      //if erasing one element won't cause the node to be empty
      if(pos.node->mySize > 1){ 
         typename vector<T>::iterator it = pos.node->elements->begin();
         for(int i = 0; i < pos.localIndex;i++){
            it++;
         }
         pos.node->elements->erase(it);
         pos.node->mySize--;
         if(pos.localIndex == pos.node->mySize-1){
            return iterator(this,pos.node,--pos.localIndex);
       } else {
            
            return pos;
         }
    } else {
         if(pos.node->next == endNode && pos.node == firstNode){
            firstNode = endNode;
            delete pos.node;
            return begin();
       } else if(pos.node->next == endNode){
            pos.node->prev->next = endNode;
            endNode->prev = pos.node->prev;
            delete pos.node;
            return iterator(this,pos.node->prev,pos.node->mySize-1);
       } else if(pos.node == firstNode){
            firstNode = firstNode->next;
            delete pos.node; 
            return begin();
       } else{
            return iterator(this,pos.node->next,0);
       }
         //delete temp;
         return pos;
         }
     
      
   }   
   const std::string toString() {
      ostringstream OUT;
      for(iterator it = begin(); it.node != endNode; it++) {
         OUT << it.node->elements->at(it.localIndex) << " ";
      } 
      std::cout << endl;
      return OUT.str();
   }
 
   private:
      //REQ:"one" starts from beginning to find node before "two"
      iterator findNode(iterator one, iterator two){
         while(one->node != two->node){
            one++;
         }
         return one;
      }
      iterator setLocalIndex(iterator it,size_t index){
         while(it->localIndex != index){
            it++;
         }
         return it;
      }
      bool nodeIsFull(ChunkNode<T>* tester){return tester->mySize == nodeCap;} 


  /* T &operator [](int index){
      ChunkNode<T>* temp = firstNode;
      int i = 0;
      std::cout << "Index is: " << index << endl; 
     // while(temp->next() != endNode && i != index){
     //    if(temp->
         return *this;
      }
  */ //at, insert, erase, operator[] etc. methods go here...
};

template<typename T>
std::ostream& operator<<(std::ostream& out,FlexArray<T>& fs){
   out << fs.toString();
   return out;
}


#endif
