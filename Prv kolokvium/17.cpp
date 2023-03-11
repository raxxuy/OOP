#include <iostream>
#include <cstring>
using namespace std;

enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char *name;
    float version;
    Tip type;
    float size;
    void copy (const OperativenSistem &os) {
        type = os.type;
        size = os.size;
        version = os.version;
        name = new char[strlen(os.name) + 1];
        strcpy(name, os.name);
    }
public:
    OperativenSistem (const char *name = "", float version = 0, Tip type = LINUX, float size = 0) {
        this->type = type;
        this->size = size;
        this->version = version;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    OperativenSistem (const OperativenSistem &os) {
        copy(os);
    }

    void print () {
        cout << "Ime: " << name << " Verzija: " << version << " Tip: " << type << " Golemina:" << size << "GB" << endl;
    }

    bool ednakviSe (const OperativenSistem &os) {
        return !strcmp(name, os.name) && type == os.type && size == os.size && version == os.version;
    }

    bool istaFamilija (const OperativenSistem &os) {
        return !strcmp(name, os.name) && type == os.type;
    }

    int sporediVerzija (const OperativenSistem &os) {
        if (ednakviSe(os)) return 0;
        else if (version < os.version) return -1;
        else return 1;
    }

    OperativenSistem &operator = (const OperativenSistem &os) {
        if (this == &os) return *this;
        copy(os);
        return *this;
    }

    ~OperativenSistem () {
        delete [] name;
    }
};

class Repozitorium {
private:
    char name[20];
    OperativenSistem *os;
    int os_num;
public:
    Repozitorium (const char *name = "") {
        os = nullptr;
        os_num = 0;
        strcpy(this->name, name);
    }

    void pecatiOperativniSistemi () {
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < os_num; i++) os[i].print();
    }

    void izbrishi (const OperativenSistem &Os) {
        for (int i = 0; i < os_num; i++) if (os[i].ednakviSe(Os)) {
            OperativenSistem *tmp = os;
            int tmp_num = 0;
            for (int j = 0; j < os_num; j++) if (!os[j].ednakviSe(Os)) tmp[tmp_num++] = os[j];
            os_num = tmp_num;
            os = new OperativenSistem[os_num];
            for (int j = 0; j < os_num; j++) os[j] = tmp[j];
            return;
        }
    }

    void dodadi (const OperativenSistem &Os) {
        for (int i = 0; i < os_num; i++) {
            if (os[i].istaFamilija(Os)) if (os[i].sporediVerzija(Os) == -1) {
                os[i] = Os;
                return;
            }
        }

        OperativenSistem *tmp = os;
        os = new OperativenSistem[os_num + 1];
        for (int i = 0; i < os_num; i++) os[i] = tmp[i];
        os[os_num++] = Os;
    }

    ~Repozitorium () {
        delete [] os;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}