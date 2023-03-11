#include <stdio.h>

typedef struct Laptop {
    char mark[100];
    float dimensions;
    int touch;
    int price;
} Laptop;

typedef struct ITStore {
    char name[100];
    char location[100];
    Laptop laptop[100];
    int laptops;
} ITStore;

void print (ITStore s) {
    printf("%s %s\n", s.name, s.location);
    for (int j = 0; j < s.laptops; j++) printf("%s %g %d\n", s.laptop[j].mark, s.laptop[j].dimensions, s.laptop[j].price);
}

void najeftina_ponuda (ITStore *s, int n) {
    ITStore cheapest;
    int cheapest_price = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < s[i].laptops; j++) {
            if (!cheapest_price && s[i].laptop[j].touch) {
                cheapest = s[i];
                cheapest_price = s[i].laptop[j].price;
            }

            if (cheapest_price > s[i].laptop[j].price && s[i].laptop[j].touch) {
                cheapest = s[i];
                cheapest_price = s[i].laptop[j].price;
            }
        }
    }

    printf("Najeftina ponuda ima prodavnicata:\n%s %s\nNajniskata cena iznesuva: %d", cheapest.name, cheapest.location, cheapest_price);
}

int main() {
    ITStore s[100];
    int n;
    scanf("%d",&n); //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i].name);
        scanf("%s", s[i].location);
        scanf("%d", &s[i].laptops);

        for (int j = 0; j < s[i].laptops; j++){
            scanf("%s", s[i].laptop[j].mark);
            scanf("%f", &s[i].laptop[j].dimensions);
            scanf("%d", &s[i].laptop[j].touch);
            scanf("%d", &s[i].laptop[j].price);
        }
    }

    for (int i = 0; i < n; i++) print(s[i]);
    najeftina_ponuda(s, n);

    return 0;
}