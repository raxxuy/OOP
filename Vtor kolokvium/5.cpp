#include <iostream>
#include <cstring>
#define MAX 50
using namespace std;

enum typeC {
    standard, loyal, vip
};

class UserExistsException {
private:
    char *exception;
public:
    UserExistsException (const char *exception = "") {
        this->exception = new char[strlen(exception) + 1];
        strcpy(this->exception, exception);
    }

    void message () {
        cout << exception << endl;
    }
};

class Customer {
private:
    char name[50];
    char email[50];
    typeC type;
    static int base_discount;
    const static int additional_discount = 20;
    int products;
public:
    Customer (const char *name = "", const char *email = "", typeC type = standard, int products = 0) {
        this->type = type;
        this->products = products;
        strcpy(this->name, name);
        strcpy(this->email, email);
    }

    void setDiscount1 (int discount) {
        if (type == loyal) Customer::base_discount = discount;
    }

    friend ostream &operator << (ostream &out, Customer &c) {
        out << c.name << endl << c.email << endl << c.products << endl;
        out << (c.type == standard ? "standard " : c.type == loyal ? "loyal " : "vip ");
        out << (c.type == standard ? 0 : c.type == loyal ? base_discount : base_discount + additional_discount) << endl;

        return out;
    }

    friend class FINKI_bookstore;
};

int Customer::base_discount = 10;

class FINKI_bookstore {
private:
    Customer *customers;
    int numCustomers;
public:
    FINKI_bookstore () {
        customers = nullptr;
        numCustomers = 0;
    }

    void setCustomers (Customer *c, int n) {
        customers = new Customer[n];
        numCustomers = n;
        for (int i = 0; i < n; i++) customers[i] = c[i];
    }

    void update () {
        for (int i = 0; i < numCustomers; i++) {
            if (customers[i].type == loyal and customers[i].products > 10) customers[i] = Customer(customers[i].name, customers[i].email, vip, customers[i].products);
            if (customers[i].type == standard and customers[i].products > 5) customers[i] = Customer(customers[i].name, customers[i].email, loyal, customers[i].products);
        }
    }

    FINKI_bookstore &operator += (const Customer &c) {

        for (int i = 0; i < numCustomers; i++) if (not strcmp(customers[i].email, c.email)) throw UserExistsException("The user already exists in the list!");

        Customer *tmp = customers;
        customers = new Customer[numCustomers + 1];
        for (int i = 0; i < numCustomers; i++) customers[i] = tmp[i];
        customers[numCustomers++] = c;

        return *this;
    }

    friend ostream &operator << (ostream &out, FINKI_bookstore &fc) {
        for (int i = 0; i < fc.numCustomers; i++) out << fc.customers[i];
        return out;
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;

        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc+=c;
        } catch (UserExistsException &e) {
            e.message();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}