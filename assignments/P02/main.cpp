/**
 * File: main.cpp
 * Aurhor: Allyson Moore
 * Course: CMPS 1063 - Fall 2019
 * Date: 10-8-19
 * Description:
 *    Main driver of an Array based implementation of a stack.
 */

#include <iostream>
#include <fstream>

using namespace std;


//Using a struct to input data because it's the only thing I got to work 
struct inData{
  char sign;
  int num;

  inData(){

    //initializes sign and num to default values
    sign = '-';
    num = 0;
  }


};
class Stack{
  private:
    int *A;         // container of items (could make it a list)
    int Top;        // keep track of top
    int Size;       // Arrays need a size
    int Max;        //holds the biggest size of the stack
                    //not the most full the stack was

  public:
  
    
    /**
     * Stack constructor
     * Description:
     *    Inits an array of ints and sets our top
     */
    Stack(){
      Size = 100;
      A = new int [Size];
      Top = -1;
      Max = Size;
    }

    
    /**
     * Stack constructor
     * Description:
     *    Inits an array of ints to a specified size and sets our top
     * Params:
     *    int s : integer size
     */
    Stack(int s){
      Size = s;
      A = new int [Size];
      Top = -1;
      Max = Size;
    }

    /**
     * Push
     * Description:
     *    Adds item to top of stack
     * Params:
     *    int val : integer size
     * Returns:
     *     bool : true = success
     */
    bool Push(int val){
      if(!full()){
        //makes sure the stack isn't full(it never should
        //be because of the enlarge function)
        if(TooSmall()){
          enlarge(); // calls enlarge function to resize
                     //if needed before adding to the
                     //stack 
        }
        Top++;
        A[Top] = val;
        return true;

      }
      else{
        return false;
      }
    }

    /**
     * Pop
     * Description:
     *    Removes top of stack and returns it
     * Params:
     *    void
     * Returns:
     *     int : item on stack
     */
    int Pop(){
      if(!empty()){
        if(TooBig()){
          reduce(); // calls reduce function to makes sure our stack isnt too large for the data
        }
        int temp = 0;   
        temp = A[Top];
        Top--;
        return temp;
      }

      return 0;
    }

    //makes sure that you dont try to pop from an empty stack
    bool empty(){

      return Top < 0;

    }
    //makes sure that you don't push to a full stack
    bool full(){

      return Top == (Size - 1);
    }

    /**
     * Print
     * Description:
     *    Prints stack for inspection
     * Params:
     *    void
     * Returns:
     *     void
     */
    void Print(ofstream& file){
      file << "Size: " << Size << endl;
      file << "Largest Size: " << Max << endl;
      file << "Values: ";
      for(int i = Top;i>=0 ; i--){
        file<<A[i]<< " ";
    }
}

    /**
    * Empty
    * Description:
    *    Is stack at 20%
    * Params:
    *    void
    * Returns:
    *    bool : true = TooBig
    */
    bool TooBig(){
      return Top <= (Size * 0.2);
    }   // Stack is at 20% capacity

    /**
     * Full
     * Description:
     *    Is stack at 80%
     * Params:
     *    void
     * Returns:
     *    bool : true = TooSmall
     */
    bool TooSmall(){
      return (Top >= (Size * 0.8));
    }


    //enlarges stack if it reaches 80%
    void enlarge(){
      int new_size = Size * 1.5;
      int *B = new int[new_size];
      
      for(int i = 0; i < Size; i++){
        B[i] = A[i];
      }
      //Keeps track of how big the stack gets
      if(Max < new_size){
          Max = new_size;
      }
      int* temp = A;
      A = B;
      Size = new_size;//Saves stack size
    
      delete [] temp;
    }
    //reduce stack if it gets to 20% full
    void reduce(){
      int new_size = Size * 0.5;
      int *B = new int[new_size];


      for(int j = 0; j < new_size; j++){
        B[j] = A[j];
      }
      
      //Saves Stack size
      Size = new_size;
      
      int *temp = A;  
      A = B;
      delete [] temp;
    }


};


int main() {


  //file starters
  ifstream infile;
  ofstream outfile;
  infile.open("input.txt");
  outfile.open("stack_out.dat");
  
  //makes use of our struck and stack 
  inData inData;
  Stack S1(10);
  
  while(!infile.eof()){
    //reads file into the struct
    infile >> inData.sign >> inData.num;
    
    if(inData.sign == '+'){
      S1.Push(inData.num); //uses Push function from stack
    }
    else if(inData.sign == '-'){
      S1.Pop(); //uses Pop function from Stack
    }
    //handles invalid char in inData
    else{
      cout << "ERROR " << inData.sign << " " << inData.num;
    }

  }
  //uses print function from Stack
  S1.Print(outfile);
};
