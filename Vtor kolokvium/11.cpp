#include <iostream>
#include <cstring>
using namespace std;

class Delo {
private:
    char name[50];
    int year;
    char country[50];
public:
    Delo (const char *name = "", int year = 0, const char *country = "") {
        this->year = year;
        strcpy(this->name, name);
        strcpy(this->country, country);
    }

    char *getIme () {
        return name;
    }

    bool operator == (const Delo &d) {
        return not strcmp(name, d.name);
    }

    friend class Pretstava;
};

class Pretstava {
protected:
    Delo act;
    int tickets;
    char date[15];
public:
    Pretstava (Delo act = {}, int tickets = 0, const char *date = "") {
        this->act = act;
        this->tickets = tickets;
        strcpy(this->date, date);
    }

    Delo &getDelo () {
        return act;
    }

    int getTickets () {
        return tickets;
    }

    virtual int cena () {
        int M, N;

        if (act.year < 1801) M = 100;
        else if (act.year < 1901) M = 75;
        else M = 50;

        if (not strcmp(act.country, "Italija")) N = 100;
        else if (not strcmp(act.country, "Rusija")) N = 150;
        else N = 80;

        return M + N;
    }
};

class Opera : public Pretstava {
public:
    Opera (Delo act, int tickets, const char *date) : Pretstava(act, tickets, date) {}
};

class Balet : public Pretstava {
private:
    static int price;
public:
    Balet (Delo act, int tickets, const char *date) : Pretstava(act, tickets, date) {}

    static void setCenaBalet (int pr) {
        Balet::price = pr;
    }

    int cena () override {
        return Pretstava(act, tickets, date).cena() + Balet::price;
    }
};

int Balet::price = 150;

int prihod (Pretstava **shows, int numShows) {
    int sum = 0;

    for (int i = 0; i < numShows; i++) sum += (*shows[i]).cena() * (*shows[i]).getTickets();
    return sum;
}

int brojPretstaviNaDelo (Pretstava **shows, int numShows, Delo act) {
    int count = 0;

    for (int i = 0; i < numShows; i++) if ((*shows[i]).getDelo() == act) count++;
    return count;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}