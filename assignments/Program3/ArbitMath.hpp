#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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
            cout<<Temp->data;
            Temp = Temp->Next;
        }
        cout<<endl;
    }

    void EmptyList(){
        while(Head != NULL){
            Node* Temp = Head;
            Head = Head->Next;
            delete Temp;
        }
    }
    //adds strings
    void Add(ArbitMath* A, ArbitMath* B){
        int carry = 0, sum;
        Node* Temp = NULL;
        ArbitMath* val1 = new ArbitMath(*A);
        ArbitMath* val2 = new ArbitMath(*B);
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
          
            // Inserting the sum digit 
            FrontSert(sum); 
        }
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
        int k=0;

        while(B->Tail != NULL){
            int carry = 0, p;
            ArbitMath* Temp = new ArbitMath(*A);
            ArbitMath* Product = new ArbitMath();
            while(Temp->Tail != NULL){
                p = ((Temp->Tail->data) * (B->Tail->data) + carry) % 10;
                carry = ((Temp->Tail->data) * (B->Tail->data) + carry) / 10;
                Product->FrontSert(p);
                Temp->Tail = Temp->Tail->Prev;
            }
            if(carry != 0){
                Product->FrontSert(carry);
            }
            for(int i = 0; i < k; i++){
                Product->EndSert(0);
            }
            Add(this, Product);
            k++;
            B->Tail = B->Tail->Prev;
            Product->Head = Product->Tail = NULL;

        }

    }
};
