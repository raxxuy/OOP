#include <iostream>
#include <cstring>
using namespace std;

class Book {
protected:
    char ISBN[20];
    char title[50];
    char author[50];
    float price;
public:
    Book (const char *ISBN = "", const char *title = "", const char *author = "", float price = 0.0) {
        this->price = price;
        strcpy(this->ISBN, ISBN);
        strcpy(this->title, title);
        strcpy(this->author, author);
    }

    void setISBN (const char *isbn) {
        strcpy(ISBN, isbn);
    }

    virtual double bookPrice () = 0;

    bool operator > (Book &b) {
        return bookPrice() > b.bookPrice();
    }

    friend ostream &operator << (ostream &out, Book &b) {
        return out << b.ISBN << ": " << b.title << ", " << b.author << " " << b.bookPrice() << endl;
    }

    virtual ~Book () = default;
};

class OnlineBook : public Book {
private:
    char *url;
    int size;
public:
    OnlineBook (const char *ISBN, const char *title, const char *author, float price, const char *url = "", int size = 0) : Book(ISBN, title, author, price) {
        this->size = size;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    double bookPrice () override {
        return (size > 20 ? price * 1.2 : price);
    }
};

class PrintBook : public Book {
private:
    float weight;
    bool inStock;
public:
    PrintBook (const char *ISBN, const char *title, const char *author, float price, float weight = 0.0, bool inStock = false) : Book(ISBN, title, author, price) {
        this->inStock = inStock;
        this->weight = weight;
    }

    double bookPrice () override {
        return (weight > 0.7 ? price * 1.15 : price);
    }
};

void mostExpensiveBook (Book** books, int numBooks) {
    int index = 0, online = 0, print = 0;

    for (int i = 1; i < numBooks; i++) if (*books[i] > *books[index]) index = i;

    for (int i = 0; i < numBooks; i++) {
        if (dynamic_cast<OnlineBook *>(books[i])) online++;
        else print++;
    }

    cout << "FINKI-Education\n"
            "Total number of online books: " << online <<
            "\nTotal number of print books: " << print <<
            "\nThe most expensive book is: \n";

    cout << *books[index];
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}