#include<iostream>
#include<fstream>
#include<direct.h>
#include<ctime>
#include<string>
#include"First.hpp"

using namespace std;

// -----------------------------ADMIN--------------------------------------
int pid=0;
void setId();
void Admin::add_Product()
{
    string str;
    setId();
    pid=pid+1;
    ofstream f1;
    f1.open("allProducts.txt",ios::app);
    f1<<endl;
    f1<<pid<<endl;
    fflush(stdin);
    cout<<"\nProduct name : ";
    getline(cin,str);
    f1<<str<<endl;
    cout<<"\nProduct Price : ";
    getline(cin,str);
    f1<<str<<endl;
    cout<<"\nEnter Product Description : ";
    getline(cin,str);
    f1<<str;
    f1.close();
}

void setId()
{
    string str;
    fstream f1;
    f1.open("allProducts.txt",ios::in);
    cout<<"Read File";
    while(!f1.eof())
    {
        // pid++;
        getline(f1,str);
        pid=stoi(str);
        getline(f1,str);
        getline(f1,str);
        getline(f1,str);
    }
    f1.close();
}

void listOfId()
{
    string str;
    fstream f1;
    f1.open("allProducts.txt",ios::in);
    cout<<"Id\tProduct Name\n";
    cout<<"-----------------------------------\n";
    while(!f1.eof())
    {
        getline(f1,str);
        cout<<str<<"\t";
        getline(f1,str);
        cout<<str<<endl;
        getline(f1,str);
        getline(f1,str);
    }
    f1.close();
    
}

bool idIsPresent(string id)
{
    string str;
    ifstream f1;
    f1.open("allProducts.txt",ios::in);

    while(!f1.eof())
    {
        getline(f1,str);
        if(str == id)
        {
            return true;
        }
    }
    return false;
}

void removeFromFile(string id)
{
    string str;
    ifstream f1;
    f1.open("allProducts.txt",ios::in);
    ofstream f2;
    f2.open("example.txt",ios::app);
    while (!f1.eof())
    {
        getline(f1,str);
        if(str == id)
        {
            getline(f1,str);
            getline(f1,str);
            getline(f1,str);
        }
        else
        {
            f2<<str<<endl;
        }
    }

    f2.close();
    f1.close();
    
    remove("allProducts.txt");
    rename("example.txt","allProducts.txt");
}

void Admin::removeProduct()
{
    string id;
    listOfId();
    cout<<"\nEnter id of product you want to delete : ";
    cin>>id;
    
    if( idIsPresent(id) )
    {
        cout<<"\nId found!!";
        removeFromFile(id);
        cout<<"\nProduct Removed!!";
    }
    else
    {
        cout<<"\nProduct not Found with entered Id!!";
    }
}



// -----------------------------USER-----------------------------------------

string getCurrentUser()
{   
    string str;
    ifstream f1;
    f1.open("Files/loginCurrent.txt");
    while(!f1.eof())
    {
        getline(f1,str);
    }
    return str;
}

void userSignUp()
{
    ofstream f1,fc,fuser1;
    ifstream fuser;
    int flag=0;
    string filename,foldername;
    string curr_user,str;
    string fname,lname,phno,address,uname,pass,cpass;
    fuser.open("Files/User/Usernames.txt",ios::in);
    fuser1.open("Files/User/Usernames.txt",ios::app);
    fflush(stdin);
    cout<<"\nEnter First name : ";
    cin>>fname;
    fflush(stdin);
    cout<<"\nEnter Last name : ";
    cin>>lname;
    fflush(stdin);
    cout<<"\nEnter your contact no : ";
    cin>>phno;
    fflush(stdin);
    cout<<"\nEnter your address : ";
    getline(cin,address);
    fflush(stdin);
    start1:
    cout<<"\nEnter username : ";
    cin>>uname;

    while(!fuser.eof())
    {
        getline(fuser,str);
        if(uname == str)
        {
            cout<<"\nUsername Already Taken!!\n\n";
            goto start1;
        }
    }

    fflush(stdin);
    start:
    cout<<"\nEnter Password : ";
    cin>>pass;
    fflush(stdin);
    cout<<"\nConfirm Password : ";
    cin>>cpass;
    if(cpass == pass)
    {
        flag=1;
        cout<<"\nAccount Created Successfully..";

        fuser1<<uname<<endl;

        //create a folder of that customer
        foldername="Files/User/Personal-Info/"+uname+"_Data";
        const char* foldername1=foldername.c_str();
        mkdir(foldername1);

        //create a file 
        filename=foldername+"/"+"Info_"+uname+".txt";

        f1.open(filename,ios::app);
        fc.open("customer.txt",ios::app);
        
        f1<<"fname-->"<<fname<<endl;
        f1<<"lname-->"<<lname<<endl;
        f1<<"phone number-->"<<phno<<endl;
        f1<<"Address-->"<<address<<endl;
        f1<<"username-->"<<uname<<endl;
        f1<<"password-->"<<pass<<endl;

        fc<<"\n"<<uname<<endl;
        fc<<pass;

        fc.close();
        f1.close();
        fuser.close();
        fuser1.close();
    }
    else
    {
        cout<<"\nPlease Enter Password Again!!";
        goto start;
    }
}

