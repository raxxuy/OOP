#include <iostream>
#include <cstring>
using namespace std;

struct Voz {
    char relation[50];
    double distance;
    int passengers;
};

struct ZeleznickaStanica {
    char city[20];
    Voz voz[30];
    int vozovi;
};

void najkratkaRelacija (ZeleznickaStanica *zs, int n, char *grad) {
    double min = 0;
    char relation[50];
    for (int i = 0; i < n; i++) for (int j = 0; j < zs[i].vozovi; j++) {
            if (!strncmp(zs[i].voz[j].relation, grad, strlen(grad))) {
                if (!min) {
                    min = zs[i].voz[j].distance;
                    strcpy(relation, zs[i].voz[j].relation);
                }
                if (min >= zs[i].voz[j].distance) {
                    min = zs[i].voz[j].distance;
                    strcpy(relation, zs[i].voz[j].relation);
                }
            }
        }

    cout << "Najkratka relacija: " << relation << " (" << min << " km)";
}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>zStanica[i].city;
        cin>>zStanica[i].vozovi;
        for (int j=0;j<zStanica[i].vozovi;j++) {
            cin>>zStanica[i].voz[j].relation;
            cin>>zStanica[i].voz[j].distance;
            cin>>zStanica[i].voz[j].passengers;
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}