/**
 * Lecture 08
 * 
 * List based queue 
 * 
 * Author: Terry Griffin
 * Date: Oct 4th ish 2019
 */
#include <iostream>
#include <fstream>
#include "ListQueue.hpp"

using namespace std;


int main() {
  ListQueue LQ;                 // Queue instance 

  
  // While still animals in the file
    while (!fin.eof()) {
        a = new Animal();                         // allocate memory for an animal
        fin >> a->name >> a->weight >> a->scary;  // load animal with file data
        LQ.Push(a);                               // push animal onto the stack
    }

  cout<<endl;                     // ummmm 

  LQ.Print();                     // print queue to see where values are


  for(int i=0;i<5;i++){           // remove 5 items
    if(!LQ.Empty()){
      int t = LQ.Pop();
      cout<<"Item: "<<t<<endl;    // print out items
    }else{
      cout<<"Empty queue!"<<endl;
    }

  }

  LQ.Print();                     // print again to show front removal
  LQ.PrintPointers();

  Node* f = LQ.GetFront();        // We added this in class JUST to see what front
  cout<<f->data<<endl;            // pointed to.
}
