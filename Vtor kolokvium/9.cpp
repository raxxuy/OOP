#include <iostream>
#include <cstring>
using namespace std;

class Exception {
private:
    char *exception;
public:
    Exception (const char *exception = "") {
        this->exception = new char[strlen(exception) + 1];
        strcpy(this->exception, exception);
    }

    void message () {
        cout << exception << endl;
    }
};

class Trud {
private:
    char type;
    int year;
public:
    Trud (char type = 0, int year = 0) {
        this->type = type;
        this->year = year;
    }

    friend istream &operator >> (istream &in, Trud &t) {
        return in >> t.type >> t.year;
    }

    friend class PhDStudent;
};

class Student {
private:
    char name[30];
    int index;
    int year;
    int grades[50];
    int subjects;
public:
    Student (const char *name = "", int index = 0, int year = 0, const int *grades = {}, int subjects = 0) {
        this->year = year;
        this->index = index;
        this->subjects = subjects;
        for (int i = 0; i < subjects; i++) this->grades[i] = grades[i];
        strcpy(this->name, name);
    }

    int getIndex () {
        return index;
    }

    int getYear () {
        return year;
    }

    virtual double rang () {
        double sum = 0;

        for (int i = 0; i < subjects; i++) sum += grades[i];
        return sum / subjects;
    }

    friend ostream &operator << (ostream &out, Student &s) {
        return out << s.index << " " << s.name << " " << s.year << " " << s.rang() << endl;
    }
};

class PhDStudent : public Student {
private:
    Trud *labors;
    int numLabors;
    static int C;
    static int J;
public:
    PhDStudent (const char *name, int index, int year, const int *grades, int subjects, Trud *labors = nullptr, int numLabors = 0) :
    Student(name, index, year, grades, subjects) {
        this->numLabors = numLabors;
        this->labors = new Trud[numLabors];
        for (int i = 0; i < numLabors; i++) {
            try {
                if (labors[i].year < getYear()) throw Exception("Ne moze da se vnese dadeniot trud");
                this->labors[i] = labors[i];
            } catch (Exception &e) {
                e.message();
            }
        }
    }

    static void setC (int c) {
        PhDStudent::C = c;
    }

    static void setJ (int j) {
        PhDStudent::J = j;
    }

    double rang () override {
        double total = 0;

        for (int i = 0; i < numLabors; i++) {
            if (labors[i].type == 'j' || labors[i].type == 'J') total += J;
            else if (labors[i].type == 'c' || labors[i].type == 'C') total += C;
        }

        return Student::rang() + total;
    }

    PhDStudent &operator += (Trud &t) {
        if (t.year < getYear()) throw Exception("Ne moze da se vnese dadeniot trud");

        Trud *tmp = labors;
        labors = new Trud[numLabors + 1];
        for (int i = 0; i < numLabors; i++) labors[i] = tmp[i];
        labors[numLabors++] = t;

        return *this;
    }
};

int PhDStudent::C = 1, PhDStudent::J = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool found = false;

        for (int i = 0; i < m; ++i) if (dynamic_cast<PhDStudent *>(niza[i]) && niza[i]->getIndex() == indeks) {
            *dynamic_cast<PhDStudent *>(niza[i]) += t;
            found = true;
        }

        if (!found) cout << "Ne postoi PhD student so indeks " << indeks << endl;

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        bool found = false;

        for (int i = 0; i < m; ++i) if (dynamic_cast<PhDStudent *>(niza[i]) && niza[i]->getIndex() == indeks) {
            *dynamic_cast<PhDStudent *>(niza[i]) += t;
            found = true;
        }

        if (!found) cout << "Ne postoi PhD student so indeks " << indeks << endl;

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try {
            for (int i = 0; i < m; ++i) if (dynamic_cast<PhDStudent *>(niza[i]) && niza[i]->getIndex() == indeks) *dynamic_cast<PhDStudent *>(niza[i]) += t;
        } catch (Exception &e) {
            e.message();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}