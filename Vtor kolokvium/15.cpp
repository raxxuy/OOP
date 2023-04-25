#include <iostream>
#include <cstring>
using namespace std;

class BadInputException {
private:
    char *exception;
public:
    BadInputException (const char *exception = "") {
        this->exception = new char[strlen(exception) + 1];
        strcpy(this->exception, exception);
    }

    void message () {
        cout << exception << endl;
    }
};

class StudentKurs {
protected:
    char name[30];
    int grade;
    bool theory;
    static int MAX;
public:
    StudentKurs (const char *name = "", int grade = 0){
        theory = false;
        this->grade = grade;
        strcpy(this->name, name);
    }

    char *getName () {
        return name;
    }

    bool getDaliUsno () {
        return theory;
    }

    virtual int ocenka () {
        if (grade > MAX) grade = MAX;
        return grade;
    }

    static void setMAX (int max) {
        MAX = max;
    }

    friend ostream &operator << (ostream &out, StudentKurs &sk) {
        return out << sk.name << " --- " << sk.ocenka() << endl;
    }
};

int StudentKurs::MAX = 10;

class StudentKursUsno : public StudentKurs {
private:
    char *gradeDesc;
public:
    StudentKursUsno (const char *name, int grade) : StudentKurs (name, grade) {
        theory = true;
    }

    int ocenka () override {
        int finalGrade = grade;
        if (not strcmp(gradeDesc, "odlicen")) finalGrade += 2;
        if (not strcmp(gradeDesc, "dobro")) finalGrade += 1;
        if (not strcmp(gradeDesc, "losho")) finalGrade -= 1;

        if (finalGrade > MAX) finalGrade = MAX;
        return finalGrade;
    }

    StudentKursUsno &operator += (const char *description) {
        for (int i = 0; i < strlen(description); i++) if (not isalpha(description[i])) throw BadInputException("Greshna opisna ocenka");

        gradeDesc = new char[strlen(description) + 1];
        strcpy(gradeDesc, description);

        return *this;
    }

    ~StudentKursUsno () {
        delete [] gradeDesc;
    }
};

class KursFakultet{
private:
    char name[30];
    StudentKurs *students[20];
    int numStudents;
    const static int MINOCENKA = 6;
public:
    KursFakultet (char *name, StudentKurs **students, int numStudents) {
        this->numStudents = numStudents;
        strcpy(this->name,name);

        for (int i = 0; i < numStudents; i++){
            if (students[i]->getDaliUsno()) this->students[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(students[i]));
            else this->students[i] = new StudentKurs(*students[i]);
        }
    }

    void pecatiStudenti () {
        cout << "Kursot " << name << " go polozile:" << endl;
        for (int i = 0; i < numStudents; i++) if ((*students[i]).ocenka() >= MINOCENKA) cout << *students[i];
    }

    void postaviOpisnaOcenka (char *studentName, char *gradeDesc) {
        for (int i = 0; i < numStudents; i++)
            if (not strcmp((*students[i]).getName(), studentName) and (*students[i]).getDaliUsno()) *dynamic_cast<StudentKursUsno *>(students[i]) += gradeDesc;
    }

    ~KursFakultet () {
        for (int i = 0; i < numStudents; i++) delete students[i];
    }
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        try {
            cin>>ime>>opisna;
            programiranje.postaviOpisnaOcenka(ime,opisna);
        } catch (BadInputException &e) {
            e.message();

            int tmpCount = 0, tmpCount2 = 0;
            for (int j = 0; j < strlen(opisna); j++) if (isalpha(opisna[j])) tmpCount++;

            char *tmp = new char[tmpCount];
            for (int j = 0; j < strlen(opisna); j++) if (isalpha(opisna[j])) tmp[tmpCount2++] = opisna[j];

            tmp[tmpCount] = '\0';
            programiranje.postaviOpisnaOcenka(ime,tmp);
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}