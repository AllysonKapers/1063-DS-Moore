/**
 * ListQueue.hpp
 * 
 * List Based Queue definition and implementation.
 * Author: Terry Griffin
 * Date: Oct 2019
 */
#include <iostream>


using namespace std;

//creates animal type for use in Queue, with overloaded constructor from HW3
struct Animal {
    string name;
    double weight;
    double scary;

    // Default constructor
    Animal() {
        name = "";
        weight = 0.0;
        scary = 99.0;
    }

    // Added overloaded constructor
    Animal(string n, double w, double s){
        name = n;
        weight = w;
        scary = s;
        
    }

};



//separate node type
struct Node {
    Animal *A;
    Node *Next;

    // Needs a default constructor

    Node(Animal *a) {
        A = a;
        Next = NULL;
    }
};





/**
 * List Queue
 * 
 * List Based Queue
 * 
 */
class ListQueue{
private:
  Node* Front;            // front of the queue (where we remove from)
  Node* Rear;             // rear of the queue (where we add to)
public:
  ListQueue();            // construct
  void Push(Animal);         // add animal to rear
  int Pop();              // remove from front
  void Print();           // print for debugging
  bool Empty();           // is queue empty (can't remove from empty queue)
  void PrintPointers();   // added for lecture purposes
  Node* GetFront();       // added for lecture purposes
};


/**
 * ListQueue
 * Purpose:
 *     Constructs our queue
 * Params:
 *     void
 * Returns:
 *     void
 */
ListQueue::ListQueue(){
  Front = Rear = NULL;
}

/**
 * Push
 * Purpose:
 *     Adds item to rear of queue
 * Params:
 *     Animal val : animal to be added
 * Returns:
 *     void
 */
void ListQueue::Push(Animal val){
  Node* temp = new Node(val);     // allocate new memory

  if(Front == NULL){              // if list is empty
    Front = Rear = temp;          // point everyone to it
  }else{
    Rear->Next = temp;            // otherwise link last node to new one
    Rear = temp;                  // then point Rear to it.
  }

}

/**
 * Pop
 * Purpose:
 *     Removes item from front of queue
 * Params:
 *     void
 * Returns:
 *     int : front item
 */
int ListQueue::Pop(){
  int temp = Front->data;     // get front data temporarily
  Node* T = Front;            // Point to the front temporarily
  Front = Front->Next;        // Move front to next item 
  delete T;                   // Now we can delete the old front

  if(!Front){                 // If front is NULL make rear NULL as well
    Rear = NULL;              // because if front is NULL list is empty!  
  }

  return temp;                // return front integer
}

/**
 * Print
 * Purpose:
 *     Prints items in queue for debugging
 * Params:
 *     void
 * Returns:
 *     void
 */
void ListQueue::Print(){
  Node* temp = Front;

  while(temp){
    cout<<temp->data;
    if(temp->Next){
      cout<<"->";
    }
    temp = temp->Next;
  }
  cout<<endl;
}

/**
 * Empty
 * Purpose:
 *     Checks for empty queue. Cant remove from empty queue!
 * Params:
 *     void
 * Returns:
 *     bool: true == empty 
 */
bool ListQueue::Empty(){
  return Front == NULL;
}

/**
 * PrintPointers
 * Purpose:
 *     Prints front and rear values for lecture purposes
 * Params:
 *     void
 * Returns:
 *     void
 */
void ListQueue::PrintPointers(){
  cout<<"Front = "<<Front<<endl;
  cout<<"Rear = "<<Rear<<endl;
}


/**
 * GetFront
 * Purpose:
 *     Returns the front node, for lecture purposes
 * Params:
 *     void
 * Returns:
 *     void
 */
Node* ListQueue::GetFront(){
  return Front;
}
