#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class OutOfBoundException {
private:
    char *exception;
public:
    OutOfBoundException (const char *exception = "") {
        this->exception = new char[strlen(exception) + 1];
        strcpy(this->exception, exception);
    }

    void message () {
        cout << exception << endl;
    }
};

class Karticka {
protected:
    char receipt[15];
    int pin;
    bool hasPins;
public:
    Karticka (const char *receipt = "", int pin = 0, bool hasPins = false) {
        this->pin = pin;
        this->hasPins = hasPins;
        strcpy(this->receipt, receipt);
    }

    bool getHasPins () {
        return hasPins;
    }

    char *getReceipt () {
        return receipt;
    }

    virtual int tezinaProbivanje () {
        return ceil(log10(pin));
    }

    friend ostream &operator << (ostream &out, Karticka &k) {
        return out << k.receipt << ": " << k.tezinaProbivanje() << endl;
    }
};

class SpecijalnaKarticka : public Karticka {
private:
    int *pins;
    int numPins;
    const static int p = 4;
public:
    SpecijalnaKarticka (const char *receipt, int pin) : Karticka(receipt, pin, true) {
        pins = nullptr;
        numPins = 0;
    }

    SpecijalnaKarticka &operator += (const int pin) {

        if (numPins == p) throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");

        int *tmp = pins;
        pins = new int[numPins + 1];
        for (int i = 0; i < numPins; i++) pins[i] = tmp[i];
        pins[numPins++] = pin;

        return *this;
    }

    int tezinaProbivanje () override {
        return Karticka::tezinaProbivanje() + numPins;
    }

    ~SpecijalnaKarticka () {
        delete [] pins;
    }
};

class Banka {
private:
    char name[30];
    Karticka *cards[20];
    int numCards;
    static int LIMIT;
public:
    Banka (const char *name = "", Karticka **cards = nullptr, int numCards = 0) {
        this->numCards = numCards;

        strcpy(this->name, name);

        for (int i = 0; i < numCards; i++) {
            if ((*cards[i]).getHasPins()) this->cards[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(cards[i]));
            else this->cards[i] = new Karticka(*cards[i]);
        }
    }

    static void setLIMIT (int limit) {
        LIMIT = limit;
    }

    void pecatiKarticki () {
        cout << "Vo bankata " << name << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < numCards; i++) if ((*cards[i]).tezinaProbivanje() <= LIMIT) cout << *cards[i];
    }

    void dodadiDopolnitelenPin (char *receipt, int newPin) {
        for (int i = 0; i < numCards; i++)
            if (not strcmp((*cards[i]).getReceipt(), receipt)) if ((*cards[i]).getHasPins()) *dynamic_cast<SpecijalnaKarticka *>(cards[i]) += newPin;
    }

    ~Banka () {
        for (int i = 0; i < numCards; i++) delete [] cards[i];
    }
};

int Banka::LIMIT = 7;

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        try {
            komercijalna.dodadiDopolnitelenPin(smetka,pin);
        } catch (OutOfBoundException &e) {
            e.message();
        }
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}