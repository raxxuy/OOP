#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa {
protected:
    char coach[100];
    int goals[10];
public:
    FudbalskaEkipa (const char *coach = "", const int *goals = {}) {
        strcpy(this->coach, coach);
        for (int i = 0; i < 10; i++) this->goals[i] = goals[i];
    }

    virtual int uspeh () = 0;

    bool operator > (FudbalskaEkipa &fe) {
        return uspeh() > fe.uspeh();
    }

    FudbalskaEkipa &operator += (int goal) {
        for (int i = 0; i < 9; i++) goals[i] = goals[i + 1];
        goals[9] = goal;
        return *this;
    }
};

class Klub : public FudbalskaEkipa {
private:
    char *name;
    int medals;
public:
    Klub (const char *coach = "", const int *goals = {}, const char *name = "", int medals = 0) : FudbalskaEkipa(coach, goals) {
        this->medals = medals;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    int uspeh () override {
        int points = 0;

        for (auto & goal : goals) points += goal * 3;
        return points + medals * 1000;
    }

    friend ostream &operator << (ostream &out, Klub &k) {
        return out << k.name << endl << k.coach << endl << k.uspeh() << endl;
    }
};

class Reprezentacija : public FudbalskaEkipa {
private:
    char *country;
    int events;
public:
    Reprezentacija (const char *coach = "", const int *goals = {}, const char *country = "", int events = 0) : FudbalskaEkipa(coach, goals) {
        this->events = events;
        this->country = new char[strlen(country) + 1];
        strcpy(this->country, country);
    }

    int uspeh () override {
        int points = 0;

        for (auto & goal : goals) points += goal * 3;
        return points + events * 50;
    }

    friend ostream &operator << (ostream &out, Reprezentacija &r) {
        return out << r.country << endl << r.coach << endl << r.uspeh() << endl;
    }
};

ostream &operator << (ostream &out, FudbalskaEkipa &e) {
    if (dynamic_cast<Klub *>(&e)) return out << *dynamic_cast<Klub *>(&e);
    else return out << *dynamic_cast<Reprezentacija *>(&e);
}

void najdobarTrener (FudbalskaEkipa **teams, int numTeams) {
    int index = 0;

    for (int i = 1; i < numTeams; i++) if (*teams[i] > *teams[index]) index = i;
    cout << *teams[index];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}