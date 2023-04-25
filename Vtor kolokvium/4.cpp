#include <iostream>
#include <cstring>
using namespace std;

enum Size {
    small, large, family
};

class Pizza {
protected:
    char name[20];
    char ingredients[100];
    float base_price;
public:
    Pizza (const char *name = "", const char *ingredients = "", float base_price = 0.0) {
        this->base_price = base_price;
        strcpy(this->name, name);
        strncpy(this->ingredients, ingredients, 49);
    }

    virtual double price () = 0;

    bool operator < (Pizza &p) {
        return price() < p.price();
    }
};

class FlatPizza : public Pizza {
private:
    Size size;
public:
    FlatPizza (const char *name, const char *ingredients, float base_price, Size size = small) : Pizza(name, ingredients, base_price), size(size) {}

    double price () override {
        return base_price * (size == small ? 1.1 : size == family ? 1.3 : 1.5);
    }

    friend ostream &operator << (ostream &out, FlatPizza &fp) {
        return out << fp.name << ": " << fp.ingredients << ", " << (fp.size == small ? "small" : fp.size == large ? "large" : "family") << " - " << fp.price() << endl;
    }
};

class FoldedPizza : public Pizza {
private:
    bool flour;
public:
    FoldedPizza (const char *name, const char *ingredients, float base_price, bool flour = true) : Pizza(name, ingredients, base_price), flour(flour) {}

    void setWhiteFlour (bool fl) {
        flour = fl;
    }

    double price () override {
        return base_price * (flour ? 1.1 : 1.3);
    }

    friend ostream &operator << (ostream &out, FoldedPizza &fp) {
        return out << fp.name << ": " << fp.ingredients << ", " << (fp.flour ? "wf" : "nwf") << " - " << fp.price() << endl;
    }
};

ostream &operator << (ostream &out, Pizza &p) {
    if (dynamic_cast<FlatPizza *>(&p)) return out << *dynamic_cast<FlatPizza *>(&p);
    else return out << *dynamic_cast<FoldedPizza *>(&p);
}

void expensivePizza (Pizza **pizzas, int numPizzas) {
    int index = 0;

    for (int i = 1; i < numPizzas; i++) if (*pizzas[index] < *pizzas[i]) index = i;
    cout << *pizzas[index];
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}