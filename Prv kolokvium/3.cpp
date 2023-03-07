#include <iostream>
#include <cstring>
using namespace std;

class StockRecord {
private: // so treba da sodrzi
    char id[12];
    char company[50];
    double base_price;
    double sale_price;
    int sales;
public:
    StockRecord (const char *id = "", const char *company = "", double base_price = 0, int sales = 0) { // constructor
        this->sales = sales;
        this->base_price = base_price;
        strcpy(this->id, id);
        strcpy(this->company, company);
    }

    void setNewPrice (double np) {
        sale_price = np;
    }

    double value () {
        return sales * sale_price;
    }

    double profit () {
        return sales * (sale_price - base_price);
    }

    friend ostream &operator << (ostream &out, StockRecord &sr) {
        return out << sr.company << " " << sr.sales << " " << sr.base_price << " " << sr.sale_price << " " << sr.profit() << endl;
    }
};

class Client {
private: // so treba da sodrzi
    char *name;
    int id;
    StockRecord *company; // aka dynamic allocation
    int companies;
public:
    Client (const char *name = "", int id = 0) {
        company = nullptr;  // mora vaka na pointeri
        companies = 0;      // mora 0
        this->id = id;
        this->name = new char[strlen(name) + 1]; // mora vaka na char pointer pred kopiranje
        strcpy(this->name, name);
    }

    double totalValue () {
        double value = 0;
        for (int i = 0; i < companies; i++) value += company[i].value();
        return value;
    }

    Client &operator += (StockRecord &sr) {
        StockRecord *tmp = company;                                 // za kopiranje
        company = new StockRecord[companies + 1];                   // se prosiruva pointerot so pravenje nov size
        for (int i = 0; i < companies; i++) company[i] = tmp[i];    // se kopiraat tmp kompaniite na company pointerot
        company[companies] = sr;                                    // nova kompanija
        companies++;                                                // se zgolemuva brojot na patnici
        return *this;
    }

    friend ostream &operator << (ostream &out, Client &c) {
        out << c.id << " " << c.totalValue() << endl;
        for (int i = 0; i < c.companies; i++) out << c.company[i];
        return out;
    }

    ~Client () { // destructor
        delete [] company;
    }
};


// OD COURSES - ne od mene
int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}