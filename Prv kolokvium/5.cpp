#include <iostream>
#include <cstring>
using namespace std;

class Gitara {
private: // so treba da sodrzi
    char serial[25];
    float price;
    int year;
    char type[40];
public:
    Gitara (const char *type = "", const char *serial = "", int year = 0, float price = 0) { // constructor
        this->year = year;
        this->price = price;
        strcpy(this->type, type);     // niza znaci no "= new char"
        strcpy(this->serial, serial); // niza znaci no "= new char"
    }

    char *getTip () { // moze i char* whatever
        return type;
    }

    char *getSeriski () { // moze i char* whatever
        return serial;
    }

    int getGodina () {
        return year;
    }

    float getNabavna () {
        return price;
    }

    bool daliIsti (Gitara &g) {
        return strcmp(serial, g.serial) == 0; // return !strcmp(serial, g.serial)
    }

    void pecati () {
        cout << serial << " " << type << " " << price << endl;
    }
};

class Magacin {
private: // so treba da sodrzi
    char name[30];
    char location[60];
    Gitara *gitara;
    int gitari;
    int year;
public:
    Magacin (const char *name = "", const char *location = "", int year = 0) { // constructor
        gitara = nullptr;   // pointer yeah
        gitari = 0;         // yeah
        this->year = year;
        strcpy(this->name, name);
        strcpy(this->location, location);
    }

    double vrednost () {
        double value = 0;
        for (int i = 0; i < gitari; i++) value += gitara[i].getNabavna();
        return value;
    }

    void dodadi (Gitara g) {
        Gitara *tmp = gitara;                                   // za kopiranje
        gitara = new Gitara[gitari + 1];                        // se prosiruva pointerot so pravenje nov size
        for (int i = 0; i < gitari; i++) gitara[i] = tmp[i];    // se kopiraat tmp gitarite na gitara pointerot
        gitara[gitari++] = g;                                     // nova gitara i se zgolemuva brojot na gitari
    }

    void prodadi (Gitara g) {
        int sold = 0, tmp_gitari = 0;       // sold za kolku treba da se namali sizeot na gitara pointerot
        auto *tmp = new Gitara[gitari];     // Gitara *tmp
        for (int i = 0; i < gitari; i++) {
            if (gitara[i].daliIsti(g)) sold++; // se zgolemuva ako ima isti gitari
            else tmp[tmp_gitari++] = gitara[i];  // taa so ne e prodadena se stava vo tmp
        }
        gitara = new Gitara[gitari -= sold]; // se menuva goleminata na pointerot also wtf moze [a -= b]????
        for (int i = 0; i < tmp_gitari; i++) gitara[i] = tmp[i]; // se kopiraat tie so ne se prodadeni
    }

    void pecati (bool daliNovi) {
        cout << name << " " << location << endl;
        if (!daliNovi) for (int i = 0; i < gitari; i++) gitara[i].pecati(); // ako ne e bitno dali se novi ili ne
        else for (int i = 0; i < gitari; i++) if (gitara[i].getGodina() > year) gitara[i].pecati(); // ako e bitno
    }
};

// OD COURSES - ne od mene
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}