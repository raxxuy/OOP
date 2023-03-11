#include <iostream>
#include <cstring>
using namespace std;

enum Extension {
    txt, pdf, exe
};

class File {
private:
    char *name;
    Extension tip;
    char *owner;
    int size;
    void copy (const File &f) {
        tip = f.tip;
        size = f.size;
        name = new char[strlen(f.name) + 1];
        owner = new char[strlen(f.owner) + 1];
        strcpy(name, f.name);
        strcpy(owner, f.owner);
    }
public:
    File (const char *name = "", const char *owner = "", int size = 0, Extension tip = txt) {
        this->tip = tip;
        this->size = size;
        this->name = new char[strlen(name) + 1];
        this->owner = new char[strlen(owner) + 1];
        strcpy(this->name, name);
        strcpy(this->owner, owner);
    }

    File (const File &f) {
        copy(f);
    }

    void print () {
        cout << "File name: " << name << "." << (tip == 0 ? "pdf" : tip == 1 ? "txt" : "exe") << "\nFile owner: " << owner << "\nFile size: " << size << endl;
    }

    bool equals (const File &f) {
        return (tip == f.tip && !strcmp(name, f.name) && !strcmp(owner, f.owner));
    }

    bool equalsType (const File &f) {
        return tip == f.tip;
    }

    File &operator = (const File &f) {
        if (this == &f) return *this;
        copy(f);
        return *this;
    }

    ~File () {
        delete [] name;
        delete [] owner;
    }
};

class Folder {
private:
    char *name;
    File *file;
    int files;
public:
    Folder (const char *name = "") {
        file = nullptr;
        files = 0;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void print () {
        cout << "Folder name: " << name << endl;
        for (int i = 0; i < files; i++) file[i].print();
    }

    void remove (const File &f) {
        for (int i = 0; i < files; i++) {
            if (file[i].equals(f)) {
                File *tmp = new File[files - 1];
                int tmp_files = 0;
                for (int j = 0; j < files; j++) {
                    if (j != i) {
                        tmp[tmp_files] = file[j];
                        tmp_files++;
                    }
                }

                files = tmp_files;
                file = new File[files];
                for (int j = 0; j < files; j++) file[j] = tmp[j];
                return;
            }
        }
    }

    void add (const File &f) {
        File *tmp = file;
        file = new File[files + 1];
        for (int i = 0; i < files; i++) file[i] = tmp[i];
        file[files++] = f;
    }

    ~Folder () {
        delete [] file;
        delete [] name;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}