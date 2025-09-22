#include <iostream>
#include <string>
using namespace std;

//----------------------------------PRODUCT CLASS------------------------------------//
class Product {
    string name;
    double price;
public:
    Product() {
        name = "Unknown";
        price = 0.0;
    }
    Product(string n, double p) {
        name = n;
        price = p;
    }
    void show() {
        cout << "Product: " << name << " | Price: " << price << endl;
    }
    friend void applyDiscount(Product &p, double percent);
};

// ---------- Friend function ----------//
void applyDiscount(Product &p, double percent) {
    p.price -= (p.price * percent / 100);
    cout << "Discount Applied! New Price: " << p.price << endl;
}

// ---------- Order Class ----------
class Order {
    static int orderCount;
    double totalAmount;
public:
    Order() { totalAmount = 0; }

    double calcTotal(double price, double shipping = 50) { // Default argument
        totalAmount = price + shipping;
        return totalAmount;
    }

    void confirmOrder() {
        orderCount++;
        cout << "Order Confirmed! Amount: " << totalAmount << endl;
    }

    static void showOrderCount() {
        cout << "Total Orders: " << orderCount << endl;
    }
};
int Order::orderCount = 0;

// ---------- Customer Class ----------
class Customer {
    string name;
    int loyaltyPoints;
public:
    Customer(string n = "Guest", int lp = 0) {
        name = n;
        loyaltyPoints = lp;
    }
    void show() {
        cout << "Customer: " << name << " | Loyalty Points: " << loyaltyPoints << endl;
    }

    // Unary Operator Overloading
    void operator++() {
        loyaltyPoints += 10;
    }

    // Binary Operator Overloading
    int operator+(Customer &c) {
        return this->loyaltyPoints + c.loyaltyPoints;
    }
};

// ---------- Inheritance ----------
class User {
public:
    void login() { cout << "User logged in.\n"; }
};
class Seller : public User {
public:
    void addProduct() { cout << "Seller added a new product.\n"; }
};
class Admin : public Seller {
public:
    void manageSite() { cout << "Admin is managing the site.\n"; }
};
class Payment {
public:
    void pay() { cout << "Payment done successfully.\n"; }
};
class Delivery {
public:
    void deliver() { cout << "Product delivered to customer.\n"; }
};
class ECommerceSystem : public Payment, public Delivery {};


// ---------- Main Program with Switch ----------
int main() {
    Product p1("Laptop", 60000);
    Order o1;
    Customer c1("Alice", 20), c2("Bob", 30);
    Admin admin;
    ECommerceSystem ecs;

    int choice;
    do {
        cout << "\n====== E-COMMERCE MENU ======\n";
        cout << "1. Show Product\n";
        cout << "2. Apply Discount\n";
        cout << "3. Place Order\n";
        cout << "4. Show Order Count\n";
        cout << "5. Show Customer Points\n";
        cout << "6. Add Loyalty (++customer)\n";
        cout << "7. Combine Customer Points (c1+c2)\n";
        cout << "8. Admin Actions (Login, Add Product, Manage Site)\n";
        cout << "9. Payment + Delivery (Multiple Inheritance)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                p1.show();
                break;
            case 2: {
                double percent;
                cout << "Enter discount %: ";
                cin >> percent;
                applyDiscount(p1, percent);
                break;
            }
            case 3: {
                double bill = o1.calcTotal(54000); // shipping default
                o1.confirmOrder();
                break;
            }
            case 4:
                Order::showOrderCount();
                break;
            case 5:
                c1.show();
                c2.show();
                break;
            case 6:
                ++c1;
                cout << "Added points to Alice.\n";
                c1.show();
                break;
            case 7: {
                int total = c1 + c2;
                cout << "Combined Loyalty Points: " << total << endl;
                break;
            }
            case 8:
                admin.login();
                admin.addProduct();
                admin.manageSite();
                break;
            case 9:
                ecs.pay();
                ecs.deliver();
                break;
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 0);

    return 0;
}
