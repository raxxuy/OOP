#include <stdio.h>

typedef struct Pacient {
    char ime[100];
    int zdrastveno;
    int pregledi;
} pacient;

typedef struct Doktor {
    char ime[100];
    int br_pac;
    pacient niza[100];
    float cena;
} doktor;

void najuspesen_doktor (doktor *md, int n) {
    doktor najuspesen;
    float najuspesna;
    int najuspesen_pregledi;

    for (int i = 0; i < n; i++) {
        float cena = 0;
        int pregledi = 0;
        for (int j = 0; j < md[i].br_pac; j++) {
            if (!md[i].niza[j].zdrastveno) cena += md[i].cena * md[i].niza[j].pregledi;
            pregledi += md[i].niza[j].pregledi;
        }
        if (!i) {
            najuspesen = md[0];
            najuspesna = cena;
            najuspesen_pregledi = pregledi;
        } else {
            if (najuspesna < cena) {
                najuspesen = md[i];
                najuspesna = cena;
                najuspesen_pregledi = pregledi;
            }

            if (najuspesna == cena && najuspesen_pregledi < pregledi) {
                najuspesen = md[i];
                najuspesna = cena;
                najuspesen_pregledi = pregledi;
            }
        }
    }

    printf("%s %.2f %d", najuspesen.ime, najuspesna, najuspesen_pregledi);
}

int main()
{
    int i, j, n, broj;
    doktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        //ime na doktor
        scanf("%s", &md[i].ime);
        //broj na pacienti
        scanf("%d", &md[i].br_pac);
        //cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].br_pac; j++){
            scanf("%s", &md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}