#include <iostream>
#include <cstring>
using namespace std;

class IceCream {
private:
    char *name;
    char ingredients[100];
    float price;
    int discount;
    void copy (const IceCream &ic) {
        price = ic.price;
        discount = ic.discount;
        name = new char[strlen(ic.name) + 1];
        strcpy(name, ic.name);
        strcpy(ingredients, ic.ingredients);
    }
public:
    IceCream (const char *name = "", const char *ingredients = "", float price = 0) {
        discount = 0;
        this->price = price;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
    }

    IceCream (const IceCream &ic) {
        copy(ic);
    }

    void setDiscount (int d) {
        discount = d;
    }

    void setName (char *nm) {
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
    }

    IceCream &operator = (const IceCream &ic) {
        if (this == &ic) return *this;
        copy(ic);
        return *this;
    }

    IceCream &operator ++ () {
        discount += 5;
        return *this;
    }

    IceCream &operator + (const char *nm) {
        char *new_name = new char[strlen(name) + 1];
        strcpy(new_name, name);
        name = new char[strlen(new_name) + strlen(nm) + 1];
        strcpy(name, new_name);
        strcat(name, " + ");
        strcat(name, nm);
        price += 10;
        return *this;
    }

    friend ostream &operator << (ostream &out, IceCream &ic) {
        out << ic.name << ": " << ic.ingredients << " " << ic.price;
        if (ic.discount) out << " (" << ic.price * (1 - (float) ic.discount/100) << ")";
        return out;
    }

    ~IceCream () {
        delete [] name;
    }
};

class IceCreamShop {
private:
    char name[50];
    IceCream *ic;
    int ic_num;
public:
    IceCreamShop (const char *name = "") {
        ic = nullptr;
        ic_num = 0;
        strcpy(this->name, name);
    }

    IceCreamShop &operator += (const IceCream &Ic) {
        IceCream *tmp = ic;
        ic = new IceCream[ic_num + 1];
        for (int i = 0; i < ic_num; i++) ic[i] = tmp[i];
        ic[ic_num++] = Ic;
        return *this;
    }

    friend ostream &operator << (ostream &out, IceCreamShop &ics) {
        out << ics.name << endl;
        for (int i = 0; i < ics.ic_num; i++) out << ics.ic[i] << endl;
        return out;
    }

    ~IceCreamShop () {
        delete [] ic;
    }
};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}