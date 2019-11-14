#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//creates Node
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
    private:
    Node* Head;
    Node* Tail;

    public:
    //constructor sets Head and Tail to NULL
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
    //prints lists
    void print(){
        Node* Temp = Head;

        while(Temp){
            outfile<<Temp->data;
            Temp = Temp->Next;
        }
        cout<<endl;
    }
    //Empties the List for reuse
    void EmptyList(){
        while(Head != NULL){
            Node* Temp = Head;
            Head = Head->Next;
            delete Temp;
        }
    }
    //adds strings
    void Add(ArbitMath* A, ArbitMath* B){
        //carry and sum are updated in the loop
        int carry = 0, sum;
        //pointers to copy the original lists
        ArbitMath* val1 = new ArbitMath(*A);
        ArbitMath* val2 = new ArbitMath(*B);
        
        while (val1->Tail != NULL || val2->Tail != NULL) { 
            if (val1->Tail != NULL && val2->Tail != NULL) {
                //sum is mod 10 to get single digit
                sum = ((val1->Tail->data) + (val2->Tail->data) + carry) % 10; 
                //carry is div. 10 to get digit in the tens column
                carry = ((val1->Tail->data) + (val2->Tail->data) + carry) / 10;
                //Updates both list Tails
                val1->Tail = val1->Tail->Prev; 
                val2->Tail = val2->Tail->Prev; 
            } 
            else if (val1->Tail == NULL && val2->Tail != NULL) { 
                //sum and carry only use val2 because val1 == NULL
                sum = ((val2->Tail->data) + carry) % 10; 
                carry = ((val2->Tail->data) + carry) / 10; 
                //only updates val2
                val2->Tail = val2->Tail->Prev; 
            } 
            else if (val1->Tail != NULL && val2->Tail == NULL) { 
                //same as last if else for val1
                sum = ((val1->Tail->data) + carry) % 10; 
                carry = ((val1->Tail->data) + carry) / 10; 
                val1->Tail = val1->Tail->Prev; 
            } 
          
            // Inserting the sum digit 
            FrontSert(sum); 
        }
        //inserts the last carry
        if (carry != 0){ 
            FrontSert(carry); 
        } 
    }
    //subtracts strings
    void Sub(ArbitMath* A, ArbitMath* B){
        ArbitMath* val1 = new ArbitMath(*A);
        ArbitMath* val2 = new ArbitMath(*B);
        int borrow = 0, Diff;

        while(val1->Tail != NULL || val2->Tail !=NULL){
            if(val1->Tail != NULL && val2->Tail != NULL){
                //checks if you need to borrow
                if((val1->Tail->data) + borrow >= (val2->Tail->data)){
                    Diff = ((val1->Tail->data) + borrow - (val2->Tail->data));
            
                }
                //executes here if you need to borrow
                else{
                    Diff = ((val1->Tail->data) + borrow + 10 - (val2->Tail->data));
                    //borrow is set to negative 1 to subtract from next node
                    borrow = -1;
                }
                //updates tail pointers
                val1->Tail = val1->Tail->Prev;
                val2->Tail = val2->Tail->Prev;
            }
            //only one "if else" because we're assuming the larger number is on top
            else if(val1->Tail != NULL && val2->Tail == NULL){
                if(val1->Tail->data >=1){
                    Diff = ((val1->Tail->data) + borrow);
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
                //updates Tail pointer for Val1
                val1->Tail = val1->Tail->Prev;
            }
            //inserts Diff in the front of the list
            
            FrontSert(Diff);
        }
        
    }
    //multiplies strings
    void Mul(ArbitMath* A, ArbitMath* B){
        int zeros = 0;

        while(B->Tail != NULL){
            int carry = 0, p;
            ArbitMath* Val = new ArbitMath(*A);
            ArbitMath* Product = new ArbitMath();
            while(Val->Tail != NULL){
                //multipies all of list A by each node of list B and uses the add function to 
                //move through nodes in B and update the Product
                p = ((Val->Tail->data) * (B->Tail->data) + carry) % 10;
                carry = ((Val->Tail->data) * (B->Tail->data) + carry) / 10;
                //frontserts P to Product
                Product->FrontSert(p);
                //updates Val Tail
                Val->Tail = Val->Tail->Prev;
            }
            //frontserts carry if there is one
            if(carry != 0){
                Product->FrontSert(carry);
            }
            //adds zeros to the end of the list for addition 
            for(int i = 0; i < zeros; i++){
                Product->EndSert(0);
            }
            //adds products through each iteration of the loop
            Add(this, Product);
            //updates zeros per iteration
            zeros++;
            //updates B pointer 
            B->Tail = B->Tail->Prev;
            //resets product
            Product->Head = Product->Tail = NULL;

        }

    }
};
