#include <iostream>
#include <string>
#include <fstream>
#include "ArbitMath.hpp"


using namespace std;

int main(){
    //variables to hold input file information
    int problems;
    string one, two;
    char operation;
    //assigns ArbitMath pointers
    ArbitMath* A = new ArbitMath();
    ArbitMath* B = new ArbitMath();
    ArbitMath* Sol = new ArbitMath();
    //opens file for reading/printing
    ifstream infile;
    infile.open("input.txt");
    ofstream outfile;
    outfile.open("output.txt");


    
    infile >> problems;
    outfile << problems;

    for(int c = 0; c < problems; c++)
    {   int num;
        //reads a new problems into variables each loop iteration
        infile >> operation >> one >> two;
        //creates list for string one
        for(int i = 0; i < one.length(); i++){
            num = one.at(i)-48;
            A->EndSert(num);
        }
        //creates list for string two
        for(int i = 0; i < two.length(); i++){
            num = two[i]-48;
            B->EndSert(num);
        }
        //tests operation to determine which function to pass A and B to
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
        //resets lists
        A->EmptyList;
        B->EmptyList;
        Sol->EmptyList;

    } 

}
