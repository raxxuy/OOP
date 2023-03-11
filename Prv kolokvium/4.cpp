#include <iostream>
#include <cstring>
using namespace std;

class Patnik {
private: // so treba da sodrzi
    char name[100];
    int _class;
    bool bicycle;
public:
    Patnik (const char *name = "", int _class = 0, bool bicycle = false) { // constructor
        this->_class = _class;
        this->bicycle = bicycle;
        strcpy(this->name, name);
    }

    int getClass () {
        return _class;
    }

    bool hasBicycle () {
        return bicycle;
    }

    friend ostream &operator << (ostream &out, Patnik &p) {
        return out << p.name << endl << p._class << endl << p.bicycle << endl;
    }
};

class Voz {
private: // so treba da sodrzi
    char destination[100];
    Patnik *passenger;
    int passengers;
    int bikes;
public:
    Voz (const char *destination = "", int bikes = 0) { // constructor
        passenger = nullptr;    // mora vaka na pointeri
        passengers = 0;         // mora 0
        this->bikes = bikes;
        strcpy(this->destination, destination);
    }

    void patniciNemaMesto () {
        int class1 = 0, class2 = 0, bicycles = bikes;

        for (int i = 0; i < passengers; i++) {
            if (passenger[i].hasBicycle() && passenger[i].getClass() == 1) {
                if (bicycles) bicycles--;
                else class1++;
            }
        }

        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << class1 << endl;

        for (int i = 0; i < passengers; i++) {
            if (passenger[i].hasBicycle() && passenger[i].getClass() == 2) {
                if (bicycles) bicycles--;
                else class2++;
            }
        }

        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << class2 << endl;
    }

    Voz &operator += (Patnik &p) {
        if (p.hasBicycle() && !bikes) return *this;                 // ako ne drzi vozot tochaci
        Patnik *tmp = passenger;                                    // za kopiranje
        passenger = new Patnik[passengers + 1];                     // se prosiruva pointerot so pravenje nov size
        for (int i = 0; i < passengers; i++) passenger[i] = tmp[i]; // se kopiraat tmp patnicite na passenger pointerotchar
        passenger[passengers++] = p;                                // noviot patnik i se zgolemuva brojot na patnici so ++
        return *this;
    }

    friend ostream &operator << (ostream &out, Voz &v) {
        out << v.destination << endl;
        for (int i = 0; i < v.passengers; i++) out << v.passenger[i] << endl;
        return out;
    }
};


// OD COURSES - ne od mene
int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}