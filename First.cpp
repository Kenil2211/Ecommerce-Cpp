#include<iostream>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<vector>
#include "First.hpp"

using namespace std;

int cnt_pid=0,total=0,co_flag=0;
//----------------------ADMIN----------------------
class Product: public Admin
{
    public:
    
    int id=0,quantity,q_ord;
    float price;
    string description;
    string name;
    bool availability,ordered=false,atc=false;

};

vector<Product>p_list;
vector<Product>cart;
vector<Product>orderList;

void Admin::add_Product()
{   
    cnt_pid++;

    Product obj;
    cout<<"\n---------------Enter new Product Details---------------";
    cout<<"\nEnter Product name : ";
    cin>>obj.name;
    cout<<"\nEnter Product Description : ";
    cin>>obj.description;
    cout<<"\nEnter Product Price : ";
    cin>>obj.price;
    cout<<"\nEnter Product Quantity Available : ";
    cin>>obj.quantity;
        
    obj.availability=true;

    obj.id = cnt_pid;   

    p_list.push_back(obj);
}

//----------------------USER----------------------

void User::display_All_Products()
{
    system("CLS");

    cout<<"\n\t\t---------------Product List---------------\n\n";

    cout<<"Id\t\tName\t\tPrice\t\tQuantity\tDescription";

    for(Product x:p_list)
    {
        cout<<endl;
        cout<<x.id<<"\t\t"<<x.name<<"\t\t"<<x.price<<"\t\t"<<x.quantity<<"\t\t"<<x.description;
    }

    
}

void listOfid()
{
    cout<<"\nName\tId";
    for(Product info:p_list)
    {
        cout<<"\n"<<info.name<<"\t"<<info.id;
    }
}

void User::specific_Product()
{
    int temp_id,flag=0;
    listOfid();
    cout<<"\nEnter id of product to be displayed : ";
    cin>>temp_id;
    for(Product x:p_list)
    {
        if(x.id == temp_id)
        {
            flag=1;
            cout<<"\n\t\t---------------Product Info---------------\n\n";

            cout<<"Id\t\tName\t\tPrice\t\tQuantity\tDescription";
            cout<<endl;
            cout<<x.id<<"\t\t"<<x.name<<"\t\t"<<x.price<<"\t\t"<<x.quantity<<"\t\t"<<x.description;
            break;
        }
    }
    if(!flag)
    {
        cout<<"\nRecord not found...";
    }

}

void search(int tid)
{
    int flag=0;
    for(Product s:p_list)
    {
        if(s.id == tid)
        {
           flag=1;
            cout<<"\n\t\t---------------Product Info---------------\n\n";

            cout<<"Id\t\tName\t\tPrice\t\tQuantity\tDescription";
            cout<<endl;
            cout<<s.id<<"\t\t"<<s.name<<"\t\t"<<s.price<<"\t\t"<<s.quantity<<"\t\t"<<s.description;
            break; 
        }
    }
    if(!flag)
    {
        cout<<"\nRecord Not Found...";
    }
}
void search(string n)
{
    int flag=0;
    for(Product s:p_list)
    {
        if(s.name == n)
        {
           flag=1;
            cout<<"\n\t\t---------------Product Info---------------\n\n";

            cout<<"Id\t\tName\t\tPrice\t\tQuantity\tDescription";
            cout<<endl;
            cout<<s.id<<"\t\t"<<s.name<<"\t\t"<<s.price<<"\t\t"<<s.quantity<<"\t\t"<<s.description;
             
        }
    }
    if(!flag)
    {
        cout<<"\nRecord Not Found..";
    }
}
void search(string n,int p)
{
    int flag=0;
    cout<<"\n\t\t---------------Product Info---------------\n\n";
    cout<<"Id\t\tName\t\tPrice\t\tQuantity\tDescription";
                
    for(Product s:p_list)
    {
        if(s.price < p || s.name == n)
        {

            if(s.name == n )
            {
                flag=1;
                
                cout<<endl;
                cout<<s.id<<"\t\t"<<s.name<<"\t\t"<<s.price<<"\t\t"<<s.quantity<<"\t\t"<<s.description; 
            }
        }
    }
    if(!flag)
    {
        cout<<"\n\nRecord Not Found...";
    }
}

void User::searchProduct()
{
    int ch,id,price;
    string name;
    cout<<"\n1-->Search By id";
    cout<<"\n2-->Search By name";
    cout<<"\n3-->Search By name with price specification ";
    cout<<"\nEnter your choice : ";
    cin>>ch;
    switch (ch)
    {
    case 1:
        cout<<"\nEnter id of product : ";
        cin>>id;
        search(id);

        break;
    case 2:
        cout<<"\nEnter name of product : ";
        cin>>name;
        search(name);

        break;
    case 3:
        cout<<"\nEnter name of product : ";
        cin>>name;
        cout<<"\nEnter Min. Price budget : ";
        cin>>price;
        search(name,price);

        break;
    default:
        cout<<"\nInvalid choice..";
        break;
    }
    
}

