#include <iostream>
#include <cstring>
using namespace std;

enum tip { // #DEFINE ama better
    POP, RAP, ROK
};

class Pesna {
private: // so treba da sodrzi
    char *name;
    int minutes;
    tip type;
public:
    Pesna (const char *name = "", int minutes = 0, tip type = POP) { // constructor
        this->type = type;
        this->minutes = minutes;
        this->name = new char[strlen(name) + 1]; // initializing na char pointer
        strcpy(this->name, name); // kopiranje od name
    }

    tip getTip() {
        return type;
    }

    int getMinutes() {
        return minutes;
    }

    void pecati() {
        cout << "\"" << name << "\"-" << minutes << "min" << endl;
    }
};

class CD {
private: // so treba da sodrzi
    Pesna pesna[10];
    int pesni;
    int max_minutes;
public:
    CD (int max_minutes = 0) { // constructor
        this->max_minutes = max_minutes;
        pesni = 0; // initializing size - pesna e so static allocation znaci ne treba "= new Pesna[...."
    }

    int getBroj () {
        return pesni;
    }

    Pesna getPesna (int i) { // se vrakja pesna na toj indeks
        return pesna[i];
    }

    void pecatiPesniPoTip (tip t) {
        for (int i = 0; i < pesni; i++) if (pesna[i].getTip() == t) pesna[i].pecati();
    }

    void dodadiPesna (Pesna &p) {
        int minutes = 0;
        if (pesni < 10) {
            for (int i = 0; i < pesni; i++) minutes += pesna[i].getMinutes();
            if (minutes + p.getMinutes() < max_minutes) {   // ako e pomalku od limitot
                pesna[pesni] = p;                           // ne e pointer so znaci ne treba uste 4 linii
                pesni++;
            }
        }
    }
};


// OD COURSES - ne od mene
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}