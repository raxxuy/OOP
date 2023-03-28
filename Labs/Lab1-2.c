// За програмски јазик да се употреби C.
//
// Да се креира структура Engine во која што ќе се чуваат податоци за коњска сила / horsepower (int) и вртежен момент / torque (int).
// Потоа, да се креира структура Car во која што ќе  се чуваат податоци името на производителот (char array),
// која година е произведена колата (int) и кој мотор / engine (Engine) која што го користи.

#include <stdio.h>

typedef struct Engine {
    int horsepower;
    int torque;
} Engine;

typedef struct Car {
    char manufacturer[50];
    int year;
    Engine motor;
} Car;

void printCars (Car *cars, int n) {
    Car best;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cars[i].motor.horsepower < cars[j].motor.horsepower) {
                Car temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }
    }

    if (cars[0].motor.torque > cars[1].motor.torque) best = cars[0];
    else best = cars[1];

    printf("Manufacturer: %s\nHorsepower: %d\nTorque: %d", best.manufacturer, best.motor.horsepower, best.motor.torque);
}

int main() {
    Car cars[100];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%s %d %d %d", cars[i].manufacturer, &cars[i].year, &cars[i].motor.horsepower, &cars[i].motor.torque);

    printCars(cars, n);
}