// Linked Queue as implented by me Cody Gronning
// www.github.com/CodingWithCody

// This file defintes the linkedQueue class and conatins all necessary functions
// for creating a linked queue and performing basic operations upon that queue

#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

template <class T>
struct nodeType{
  T info;
  nodeType<T> *next;
};

template <class T>
class linkedQueue{
public:
  bool operator==(const linkedQueue<T>&);
  bool operator!=(const linkedQueue<T>&);
  linkedQueue<T> operator=(const linkedQueue<T>&);
  linkedQueue();
  linkedQueue(const linkedQueue<T>&);
  ~linkedQueue();
  void deleteQueue();
  bool isQueueEmpty() const;
  void addQueue(const T&);
  T remQueue();
  T peekQueue() const;
  int queueCount() const;
private:
  nodeType<T> *front, *back;
  mutex queMutex;
  int count;
  void copyQueue(const linkedQueue<T>&);
};

//overloading the == operator to ensure each queue node has the same info
template <class T>
bool linkedQueue<T>::operator==(const linkedQueue<T>& list){
  nodeType<T> *temp1;
  temp1 = this->front;
  nodeType<T> *temp2;
  temp2 = list.front;

  //check for empty queues
  if (temp1 == nullptr && temp2 == nullptr) {
    return true;
  }

  //check if either queue is empty
  if (temp1 == nullptr || temp2 == nullptr) {
    return false;
  }

  //check first node
  if (temp1->info != temp2->info) {
    return false;
  }

  //make sure each other node's info is equivalent
  while (temp1->next != nullptr && temp2->next != nullptr) {
    temp1 = temp1->next;
    temp2 = temp2->next;
    if (temp1->info != temp2->info) {
      return false;
    }
  }

  //check that one queue is not longer than the other
  if (temp1->next != nullptr || temp2->next != nullptr) {
    return false;
  }

  //if so return true
  return true;
}

//overloading the =! operator to ensure each queue node has the same info
template <class T>
bool linkedQueue<T>::operator!=(const linkedQueue<T>& list){
  nodeType<T> *temp1;
  temp1 = this->front;
  nodeType<T> *temp2;
  temp2 = list.front;

  //check for empty queues
  if (temp1 == nullptr && temp2 == nullptr) {
    return false;
  }

  //check if either queue is empty
  if (temp1 == nullptr || temp2 == nullptr) {
    return true;
  }

  //check first node
  if (temp1->info != temp2->info) {
    return true;
  }

  //check if each other node's info is equivalent
  while (temp1->next != nullptr && temp2->next != nullptr) {
    temp1 = temp1->next;
    temp2 = temp2->next;
    if (temp1->info != temp2->info) {
      return true;
    }
  }

  //check if one queue is longer than the other
  if (temp1->next != nullptr || temp2->next != nullptr) {
    return true;
  }

  //otherwise return false
  return false;
}

//overload the = operator to do a deep copy of a queue, see copyQueue for more info
template <class T>
linkedStack<T>::operator=(const linkedStack<T>& queue){
  copyQueue(queue);
  return *this;
}

//basic constructor to initialize all pointers
template <class T>
linkedQueue<T>::linkedQueue(){
  front = nullptr;
  back = nullptr;
  count = 0;
}

//copy constructor, see copy queue for more details
template <class T>
linkedQueue<T>::linkedQueue(const linkedQueue<T>&){
  front = nullptr;
  back = nullptr;
  count = 0;
}

//destructor, see deleteQueue for more info
template <class T>
linkedQueue<T>::~linkedQueue(){
  deleteQueue();
}

//delete all items from the queue and initialize to empty state
template <class T>
void linkedQueue<T>::deleteQueue(){
  nodeType<T> *temp, *current;
  current = front;
  while (current != nullptr) {
    temp = current;
    current = current->next;
    delete temp;
  }

  front = nullptr;
  back = nullptr;
}

//check if the queue is empty and return true if so
template <class T>
bool linkedQueue<T>::isQueueEmpty() const{
  if (this->front == nullptr) {
    return true;
  }

  return false;
}

//add an item to the back of the queue
template <class T>
void linkedQueue<T>::addQueue(const T& item){
  nodeType<T> *newNode;
  newNode = new nodeType<T>;
  newNode->info = item;
  newNode->next = nullptr;
  count++;

  //check if the queue is empty and add the first node if so
  if (back == nullptr) {
    back = newNode;
    front = newNode;
    return;
  }

  //Otherwise add it into the back of the queue
  else{
    back->next = newNode;
    back = newNode;
    return;
  }
}

//remove and return the front item of the queue
template <class T>
T linkedQueue<T>::remQueue(){
  if (front == nullptr) {
    cout << "Error, queue is empty." << endl;
    return {};
  }
  T item = front->info;
  nodeType<T> *temp;
  temp = front;
  front = front->next;
  delete temp;
  count--;
  return item;
}

//peek at the front node in the list and return the value from it without removing it from the queue()
template <class T>
T linkedQueue<T>::peekQueue() const{
  if (isQueueEmpty()) {
    cout << "Error, queue is empty." << endl;
    return {};
  }
  return front->info;
}

//return the number of items in the queue
template <class T>
int linkedQueue<T>::queueCount() const{
  return count;
}

//deep copy the passed in linked queue, delete the current queue
//first if it is not empty
template <class T>
void linkedQueue<T>::copyQueue(const linkedQueue<T>& list1){
  if (front != nullptr) {
    deleteQueue();
  }

  nodeType<T> *temp;
  nodeType<T> *inList;
  inList = list1.front;

  //copy the first node and set first appropriately
  nodeType<T> *newNode;
  newNode = new nodeType<T>;
  newNode->info = inList->info;
  newNode->next = nullptr;
  front = newNode;
  temp = newNode;

  inList = inList->next;
  while (inList != nullptr) {
    newNode = new nodeType<T>;
    newNode->info = inList->info;
    temp->next = newNode;
    inList = inList->next;
    temp = temp->next;
  }

  temp->next = nullptr;
  back = temp;
}
