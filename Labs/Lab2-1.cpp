#include <iostream>
#include <cstring>
using namespace std;

class BasketballPlayer {
private:
    char name[20];
    char surname[20];
    int num;
    int first;
    int second;
    int third;
public:
    BasketballPlayer (const char *name, const char *surname, int num, int first, int second, int third) {
        this->num = num;
        this->first = first;
        this->second = second;
        this->third = third;
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }

    float average () {
        return (float) (first + second + third) / 3;
    }

    void print() {
        cout << "Player: " << name << " " << surname << " with number: " << num << " has " << average() << " points on average\n";
    }
};

int main () {
    char name[20], surname[20];
    int number, first, second, third;

    cin >> name >> surname >> number >> first >> second >> third;

    BasketballPlayer bp(name, surname, number, first, second, third);

    bp.print();
}