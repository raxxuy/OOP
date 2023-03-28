// За програмски јазик да се употреби C.
//
// Да се напише програма во која од стандарден влез се внесува бројот N (бројот на фудбалски тимови) и информациите за N-те фудбалски тимови.
//
// Една структура за Фудбалски тим (FootballTeam) треба да ги чува следните информации:
// -Името на тимот (низа од карактери)
// -Низа од играчи (претставени преку структурата FootballPlayer, при што еден тим секогаш ќе има 11 играчи)
//
// Во структурата Фудбалски играч (FootballPlayer) треба да се чуваат следните информации:
// -Името на играчот (низа од карактери)
// -Број на дресот (int)
// -Број на дадени голови (int)
//
// Ваша задача е да направите функција void bestTeam(FootballTeam * teams, int n) која ќе го печати тимот со
// најмногу дадени голови (во случај да има повеќе тима со ист број на голови треба да се печати првиот што е внесен).

#include <stdio.h>

typedef struct FootballPlayer {
    char name[50];
    int number;
    int goals;
} FootballPlayer;

typedef struct FootballTeam {
    char name[50];
    FootballPlayer players[11];
} FootballTeam;

void bestTeam (FootballTeam *teams, int n) {
    FootballTeam best;
    int most;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < 11; j++) count += teams[i].players[j].goals;

        if (!i || most < count) {
            most = count;
            best = teams[i];
        }
    }

    printf("Najdobar tim e: %s", best.name);
}

int main() {
    FootballTeam teams[100];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", teams[i].name);
        for (int j = 0; j < 11; j++) scanf("%s %d %d", teams[i].players[j].name, &teams[i].players[j].number, &teams[i].players[j].goals);
    }

    bestTeam(teams, n);
}