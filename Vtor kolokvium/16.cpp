#include <iostream>
#include <cstring>
using namespace std;

class Transport {
protected:
    char destination[20];
    int price;
    int distance;
public:
    Transport (const char *destination = "", int price = 0, int distance = 0) {
        this->price = price;
        this->distance = distance;
        strcpy(this->destination, destination);
    }

    // CRINGE BARANJE
    char *getDestination () { return destination; }
    int getPrice () { return price; }
    int getDistance () { return distance; }

    virtual double cenaTransport () = 0;

    bool operator < (const Transport &t) const {
        return distance < t.distance;
    }

    virtual ~Transport () = default;
};

class AvtomobilTransport : public Transport {
private:
    bool chauffeur;
public:
    AvtomobilTransport (const char *destination, int price, int distance, bool chauffeur = false) : Transport(destination, price, distance), chauffeur(chauffeur) {}

    bool getChauffeur () { return chauffeur; }

    double cenaTransport () override {
        return (chauffeur ? price * 1.2 : price);
    }
};

class KombeTransport : public Transport {
private:
    int people;
public:
    KombeTransport (const char *destination, int price, int distance, int people = 0) : Transport(destination, price, distance), people(people) {}

    int getPeople () { return people; }

    double cenaTransport () override {
        return price - 200 * people;
    }
};

void pecatiPoloshiPonudi (Transport **transports, int numTransports, Transport &transport) {
    for (int i = 0; i < numTransports; i++) for (int j = 0; j < numTransports; j++)
        if (*transports[i] < *transports[j]) swap(transports[i], transports[j]);

    for (int i = 0; i < numTransports; i++)
        if (transports[i]->cenaTransport() > transport.cenaTransport())
            cout << transports[i]->getDestination() << " " << transports[i]->getDistance() << " " << transports[i]->cenaTransport() << endl;
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}