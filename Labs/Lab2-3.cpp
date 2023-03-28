#include <iostream>
#include <cstring>
using namespace std;

class Country {
private:
    char name[100];
    char capital[100];
    double area;
    double population;
public:
    Country (const char *name = "", const char *capital = "", double area = 0, double population = 0) {
        this->area = area;
        this->population = population;
        strcpy(this->name, name);
        strcpy(this->capital, capital);
    }

    double getArea () {
        return area;
    }

    void setName (const char *nm) {
        strcpy(name, nm);
    }

    void setCapital (const char *cp) {
        strcpy(capital, cp);
    }

    void setArea (double ar) {
        area = ar;
    }

    void setPopulation (double pu) {
        population = pu;
    }

    void display () {
        cout << "Country: " << name << endl;
        cout << "Capital: " << capital << endl;
        cout << "Area: " << area << endl;
        cout << "Population: " << population << endl;
    }

    ~Country () = default;
};

void sortCountries (Country *countries, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (countries[i].getArea() < countries[j].getArea()) {
                Country tmp = countries[i];
                countries[i] = countries[j];
                countries[j] = tmp;
            }
        }
    }

    for (int i = 0; i < n; i++) countries[i].display();
}

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> capital;
        cin >> area;
        cin>>population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> capital;
    cin >> area;
    cin>>population;
    countries[n-1].setName(name);
    countries[n-1].setCapital(capital);
    countries[n-1].setArea(area);
    countries[n-1].setPopulation(population);

    cout<<"-->Testing set methods and display()"<<endl;
    countries[n-1].display();
    cout<<endl;

    cout<<"-->Testing sortCountries()"<<endl;
    sortCountries(countries,n);
    return 0;
}