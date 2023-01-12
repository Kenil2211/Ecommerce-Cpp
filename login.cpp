#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

int id=0;
void writeToFile(string n,string p)
{
    string str;
    int cnt=0;
    ofstream f1;
    f1.open("customer.txt",ios::app);
    while(!f1.eof())
    {
        getline(cin,str);
        cnt++;
    }
    cout<<cnt;
    f1<<id<<endl;
    f1<<n<<endl;
    f1<<p<<endl;
    f1.close();
}

// void Account::readFile()
// {
    
// }
class Account
{
    string uname,upass,c_upass;
    public:
    void getdata();
    void readFile();
    
};

void Account::getdata()
{
    int ch;
    while(1)
    {
        cout<<"\nEnter uname : ";
        cin>>uname;
        start:
        cout<<"\nEnter Password : ";
        cin>>upass;
        cout<<"\nConfirm Password : ";
        cin>>c_upass;
        if(upass == c_upass)
        {
            id++;
            cout<<"\nAccount Created Successfully.."<<id;
            writeToFile(uname,upass);
            cout<<"\n0--> exit";
            cin>>ch;
            if(!ch)
                break;
        }
        else
        {
            cout<<"\nConfirm Password correctly..";
            goto start;
        }
    }
}




int main()
{
    Account obj;
    obj.getdata();
}