void userLogIn()
{
    ofstream f2;
    ifstream f1,fcart;
    int flag=0,ch;
    string uname,pass,str,str1;
    start:
    cout<<"\n\n-------------------LOGIN---------------------";
    cout<<"\nEnter User name : ";
    cin>>uname;
    cout<<"\nEnter Password : ";
    cin>>pass;
    f1.open("customer.txt",ios::in);
    while(!f1.eof())
    {
        getline(f1,str);
        getline(f1,str1);
        if(str == uname && str1==pass)
        {
            flag=1;
            cout<<"\nLogin Successsfull";

            //create current login file
            f2.open("Files/loginCurrent.txt");
            f2<<uname;
            
            f2.close();
            break;
        }
    }
    
    if(!flag)
    {
        cout<<"\nUsername/Password Incorrect!!";
        f1.close();
        cout<<"\n\nDo you wish to login or Sign up First!!";
        cout<<"\n1-->Login\n2-->Sign Up\nEnter : ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                goto start;
            break;
            case 2:
                userSignUp();
            break;
            default:
                cout<<"\nInvalid Choice..";
        }

    }
}

void User::display_All_Products()
{
    string str;
    ifstream f1;
    f1.open("allProducts.txt",ios::in);
    cout<<"Id\tName\t\t\t\tPrice\n";
    cout<<"------------------------------------------------------------\n";
    while(!f1.eof())
    {
        getline(f1,str);
        cout<<str<<"\t";
        getline(f1,str);
        cout<<str<<"\t\t\t";
        getline(f1,str);
        cout<<"Rs."<<str<<"\n";
        getline(f1,str);
    }
    f1.close();
}

void User::specific_Product()
{
    string str;
    ifstream f1;
    f1.open("allProducts.txt",ios::in);
    listOfId();
    string id;
    cout<<"\nEnter id of product you want to View : ";
    cin>>id;
    
    if( idIsPresent(id) )
    {

        while(!f1.eof())
        {
            getline(f1,str);
            if(str == id)
            {
                cout<<"\nProduct id : "<<id;
                getline(f1,str);
                cout<<"\nProduct Name : "<<str;
                getline(f1,str);
                cout<<"\nProduct Price : Rs. "<<str;
                getline(f1,str);
                cout<<"\nAbout the Product : "<<str;
                break;
            }
        }
    }
    else
    {
        cout<<"\nProduct not Found with entered Id!!";
    }
}

void User::add_to_cart()
{   
    string tid;
    int flag=0,p_atc=0;
    string cartFilename,str;
    ofstream f1;
    ifstream f2,f3;

    f2.open("Files/loginCurrent.txt",ios::in);
    while (!f2.eof())
    {
        getline(f2,str);
    }
    f2.close();
    str = str + "_Data/";
    cartFilename="Files/User/Personal-Info/"+str+"Cart.txt";
    f1.open(cartFilename,ios::app);
    
    cout<<"\n";
    listOfId();
    cout<<"\nEnter id of product which you want to add to cart : ";
    cin>>tid;

    //check for, if product already added to cart..
    f3.open(cartFilename,ios::in);
    while(!f3.eof())
    {
        getline(f3,str);
        if(tid == str)
        {
            cout<<"\nProduct Already Added to Cart..";
            p_atc=1;
            f3.close();
            break;
        }
    }

    if(!p_atc)
    {
        f2.open("allProducts.txt",ios::in);
        while(!f2.eof())
        {
            getline(f2,str);
            if(str == tid)
            {
                flag=1;
                f1<<str<<endl;
                getline(f2,str);
                f1<<str<<endl;
                getline(f2,str);
                f1<<str<<endl;
                getline(f2,str);
                f1<<str<<endl;
                f2.close();
                f1.close();
                cout<<"\nProduct Added to cart..";
                break;
            }
        }
        if(!flag)
        {
            cout<<"\nEntered Id matched with no product!!";
        }
    }
}

