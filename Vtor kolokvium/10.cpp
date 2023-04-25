#include <iostream>
#include <cstring>
using namespace std;

class NegativnaVrednost {
public:
    char *exception;
public:
    NegativnaVrednost (const char *exception = "") {
        this->exception = new char[strlen(exception) + 1];
        strcpy(this->exception, exception);
    }

    void message () {
        cout << exception << endl;
    }
};

class Oglas {
private:
    char title[50];
    char category[30];
    char description[100];
    float price;
public:
    Oglas (const char *title = "", const char *category = "", const char *description = "", float price = 0.0) {
        this->price = price;
        strcpy(this->title, title);
        strcpy(this->category, category);
        strcpy(this->description, description);
    }

    bool operator > (const Oglas &o) const {
        return price > o.price;
    }

    friend ostream &operator << (ostream &out, Oglas &o) {
        return out << o.title << endl << o.description << endl << o.price << " evra" << endl;
    }

    friend class Oglasnik;
};

class Oglasnik {
private:
    char name[20];
    Oglas *oglasi;
    int numOglasi;
public:
    Oglasnik (const char *name = "") {
        oglasi = nullptr;
        numOglasi = 0;
        strcpy(this->name, name);
    }

    void oglasiOdKategorija (const char *category) {
        for (int i = 0; i < numOglasi; i++) if (not strcmp(oglasi[i].category, category)) cout << oglasi[i] << endl;
    }

    void najniskaCena () {
        int index = 0;

        for (int i = 1; i < numOglasi; i++) if (oglasi[index] > oglasi[i]) index = i;
        cout << oglasi[index];
    }

    Oglasnik &operator += (const Oglas &o) {
        try {
            if (o.price < 0) throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");

            Oglas *tmp = oglasi;
            oglasi = new Oglas[numOglasi + 1];
            for (int i = 0; i < numOglasi; i++) oglasi[i] = tmp[i];
            oglasi[numOglasi++] = o;

        } catch (NegativnaVrednost &nv) {
            nv.message();
        }

        return *this;
    }

    friend ostream &operator << (ostream &out, Oglasnik &o) {
        out << o.name << endl;

        for (int i = 0; i < o.numOglasi; i++) out << o.oglasi[i] << endl;
        return out;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}