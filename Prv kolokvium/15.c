#include <stdio.h>
#define NEDELI 4
#define DENOVI 5

typedef struct RabotnaNedela {
    int casovi[DENOVI];
    int nedela;
} RN;

typedef struct Rabotnik {
    char ime[50];
    RN nedeli[NEDELI];
} R;

int maxNedela (R *r) {
    int max_casovi = 0, nedela;

    for (int i = 0; i < NEDELI; i++) {
        int casovi = 0;
        for (int j = 0; j < DENOVI; j++) casovi += r->nedeli[i].casovi[j];

        if (!i) {
            max_casovi = casovi;
            nedela = i+1;
        } else if (max_casovi < casovi) {
            max_casovi = casovi;
            nedela = i+1;
        }
    }

    return nedela;
}

void table (R *r, int n) {
    printf("Rab\t");
    for (int i = 0; i < NEDELI; i++) printf("%d\t", i+1);
    printf("Vkupno\n");

    for (int i = 0; i < n; i++) {
        printf("%s\t", r[i].ime);
        int vkupno = 0;

        for (int j = 0; j < NEDELI; j++) {
            int casovi = 0;
            for (int k = 0; k < DENOVI; k++) casovi += r[i].nedeli[j].casovi[k];

            vkupno += casovi;
            printf("%d\t", casovi);
        }

        printf("%d\n", vkupno);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}