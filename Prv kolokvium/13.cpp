#include <iostream>
#include <cstring>
using namespace std;

class Zichara {
private:
    char *location;
    int price;
public:
    Zichara (const char *location = "", int price = 0) {
        this->price = price;
        this->location = new char[strlen(location) + 1];
        strcpy(this->location, location);
    }

    int getPrice() {
        return price;
    }
};

class PlaninarskiDom {
private:
    char name[15];
    int prices[2];
    char grade;
    bool imaZichara;
    Zichara *zichara;
public:
    PlaninarskiDom (const char *name = "", const int *prices = nullptr, char grade = 0) {
        zichara = nullptr;
        this->grade = grade;
        strcpy(this->name, name);
        if (prices) for (int i = 0; i < 2; i++) this->prices[i] = prices[i];
    }

    void setZichara (const Zichara &z) {
        if (!imaZichara) imaZichara = true;
        zichara = new Zichara;
        *zichara = z;
    }

    void presmetajDnevenPrestoj (int day, int month, int &price) {
        if (day < 0 || day > 31 || month < 0 || month > 12) throw 0;
        price = 0;
        if (imaZichara) price += zichara->getPrice();
        if (month >= 4 && month <= 8 || (month == 9 && day == 1)) price += prices[0];
        else price += prices[1];
    }

    PlaninarskiDom &operator = (const PlaninarskiDom &pd) {
        if (this == &pd) return *this;
        imaZichara = pd.imaZichara;
        zichara = pd.zichara;
        grade = pd.grade;
        strcpy(name, pd.name);
        for (int i = 0; i < 2; i++) prices[i] = pd.prices[i];
        return *this;
    }

    PlaninarskiDom &operator -- () {
        if (grade == 'F') return *this;
        ++grade;
        return *this;
    }

    bool operator <= (char g) {
        return grade >= g;
    }

    friend ostream &operator << (ostream &out, PlaninarskiDom &pd) {
        return out << pd.name << " klasa:" << pd.grade << (pd.imaZichara ? " so Zichara" : "") << endl;
    }
};

int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}