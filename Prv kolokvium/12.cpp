#include <iostream>
#include <cstring>
using namespace std;

class Pica {
private:
    char name[15];
    int price;
    char *ingredients;
    int discount;
public:
    Pica (const char *name = "", int price = 0, const char *ingredients = "", int discount = 0) {
        this->price = price;
        this->discount = discount;
        this->ingredients = new char[strlen(ingredients) + 1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
    }

    int getDiscount () {
        return discount;
    }

    bool istiSe (Pica &p) {
        return !strcmp(ingredients, p.ingredients);
    }

    void pecati () {
        cout << name << " - " << ingredients << ", " << price;
        if (discount) cout << " " << price - price * discount / 100;
        cout << endl;
    }

    Pica &operator = (const Pica &p) {
        if (this == &p) return *this;
        delete [] ingredients;
        price = p.price;
        discount = p.discount;
        ingredients = new char[strlen(p.ingredients) + 1];
        strcpy(name, p.name);
        strcpy(ingredients, p.ingredients);
        return *this;
    }

    ~Pica () {
        delete [] ingredients;
    }
};

class Picerija {
private:
    char name[15];
    Pica *pica;
    int pici;
    void copy (const Picerija &p) {
        pici = p.pici;
        pica = new Pica[pici + 1];
        for (int i = 0; i < pici; i++) pica[i] = p.pica[i];
        strcpy(name, p.name);
    }
public:
    Picerija (const char *name = "") {
        pica = nullptr;
        pici = 0;
        strcpy(this->name, name);
    }

    Picerija (const Picerija &p) {
        copy(p);
    }

    char *getIme () {
        return name;
    }

    void setIme (char *nm) {
        strcpy(name, nm);
    }

    void piciNaPromocija () {
        for (int i = 0; i < pici; i++) if (pica[i].getDiscount()) pica[i].pecati();
    }

    Picerija &operator += (Pica &p) {
        for (int i = 0; i < pici; i++) if (pica[i].istiSe(p)) return *this;
        Pica *tmp = pica;
        pica = new Pica[pici + 1];
        for (int i = 0; i < pici; i++) pica[i] = tmp[i];
        pica[pici++] = p;
        return *this;
    }

    Picerija &operator = (const Picerija &p) {
        if (this == &p) return *this;
        delete [] pica;
        copy(p);
        return *this;
    }

    ~Picerija () {
        delete [] pica;
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}