void viewCart()
{
    cout<<"\n\n---------------------CART-------------------------------\n";
    ifstream f2,f1;
    string str,cartF;
    f2.open("Files/loginCurrent.txt",ios::in);
    while (!f2.eof())
    {
        getline(f2,str);
    }
    f2.close();
    str=str+"_Data/";
    cartF="Files/User/Personal-Info/"+str+"Cart.txt";
    f1.open(cartF,ios::in);
    if(f1)
    {
        while(!f1.eof())
        {
            getline(f1,str);
            cout<<str<<"\n";
        }
        f1.close();
    }
    else
    {
        cout<<"\nYour Cart is empty\nPlease Add products to your cart!!";
    }
}

void User::placeOrder()
{
    viewCart();
    string id,str,orderFile;
    int p_o=0;
    ofstream f1;
    ifstream f2,f3;
    orderFile=getCurrentUser();
    orderFile=orderFile+"_Data/";
    start:
    f2.open("Files/User/Personal-Info/"+orderFile+"Cart.txt",ios::in);
    if(f2)
    {
        orderFile="Files/User/Personal-Info/"+orderFile+"Orders.txt";
        f1.open(orderFile,ios::app);

        cout<<"\nEnter Id of product you want to place order : ";
        cin>>id;

        f3.open(orderFile,ios::in);
        // str1=str1+id;
        while(!f3.eof())
        {
            getline(f3,str);
            if(str == id)
            {
                cout<<"\nProduct Already Ordered..";
                p_o=1;
                f3.close();
                break;
            }
        }
        if(!p_o)
    {
        while(!f2.eof())
        {
            getline(f2,str);
            if(id == str)
            {
                f1<<str<<endl;
                getline(f2,str);
                f1<<"Product Name : "<<str<<endl;
                getline(f2,str);
                f1<<"Product Price : Rs. "<<str<<endl;
                f2.close();
                f1.close();
                cout<<"\nOrdered!!";
                p_o=1;
                break;
            }
        }
        if(!p_o)
        cout<<"\nProduct not Found in Cart!!";
    }
    }
}

void User::orderDetails()
{
    string str,str1;
    int total=0;
    ifstream f1,f2;
    
    cout<<"\n\n----------------ORDER DETAILS------------------\n";
    str=getCurrentUser();
    str=str+"_Data/";
    str="Files/User/Personal-Info/"+str+"Orders.txt";
    f1.open(str,ios::in);
    if(!f1.tellg())
    {
        while(!f1.eof())
        {
            f2.open("allProducts.txt",ios::in);
            getline(f1,str);
            getline(f1,str);
            cout<<str<<endl;
            getline(f1,str);
            cout<<str<<endl;
        }
        f1.close();
    }
    else
    {
        cout<<"\nNo Order Placed by you!!";
    }
}

void orderHistoryFile()
{
    ifstream f1;
    ofstream f2;
    string curr_user,str,nfname;

    curr_user=getCurrentUser()+"_Data/";

    f1.open("Files/User/Personal-Info/"+curr_user+"Orders.txt",ios::in);
    nfname="Files/User/Personal-Info/"+curr_user+"OrderHistory.txt";
    f2.open(nfname,ios::app);
        
    
        //Get local Date/Time

        time_t now = time(0);
        // convert to string form
        char* dt = ctime(&now);


        f2<<"Order Date and Time : "<<dt<<endl;
        while(!f1.eof())
        {
            getline(f1,str);
            f2<<str<<endl;
        }
        f2.close();
        f1.close();
}

