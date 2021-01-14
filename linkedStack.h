// Linked Stack as implented by me Cody Gronning
// www.github.com/CodingWithCody

// This file defintes the linkedStack class and conatins all necessary functions
// for creating a linked stack and performing basic operations upon that stack

#include <iostream>
#include <string>

using namespace std;

/*template <class T>
struct nodeType{
  T info;
  nodeType<T> *next;
};
*/
template <class T>
class linkedStack{
public:
  linkedStack();
  linkedStack(const linkedStack<T>&);
  ~linkedStack();
  bool operator==(const linkedStack<T>&);
  bool operator!=(const linkedStack<T>&);
  linkedStack<T> operator=(const linkedStack<T>&);
  void deleteStack();
  bool isStackEmpty() const;
  void push(const T&);
  T peek() const;
  T pop();
  int stackCount() const;
  T stackSum() const;
private:
  nodeType<T> *stackTop;
  int count;
  T rSum(nodeType<T> *) const;
  void copyStack(const linkedStack<T>&);
};

//default constructor for an empty stack
template <class T>
linkedStack<T>::linkedStack(){
  stackTop = nullptr;
  count = 0;
}

//copy constructor, see copyStack for more details
template <class T>
linkedStack<T>::linkedStack(const linkedStack<T>& stack){
  stackTop = nullptr;
  count = 0;
  copyStack(stack);
}

//destructor for reallocation of memory, see deleteStack for more info
template <class T>
linkedStack<T>::~linkedStack(){
  deleteStack();
}

//overloading the == operator to ensure each stack node has the same info
template <class T>
bool linkedStack<T>::operator==(const linkedStack<T>& list){
  nodeType<T> *temp1;
  temp1 = this->stackTop;
  nodeType<T> *temp2;
  temp2 = list.stackTop;

  //check for empty stacks
  if (temp1 == nullptr && temp2 == nullptr) {
    return true;
  }

  //check if either stack is empty
  if (temp1 == nullptr || temp2 == nullptr) {
    return false;
  }

  //check first node
  if (temp1->info != temp2->info) {
    return false;
  }

  //make sure each other node's info is equivalent
  while (temp1->link != nullptr && temp2->link != nullptr) {
    temp1 = temp1->link;
    temp2 = temp2->link;
    if (temp1->info != temp2->info) {
      return false;
    }
  }

  //check that one list is not longer than the other
  if (temp1->link != nullptr || temp2->link != nullptr) {
    return false;
  }

  //if so return true
  return true;
}

//overloading the != operator to ensure each stack node has the same info
template <class T>
bool linkedStack<T>::operator!=(const linkedStack<T>& list){
  nodeType<T> *temp1;
  temp1 = this->stackTop;
  nodeType<T> *temp2;
  temp2 = list.stackTop;

  //check for empty stacks
  if (temp1 == nullptr && temp2 == nullptr) {
    return false;
  }

  //check if either stack is empty
  if (temp1 == nullptr || temp2 == nullptr) {
    return true;
  }

  //check first node
  if (temp1->info != temp2->info) {
    return true;
  }

  //check if each other node's info is equivalent
  while (temp1->link != nullptr && temp2->link != nullptr) {
    temp1 = temp1->link;
    temp2 = temp2->link;
    if (temp1->info != temp2->info) {
      return true;
    }
  }

  //check if one list is longer than the other
  if (temp1->link != nullptr || temp2->link != nullptr) {
    return true;
  }

  //otherwise return false
  return false;
}

//overload the = operator to do a deep copy of a stack, see copyStack for more info
template <class T>
linkedStack<T> linkedStack<T>::operator=(const linkedStack<T>& list){
  copyStack(list);
  return *this;
}

//check if a stack is empty
template <class T>
bool linkedStack<T>::isStackEmpty() const{
  if (stackTop == nullptr) {
    return true;
  }
  return false;
}

//push an item onto the stack
template <class T>
void linkedStack<T>::push(const T& item){
  nodeType<T> *newNode;
  newNode = new nodeType<T>;
  newNode->info = item;
  newNode->link = nullptr;
  count++;

  //check if the stack is empty and add the first node if so
  if (stackTop == nullptr) {
    stackTop = newNode;
    return;
  }

  //Otherwise push it onto the stack
  else{
    newNode->link = stackTop;
    stackTop = newNode;
    return;
  }
}

//return the value from the top of the stack but do not remove it
template <class T>
T linkedStack<T>::peek() const{
  if (isStackEmpty()) {
    cout << "Error, stack is empty." << endl;
    return {};
  }
  return stackTop->info;
}

//return the value on top the stack and then remove the item from the stack
template <class T>
T linkedStack<T>::pop(){
  if (stackTop == nullptr) {
    cout << "Error, stack is empty." << endl;
    return {};
  }
  T item = stackTop->info;
  nodeType<T> *temp;
  temp = stackTop;
  stackTop = stackTop->link;
  delete temp;
  count--;
  return item;
}

//return the total number of items on the stack
template <class T>
int linkedStack<T>::stackCount() const{
  return count;
}

//return the sum of all items in the stack
template <class T>
T linkedStack<T>::stackSum() const{
  return rSum(stackTop);
}

//deep copy the passed in stack, delete the current stack first if it is not empty
template <class T>
void linkedStack<T>::copyStack(const linkedStack<T>& list1){
  if (stackTop != nullptr) {
    deleteStack();
  }

  nodeType<T> *temp;
  nodeType<T> *inList;
  inList = list1.stackTop;

  //copy the first node and set first appropriately
  nodeType<T> *newNode;
  newNode = new nodeType<T>;
  newNode->info = inList->info;
  newNode->link = nullptr;
  stackTop = newNode;
  temp = newNode;

  inList = inList->link;
  while (inList != nullptr) {
    newNode = new nodeType<T>;
    newNode->info = inList->info;
    temp->link = newNode;
    inList = inList->link;
    temp = temp->link;
  }

  temp->link = nullptr;
  count = list1.stackCount();
}

//destroy the stack and initialize class variables back to an empty stack
template <class T>
void linkedStack<T>::deleteStack(){
  nodeType<T> *temp, *current;
  current = stackTop;
  while (current != nullptr) {
    temp = current;
    current = current->link;
    delete temp;
  }

  stackTop = nullptr;
  count = 0;
}

//recursivley calculate the sum of all items in the stack
template <class T>
T linkedStack<T>::rSum(nodeType<T> *node) const{
  if (node == nullptr)
    return 0;
  return node->info + rSum(node->link);
}
