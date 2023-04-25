#include <iostream>
#include <cstring>
using namespace std;

class Image {
protected:
    char *name;
    char author[50];
    int width;
    int height;
public:
    Image (const char *name = "untitled", const char *author = "unknown", int width = 800, int height = 800) {
        this->width = width;
        this->height = height;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->author, author);
    }

    virtual long fileSize () {
        return width * height * 3;
    }

    bool operator > (Image &i) {
        return fileSize() > i.fileSize();
    }

    friend ostream &operator << (ostream &out, Image &i) {
        return out << i.name << " " << i.author << " " << i.fileSize() << endl;
    }

    virtual ~Image () {
        delete [] name;
    }
};

class TransparentImage : public Image {
protected:
    bool transparent;
public:
    TransparentImage (const char *name = "untitled", const char *author = "unknown", int width = 800, int height = 800, bool transparent = true) :
    Image(name, author, width, height), transparent(transparent) {}

    long fileSize () override {
        return (transparent ? width * height * 4 : 9 * width * height / 8);
    }
};

class Folder {
protected:
    char name[255];
    char author[50];
    Image *images[100];
    int numImages;
public:
    Folder (const char *name = "", const char *author = "unknown") {
        numImages = 0;
        strcpy(this->name, name);
        strcpy(this->author, author);
    }

    long folderSize () {
        long size = 0;

        for (int i = 0; i < numImages; i++) size += (*images[i]).fileSize();
        return size;
    }

    Image *getMaxFile () {
        int index = 0;

        for (int i = 1; i < numImages; i++) if (*images[i] > *images[index]) index = i;
        return images[index];
    }

    Folder &operator += (Image &i) {
        images[numImages++] = &i;
        return *this;
    }

    Image *operator [] (int index) {
        if (images[index]) return images[index];
        else return nullptr;
    }

    friend ostream &operator << (ostream &out, Folder &f) {
        out << f.name << " " << f.author << endl << "--" << endl;
        for (int i = 0; i < f.numImages; i++) out << (*f.images[i]);
        return out << "--" << endl << "Folder size: " << f.folderSize() << endl;
    }
};

Folder &max_folder_size (Folder *folders, int numFolders) {
    int index = 0;

    for (int i = 1; i < numFolders; i++) if (folders[i].folderSize() > folders[index].folderSize()) index = i;
    return folders[index];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for


        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};