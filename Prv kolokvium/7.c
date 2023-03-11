#include <stdio.h>

typedef struct Vozenje {
    char ime[100];
    int traenje;
    float cena;
    int daliPopust;
} Vozenje;

typedef struct ZabavenPark {
    char ime[100];
    char lokacija[100];
    Vozenje niza[100];
    int n;
} ZabavenPark;

void pecati (ZabavenPark *zp, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s\n", zp[i].ime, zp[i].lokacija);
        for (int j = 0; j < zp[i].n; j++) printf("%s %d %.2f\n", zp[i].niza[j].ime, zp[i].niza[j].traenje, zp[i].niza[j].cena);
    }
}

void najdobar_park (ZabavenPark *zp, int n) {
    ZabavenPark best;
    int max_discounts = 0, max_time = 0;
    for (int i = 0; i < n; i++) {
        int discounts = 0, time = 0;
        for (int j = 0; j < zp[i].n; j++) {
            if (zp[i].niza[j].daliPopust) discounts++;
            time += zp[i].niza[j].traenje;
        }

        if (max_discounts == discounts && time > max_time) {
            best = zp[i];
            max_discounts = discounts;
            max_time = time;
        }

        if (max_discounts < discounts) {
            best = zp[i];
            max_discounts = discounts;
            max_time = time;
        }
    }

    printf("Najdobar park: %s %s", best.ime, best.lokacija);
}

int main()
{
    int i, j, n, broj;
    //kreiraj niza od maksimum 100 zabavni parkovi
    ZabavenPark ff[100];
    scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
        //ime na festivalot
        scanf("%s", ff[i].ime);
        //mesto
        scanf("%s", ff[i].lokacija);
        //broj na filmovi
        scanf("%d", &ff[i].n);

        for (j = 0; j < ff[i].n; j++){
            scanf("%s", ff[i].niza[j].ime);  			/* Ime na filmot */
            scanf("%d", &ff[i].niza[j].traenje); 		/* Vremetraenje   */
            scanf("%f", &ff[i].niza[j].cena); 	/* Cena */
            scanf("%d", &ff[i].niza[j].daliPopust);	/* Popust */

        }


    }
    pecati(ff,n);
    najdobar_park(ff,n);

    return 0;
}