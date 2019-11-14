#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//node struct to hold data
struct Node{
    int data;
    Node* Prev;
    Node* Next;

    Node(int d){
        data = d;
        Prev = Next = NULL;
    } 
};

class ArbitMath{


  public:
  Node* Head;
  Node* Tail;

  ArbitMath(){
      Head = Tail = NULL;
  }
  //inserts at end
  void EndSert(int d){
      Node* Temp = new Node(d);
      if(!Head){
          Head = Temp;
          Tail = Temp;
      }
      else{
      Tail->Next = Temp;
      Temp->Prev = Tail;
      Tail = Temp;
      }
  }
  //inserts in front
  void FrontSert(int d){
      Node* Temp = new Node(d);
      if(!Head){
          Head = Temp;
          Tail = Temp;
      }
      else{
      Head->Prev = Temp;
      Temp->Next = Head;
      Head = Temp;
      }
  }

//method to empty list for reuse
  void EmptyList(){
    while(Head != NULL){
      Node* Temp = Head;
      Head = Head->Next;
      delete Temp;
    }
  }


  //adds strings
  void Add(ArbitMath* A, ArbitMath* B){
      
    ArbitMath* val1 = new ArbitMath(*A); 
    ArbitMath* val2 = new ArbitMath(*B); 
    int carry = 0, sum; 
    //for use when you pass to add in the Mul function
    this->Head = NULL;
    this->Tail = NULL;
    
    while (val1->Tail != NULL || val2->Tail != NULL) { 
        if (val1->Tail != NULL && val2->Tail != NULL) { 
            sum = ((val1->Tail->data) + (val2->Tail->data) + carry) % 10; 
            carry = ((val1->Tail->data) + (val2->Tail->data) + carry) / 10; 
            val1->Tail = val1->Tail->Prev; 
            val2->Tail = val2->Tail->Prev; 
        } 
        else if (val1->Tail == NULL && val2->Tail != NULL) { 
            sum = ((val2->Tail->data) + carry) % 10; 
            carry = ((val2->Tail->data) + carry) / 10; 
            val2->Tail = val2->Tail->Prev; 
        } 
        else if (val1->Tail != NULL && val2->Tail == NULL) { 
            sum = ((val1->Tail->data) + carry) % 10; 
            carry = ((val1->Tail->data) + carry) / 10; 
            val1->Tail = val1->Tail->Prev; 
        } 
        else{
          val1->Tail = val1->Tail->Prev;
          val2->Tail = val2->Tail->Prev;
        }
          
        // Inserting the sum digit 
        FrontSert(sum); 
    } 
      
    // Inserting last carry 
    if (carry != 0) 
        FrontSert(carry); 
  }
  //subtracts strings
  void Sub(ArbitMath* A, ArbitMath* B){
      ArbitMath* val1 = new ArbitMath(*A);
      ArbitMath* val2 = new ArbitMath(*B);
      int borrow = 0, Diff;

      while(val1->Tail != NULL || val2->Tail !=NULL){
          if(val1->Tail != NULL && val2->Tail != NULL){
              if((val1->Tail->data) + borrow >= (val2->Tail->data)){
                  Diff = ((val1->Tail->data) + borrow - (val2->Tail->data));
                  borrow = 0;
              }
              else{
                  Diff = ((val1->Tail->data) + borrow + 10 - (val2->Tail->data));
                  borrow = -1;
              }
              val1->Tail = val1->Tail->Prev;
              val2->Tail = val2->Tail->Prev;
          }
          else if(val1->Tail != NULL && val2->Tail == NULL){
              if(val1->Tail->data >=1){
                  Diff =((val1->Tail->data) + borrow);
                  borrow = 0;
              }
              else{
                  if(borrow != 0){
                      Diff = ((val1->Tail->data) + 10 + borrow);
                      borrow = -1;
                  }
                  else{
                      Diff = val1->Tail->data;
                  }
              }
              val1->Tail = val1->Tail->Prev;
          }
          FrontSert(Diff);
      }
      
  }
  //multiplies strings
  void Mul(ArbitMath* A, ArbitMath* B){
    int zeros = 0;

    while(B->Tail != NULL){
        int carry = 0, p = 0;
        ArbitMath* val = new ArbitMath(*A);
        ArbitMath* Product = new ArbitMath();
        while(val->Tail != NULL){
          p = ((val->Tail->data) * (B->Tail->data) + carry) % 10;
          carry = ((val->Tail->data) * (B->Tail->data) + carry) / 10;
          Product->FrontSert(p);
          val->Tail = val->Tail->Prev; 
        }
        if(carry != 0){
            Product->FrontSert(carry);
        }
      
        for(int i = 0; i < zeros; i++){
            Product->EndSert(0);
        }
        Add(this, Product);
        zeros++;
        B->Tail = B->Tail->Prev;
        Product->Head = Product->Tail = NULL;

      }

  }
};

int main(){
    int problems;
    string one, two;
    char operation;

    ArbitMath* A = new ArbitMath();
    ArbitMath* B = new ArbitMath();
    ArbitMath* Sol = new ArbitMath();

    ifstream infile;
    infile.open("input.txt");
    ofstream outfile;
    outfile.open("output.txt");

    infile >> problems;
    for(int count = 0; count < problems; count++){
      int num;
      infile >> operation >> one >> two;
      for(int i = 0; i < one.length(); i++){
          num = one[i]-48;
          A->EndSert(num);
      }
      for(int i = 0; i < two.length(); i++){
          num = two[i]-48;
          B->EndSert(num);
      }

      if(operation == '+'){
        Sol->Add(A, B);
        outfile << "Sum: ";
        //Sol->print();
          
      }  
      else if(operation == '-'){
          Sol->Sub(A, B);
          outfile << "Difference: ";
          //Sol->print();
      }
      else if(operation == '*'){
          Sol->Mul(A, B);
          outfile << "Product: ";
          //Sol->print();
      }
      //prints lists here so we can print ot a file

      Node* Temp = Sol->Head;
    
      while(Temp != NULL){
          outfile<<Temp->data;
          Temp = Temp->Next;
      }
      outfile<<endl;
        
      //empties each list for reuse in the loop
      A->EmptyList();
      B->EmptyList();
      Sol->EmptyList();

    } 
 return 0;
}
