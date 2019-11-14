#include <iostream>
#include <string>
#include <fstream>
#include "ArbitMath.hpp"


using namespace std;

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
    outfile.open("output.num");


    
    infile >> problems;
    outfile << problems;

    while(problems > 0)
    {   int num;
        infile >> operation >> one >> two;
        for(int i = 0; i < one.length(); i++){
            num = one.at(i)-48;
            cout << num;
            A->EndSert(num);
        }
        for(int i = 0; i < two.length(); i++){
            num = two[i]-48;
            cout << num;
            B->EndSert(num);
        }
        if(operation == '+'){
            Sol->Add(A, B);
            Sol->print();
            
        }  
        else if(operation == '-'){
            Sol->Sub(A, B);
            Sol->print();
        }
        else if(operation == '*'){
            Sol->Mul(A, B);
            Sol->print();
        }
        problems--; 

    } 
    return 0;
}
