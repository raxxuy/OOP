#include <iostream>
using namespace std;

struct Laptop {
    char mark[100];
    float dimensions;
    bool touch;
    int price;
};

struct ITStore {
    char name[100];
    char location[100];
    Laptop laptop[100];
    int laptops;
    void print();
};

void ITStore::print() {
    cout << name << " " << location << endl;
    for (int j = 0; j < laptops; j++) cout << laptop[j].mark << " " << laptop[j].dimensions << " " << laptop[j].price << endl;
}

void najeftina_ponuda (ITStore *s, int n) {
    ITStore cheapest;
    int cheapest_price = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < s[i].laptops; j++) {
            if (!cheapest_price && s[i].laptop[j].touch) {
                cheapest = s[i];
                cheapest_price = s[i].laptop[j].price;
            }

            if (cheapest_price > s[i].laptop[j].price && s[i].laptop[j].touch) {
                cheapest = s[i];
                cheapest_price = s[i].laptop[j].price;
            }
        }
    }

    cout << "Najeftina ponuda ima prodavnicata:\n" << cheapest.name << " " << cheapest.location << "\nNajniskata cena iznesuva: " << cheapest_price;
}

int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for (int i = 0; i < n; i++) { // se dopolnuva
        cin >> s[i].name;         // se dopolnuva
        cin >> s[i].location;     // se dopolnuva
        cin >> s[i].laptops;      // se dopolnuva

        for (int j = 0; j < s[i].laptops; j++) { // se dopolnuva
            cin >> s[i].laptop[j].mark;          // se dopolnuva
            cin >> s[i].laptop[j].dimensions;    // se dopolnuva
            cin >> s[i].laptop[j].touch;         // se dopolnuva
            cin >> s[i].laptop[j].price;         // se dopolnuva
        }
    }

    //pecatenje na site prodavnici
    for (int i = 0; i < n; i++) s[i].print(); // se dopolnuva

    //povik na glavnata metoda
    najeftina_ponuda(s, n); // // se dopolnuva

    return 0;
}
