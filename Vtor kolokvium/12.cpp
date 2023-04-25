#include <iostream>
#include <cstring>
using namespace std;

typedef enum type { smartphone, laptop } tip;

class InvalidProductionDate {
private:
    char *exception;
public:
    InvalidProductionDate (const char *exception = "") {
        this->exception = new char[strlen(exception) + 1];
        strcpy(this->exception, exception);
    }

    void message () {
        cout << exception << endl;
    }
};

class Device {
private:
    char model[100];
    type device_type;
    static double hours;
    int year;
public:
    Device (const char *model = "", type device_type = smartphone, int year = 0) {
        this->year = year;
        this->device_type = device_type;
        strcpy(this->model, model);
    }

    double repair () {
        double additional = 0;

        if (year > 2015) additional += 2;
        if (device_type == laptop) additional += 2;

        return additional + Device::hours;
    }

    static void setPocetniCasovi (float hrs) {
        Device::hours = hrs;
    }

    friend ostream &operator << (ostream &out, Device &d) {
        return out << d.model << endl << (d.device_type == smartphone ? "Mobilen " : "Laptop ") << d.repair() << endl;
    }

    friend class MobileServis;
};

double Device::hours = 1;

class MobileServis {
private:
    char address[100];
    Device *devices;
    int numDevices;
public:
    MobileServis (const char *address = "") {
        devices = nullptr;
        numDevices = 0;
        strcpy(this->address, address);
    }

    void pecatiCasovi () {
        cout << "Ime: " << address << endl;
        for (int i = 0; i < numDevices; i++) cout << devices[i];
    }

    MobileServis &operator += (const Device &d) {
        try {
            if (d.year < 2000 or d.year > 2019) throw InvalidProductionDate("Невалидна година на производство");

            Device *tmp = devices;
            devices = new Device[numDevices + 1];
            for (int i = 0; i < numDevices; i++) devices[i] = tmp[i];
            devices[numDevices++] = d;

        } catch (InvalidProductionDate &ipd) {
            ipd.message();
        }

        return *this;
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}