# CPlusPlusHeaders
A collection of custom headers I have built for C++. Many of these are implemented elsewhere already but I wanted to test myself and create them from scratch.
Below I've included brief descriptions for each header and a quick outline of their UML in some cases.

*** linkedStack.h ***
This is a linked stack implementation complete with valid operator overloading and templates for use with any datatype, a quick sketch of the class UML can be found below

linkedStack<T>
  -nodeType<T> *stackTop
  -count: int
  +operator == (const linkedStack<T>&): bool
  +operator != (const linkedStack<T>&): bool
  +operator = (const linkedStack<T>&): linkedStack<T>
  +linkedStack()
  +linkedStack(const linkedStack<T>&)
  +~linkedStack()
  +deleteStack(): void
  +isStackEmpty() const: bool
  +push(const T&): void
  +peek() const: T
  +pop(): T
  +stackCount() const: int
  +stackSum() const: T
  -rSum(nodeType<T> *) const: T
  -copyStack(const linkedStack<T>&): void'
  


*** linkedQueue.h ***
This is a linked queue implementation complete with valid operator overloading and templates for use with any datatype, a quick sketch of the class UML can be found below

linkedQueue<T>
  -nodeType<T> *front
  -nodeType<T> *back
  -queMutex: mutex
  -count: int 
  +operator == (const linkedQueue<T>&): bool
  +operator != (const linkedQueue<T>&): bool
  +operator = (const linkedQueue<T>&): linkedQueue<T>
  +linkedQueue()
  +linkedQueue(const linkedQueue<T>)
  +~linkedQueue()
  +deleteQueue(): void
  +isQueueEmpty() const: bool
  +addQueue(const T&): void
  +remQueue(): T
  +peekQueue() const: T
  +queueCount() const: int
  -copyQueue(const linkedQueue<T>&): void
