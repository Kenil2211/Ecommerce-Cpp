#include<iostream>
#include<fstream>

using namespace std;

class Employee {
   public:
      string name;
      long Employee_ID;
      int Salary;
} ;

int main()
{
    Employee Emp_1;
    Emp_1.name="Jhonson";
    Emp_1.Employee_ID=212020;
    Emp_1.Salary=11000;

    ofstream f1;
    f1.open("employee.txt",ios::app);

    f1.write((char*)&Emp_1,sizeof(Employee));
    f1.close();

    ifstream f2;
    f2.open("employee.txt",ios::in);
    f2.read((char *)&Emp_1,sizeof(Employee));
    
    cout<<Emp_1.name;
    cout<<Emp_1.Employee_ID;
    cout<<Emp_1.Salary;
    return 0;
}