void User::display_cart()
{
    cout<<"\n\t\t------------------Cart--------------------\n\n";
    cout<<"\n\t\t---------------Product List---------------\n\n";

    cout<<"Id\t\tName\t\tPrice\t\tQuantity\tDescription";
    for(Product p:cart)
    {
        cout<<endl;
        cout<<p.id<<"\t\t"<<p.name<<"\t\t"<<p.price<<"\t\t"<<p.quantity<<"\t\t"<<p.description;
    }

}


void User::add_to_cart()
{
    int tid,ch,flag;
    listOfid();
    while(1)
    {
        cout<<"\nEnter id of product which you want to add to cart : ";
        cin>>tid;
        flag=1;
        if(flag)
        {
            for(Product t:cart)
            {
                if(t.id == tid)
                {
                    flag=0;
                    cout<<"\nProduct already added to cart\n";
                    break;
                }
            }
        }
        if(flag)
        {
            for(Product p:p_list)
            {
                if(p.id == tid) 
                {
                    p.atc=true;
                    p.q_ord=1;
                    cart.push_back(p);
                    cout<<"\nProduct Added to Cart Successfully..\n";
                    break;
                }
            }
        }    
            cout<<"\nDo you want to add more products to cart";
            cout<<"\nEnter 0 to exit : ";
            cin>>ch;
            if(!ch)
                break;
    }    
}

void User::placeOrder()
{
    int ch;
    for(Product p:cart)
    {
        start:
        cout<<"\nEnter Quantity for "<<p.name<<" : ";
        cin>>p.q_ord;
        if(p.q_ord<=p.quantity)
        {
            if(p.q_ord>0)
            {
                orderList.push_back(p);
                total += (p.price*p.q_ord);
            }
            else
            {
                p.q_ord=1;
                cout<<"\nMinimum 1 quantity required..";
                cout<<"\nDo you wish to change quantity ? ";
                cout<<"\n1-->YES : ";
                cin>>ch;
                if(ch==1)
                    goto start;
            }
        }
        else
        {
            cout<<"\nQuantity available is "<<p.quantity<<endl;
            goto start;
        }
    }

    if(total>0)
    {
        cout<<"\nOrder Successfully Placed..";
        cart.clear();
    }
    else
    {
        cout<<"\nYour Cart is Empty..";
    }
}

void User::checkout()
{
    if(total>0)
    {
        co_flag=1;
        cout<<"\nTotal Bill : Rs. "<<total;
        
    }
    else
    {
        cout<<"\nNo Order Placed..";
    }
}

void User::orderDetails()   
{
    if(total>0 && co_flag==1)
    {
        cout<<"\n\t\t------------------Order Details--------------------\n\n";
        // cout<<"\n\t\t---------------Product List---------------\n\n";

        cout<<"Id\t\tName\t\tPrice\t\tQuantity ordered\tDescription";
        
        
        for(Product x:orderList)
        {
            cout<<endl;
            cout<<x.id<<"\t\t"<<x.name<<"\t\t"<<x.price<<"\t\t\t"<<x.q_ord<<"\t\t"<<x.description;
        }
        
        cout<<"\n\n\n\n\t\tTotal Bill : Rs. "<<total;
        total=0;
        co_flag=0;
    }
    else
    {
        cout<<"\nNo Order Placed Yet!";
    }
}

int main()
{
    User userobj;    
    int choice,ch;
    while(1)
    {
        start:
        cout<<"\n\n1-->Admin";
        cout<<"\n2-->User";
        cout<<"\n3-->Exit";
        cout<<"\nEnter Your Choice : ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                //Admin Section
                while(1)
                {
                    Product obj;
                    obj.add_Product();
                    cout<<"\nEnter 0 to exit adding products --> ";
                    cin>>ch;
                    if(!ch)
                        break;
                }
                break;
            case 2:
                //USER SECTION
            while(1)
            {
                // system("CLS");
                cout<<"\n\n1-->Display All Products";
                cout<<"\n2-->Search Any Product";
                cout<<"\n3-->Display Particular Product";
                cout<<"\n4-->Add Product to Cart";
                cout<<"\n5-->Display Cart";
                cout<<"\n6-->Place Order";
                cout<<"\n7-->Checkout";
                cout<<"\n8-->Order Details";
                cout<<"\n9-->Order History";
                cout<<"\n10-->Exit";
                cout<<"\nEnter your Choice : ";
                cin>>ch;
                switch(ch)
                {
                    case 1:
                        userobj.display_All_Products();
                    break;
                    case 2:
                        userobj.searchProduct();
                    break;
                    case 3:
                        userobj.specific_Product();
                    break;
                    case 4:
                        userobj.add_to_cart();
                    break;
                    case 5:
                        userobj.display_cart();
                    break;
                    case 6:
                        userobj.placeOrder();
                    break;
                    case 7:
                        userobj.checkout();
                    break;
                    case 8:
                        userobj.orderDetails();
                    break;
                    case 10:
                        goto start;
                    break;
                    default:
                    cout<<"\nInvalid Choice..";

                }//End of switch of User

            }//End of While of User
                break;
            case 3:
                exit(0);
                break;
            default:
                cout<<"\nInvalid Choice..";

        }//End of Main-Switch

    }//End of Main-while

    return 0;
}