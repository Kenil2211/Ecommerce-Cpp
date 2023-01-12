#ifndef First_hpp
#define First_hpp

class Admin
{
    public:
    void add_Product();
    void removeProduct();
};

class User
{
    public:
    void display_All_Products();
    void specific_Product();
    void add_to_cart();
    void display_cart();
    void placeOrder();
    void checkout();
    void orderHistory();
    void orderDetails();
    void searchProduct();
};


#endif 