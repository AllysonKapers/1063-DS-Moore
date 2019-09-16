#include <iostream>
#include <fstream>

using namespace std;


struct Employee{
    string emp_id; 
    string first_name;
    string last_name;
    string gender;
    string email;
    double hourly_pay;
    Employee *Next;
    
    
  

    Employee(){
        emp_id = "";
        first_name = "";
        last_name = "";
        gender = "";
        email = "";
        hourly_pay = 0.0;
    }

    Employee(string id,string first,string last,string sex,string mail, double pay){
        emp_id = id;
        first_name = first;
        last_name = last;
        gender = sex;
        email = mail;
        hourly_pay = pay;
    }
};

class LinkedList{
private:
    Employee* Head;
    Employee* Holder;//holder variable to use throughout program
  
    
    
    

public:
    
    LinkedList(){
        Head = NULL;
    }


    void frontSert(string id,string first,string last,string sex,string mail, double pay){
        Employee* Temp = new Employee(id,first,last,sex,mail,pay);

        if(Head == NULL){
            Head = Temp;
        }
        else{
            Temp->Next = Head;
            Head = Temp;
        }
        
    }


    void print(){
        Employee* Temp = Head;
        int count = 0;
        while(count<30)//edited to print only the first 30 nodes in list
        {
            cout<<Temp->emp_id<<", "<<Temp->first_name<<", "<<Temp->last_name<<", "<<Temp->email<<", "<<Temp->gender<<", "<<Temp->hourly_pay;
            if(Temp->Next){
                cout<<"->";
            }
            cout<< endl;
            Temp = Temp->Next;
            count++;
        }
    }
    void push(Employee* front){
      Employee* Temp = front;//points to the new head
      Temp->Next = Head; //points front to the head of the list
      Head = front;//reassigns head of list
    }
    void pop(){
      Employee* Temp = Head;//points to the first node
      Head = Head->Next;//points head to the second node in list
      delete Temp;//deletes first node
      }
    
    bool search(string x){
      Employee* Temp = Head; // Starts search at beginning of list
      
      int g = 0; // stays 0 if string is not found

      while(Temp != NULL)//runs through list
      {
        string s = Temp->email;
        
        
        if(s.find(x) != std::string::npos){
          cout<< s << endl; //prints email of matched string(s)
         
          g = 1; //because string was found

        }
      }
      if (g == 0){
        return false;
      }
      
      return true;
    }

    void del(string a){
      Employee* Temp = Head;
      if(search(a)== true){
        
        while(Temp != NULL)//runs through list
        {
          string s = Temp->email;
        
        
          if(s.find(a) != std::string::npos){
           break;//ends the loop once string is found, requires employees correct email
            

        }

        Holder = Temp;//holds value before Temp so you can relink the list
        Temp = Temp->Next;//increments the list
        
        
      }
      
      Holder->Next = Temp->Next;
      delete Temp; 
      cout << "Sucessfully deleted" << endl;
      }
      else{
        cout<< "There is no employee with that email";
      }
    }

};

int main(){

    LinkedList EmpList;

    string empid;
    string first;
    string last;
    string email;
    string gender;
    double pay;

    string line;
    string *tokens;
    ifstream fin("employees.dat");


    while(!fin.eof()){

        fin>>empid>>first>>last>>email>>gender>>pay;

        //cout<<empid<<", "<<first<<", "<<last<<", "<<email<<", "<<gender<<", "<<pay<<endl;

        EmpList.frontSert(empid,first,last,email,gender,pay);
    }
    
    EmpList.print();


    return 0;
}
