#include <iostream>
#include <cstring>
using namespace std;

class Film {
private:
    char name[100];
    double rating;
    double revenue;
public:
    Film (const char *name = "", double rating = 0, double revenue = 0) {
        this->rating = rating;
        this->revenue = revenue;
        strcpy(this->name, name);
    }

    double getRevenue () {
        return revenue;
    }

    void setName (const char *nm) {
        strcpy(name, nm);
    }

    void setRating (double rt) {
        rating = rt;
    }

    void setRevenue (double rev) {
        revenue = rev;
    }

    void display () {
        cout << "Name of film: " << name << endl;
        cout << "Rating: " << rating << endl;
        cout << "Revenue: " << revenue << endl;
    }

    ~Film () = default;
};

void printMostPopularFilm (Film *films, int n) {
    Film best;

    for (int i = 0; i < n; i++) if (best.getRevenue() < films[i].getRevenue()) best = films[i];

    best.display();
}

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> rating;
    cin >> revenue;
    films[n-1].setName(name);
    films[n-1].setRating(rating);
    films[n-1].setRevenue(revenue);

    cout<<"-->Testing set methods and display()"<<endl;
    films[n-1].display();
    cout<<endl;

    cout<<"-->Testing printMostPopularFilm()"<<endl;
    printMostPopularFilm(films , n);
    return 0;
}