void User::checkout()
{
    ifstream f1,f2;
    string curr_user,str,str1;
    long total=0,tonum;
    curr_user=getCurrentUser();
    curr_user+="_Data/";
    curr_user="Files/User/Personal-Info/"+curr_user+"Orders.txt";
    f1.open(curr_user,ios::in);
    if(!f1.tellg())
    {
        cout<<"\n\n------------------Order Summary------------------\n";
        orderDetails();
       while(!f1.eof())
        {
            f2.open("allProducts.txt",ios::in);
            getline(f1,str);
            while(!f2.eof())
            {
                getline(f2,str1);
                if(str1 == str)
                {
                    getline(f2,str1);
                    getline(f2,str1);
                    tonum=stol(str1);
                    total=total+tonum;
                    f2.close();
                    break;
                }
            }
            getline(f1,str);
            getline(f1,str);      
        }
        f1.close();
        cout<<"\nTotal amt to be paid : Rs. "<<total;
        cout<<"\n\nThank You for shopping with us!!\n\tVISIT AGAIN!!!";
        
        //write to order history
        orderHistoryFile();

        //clear order file
        const char* fname=curr_user.c_str();
        remove(fname);
    }
    else
    {
        cout<<"\n\nOrder needs to be Placed before final checkout!!";
    }
}

void User::orderHistory()
{
    ifstream f1;
    string user,fname,str;
    user=getCurrentUser()+"_Data/";
    fname="Files/User/Personal-Info/"+user+"OrderHistory.txt";
    f1.open(fname,ios::in);
    if(f1)
    {
        cout<<"\n------------------Order History----------------------\n";
        while(!f1.eof())
        {
            getline(f1,str);
            cout<<str<<endl;
        }
        f1.close();
    }
    else
    {
        cout<<"\n---------------------------------------------";
        cout<<"\nNo Order Placed Yet!!\nOrder Something Fast!!";
        cout<<"\n---------------------------------------------";
    }
}

// -----------------------------MAIN SECTION----------------------------------
int main()
{
    User u;
    Admin a;

    int ch,ch1;
    Mainmenu:
    cout<<"\n0-->Exit\n1-->Admin\n2-->User";
    cout<<"\nEnter : ";
    cin>>ch;
    switch(ch)
    {
        case 0:
            exit(0);
        case 1:
            //while for admin..
            while(1)
            {
                cout<<"\n0-->Go to Main menu\n1-->add\n2-->Remove\nEnter : ";
                cin>>ch;
                switch(ch)
                {
                    case 0:     
                        goto Mainmenu;
                    break;
                    case 1:
                        a.add_Product();
                    break;
                    case 2:
                        a.removeProduct();
                    break;
                    default:
                        cout<<"\nInvalid Choice!!";
                }
            }
            //End of while for admin..

        break;
        case 2:
            while(1)
            {
                cout<<"\n0-->Go to Main Menu\n1-->LogIn\n2-->SignUp\nEnter : ";
                cin>>ch1;
                switch (ch1)
                {
                    case 0:
                        goto Mainmenu;
                    break;

                    case 1:
                        login:
                        userLogIn();

                        //Menu: 
                        //While for User
                        while (1)
                        {
                            cout<<"\n\n0-->Exit\n1-->Display all Products\n2-->Display specific Product";
                            cout<<"\n3-->Add to Cart\n4-->Display Cart\n5-->Place Order";
                            cout<<"\n6-->Order Details\n7-->Proceed to Checkout\n8-->My Order History";
                            cout<<"\nEnter : ";
                            cin>>ch;
                            switch (ch)
                            {
                                case 0:
                                    exit(0);
                                case 1:
                                    u.display_All_Products();
                                break;
                                case 2:
                                    u.specific_Product();
                                break;
                                case 3:
                                    u.add_to_cart();
                                break;
                                case 4:
                                    viewCart();
                                break;
                                case 5:
                                    u.placeOrder();
                                break;
                                case 6:
                                    u.orderDetails();
                                break;
                                case 7:
                                    u.checkout();
                                break;
                                case 8:
                                    u.orderHistory();
                                break;
                                default:
                                    cout<<"\nInvalid choice...";
                                    break;
                            }
                        }
                        //End of While for User

                    break;

                    case 2:
                        userSignUp();
                        goto login;

                    break;

                    default:
                        cout<<"Invalid choice!!!";
                }
            }
            
        break;
        default:
            cout<<"\nInvalid Choice..";

    }
}