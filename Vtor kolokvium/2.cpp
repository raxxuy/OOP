#include <iostream>
#include <cstring>
using namespace std;

class Vozac {
protected:
    char name[100];
    int age;
    int races;
    bool veteran;
public:
    Vozac (const char *name = "", int age = 0, int races = 0, bool veteran = false) {
        this->age = age;
        this->races = races;
        this->veteran = veteran;

        strcpy(this->name, name);
    }

    virtual double danok () = 0;

    virtual double zarabotuvachka () = 0;

    bool operator == (Vozac &v) {
        return zarabotuvachka () == v.zarabotuvachka();
    }

    friend ostream &operator << (ostream &out, Vozac &v) {
        return out << v.name << endl << v.age << endl << v.races << endl << (v.veteran ? "VETERAN\n" : "");
    }

    virtual ~Vozac () = default;
};

class Avtomobilist : public Vozac {
private:
    float price;
public:
    Avtomobilist (const char *name, int age, int races, bool veteran, float price = 0.0) : Vozac(name, age, races, veteran), price(price) {}

    double zarabotuvachka () override {
        return price / 5;
    }

    double danok () override {
        return (races > 10 ? zarabotuvachka() * 0.15 : zarabotuvachka() * 0.10);
    }
};

class Motociklist : public Vozac {
private:
    int power;
public:
    Motociklist (const char *name, int age, int races, bool veteran, int power = 0) : Vozac(name, age, races, veteran), power(power) {}

    double zarabotuvachka () override {
        return power * 20;
    }

    double danok () override {
        return (veteran ? zarabotuvachka() * 0.25 : zarabotuvachka() * 0.20);
    }
};

int soIstaZarabotuvachka (Vozac **drivers, int numDrivers, Vozac *driver) {
    int count = 0;

    for (int i = 0; i < numDrivers; i++) if ((*drivers[i]) == (*driver)) count++;
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}