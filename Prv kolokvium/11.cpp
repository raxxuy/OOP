#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik {
private:
    char *name;
    bool sex;
    int age;
public:
    Ucesnik (const char *name = "", bool sex = false, int age = 0) {
        this->age = age;
        this->sex = sex;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    int getAge () {
        return age;
    }

    bool operator > (Ucesnik &u) {
        return age > u.age;
    }

    friend ostream &operator << (ostream &out, Ucesnik &u) {
        return out << u.name << endl << (u.sex ? "mashki" : "zhenski") << endl << u.age;
    }
};

class Maraton {
private:
    char location[100];
    Ucesnik *ucesnik;
    int ucesnici;
public:
    Maraton (const char *location = "") {
        ucesnici = 0;
        strcpy(this->location, location);
    }

    double prosecnoVozrast () {
        double age = 0;
        for (int i = 0; i < ucesnici; i++) age += ucesnik[i].getAge();
        return age / ucesnici;
    }

    void pecatiPomladi (Ucesnik &u) {
        for (int i = 0; i < ucesnici; i++) if (u > ucesnik[i]) cout << ucesnik[i] << endl;
    }

    Maraton operator += (Ucesnik &u) {
        ucesnik[ucesnici++] = u;
        return *this;
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}