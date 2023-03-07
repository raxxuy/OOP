#include <iostream>
using namespace std;

class List {
private: // so treba da sodrzi
    int *num;
    int nums;
    void copy (const List &l) { // copy function za polesno
        nums = l.nums;
        num = new int[nums + 1];                            // isto kako so char pointer
        for (int i = 0; i < nums; i++) num[i] = l.num[i];   // se kopiraat broevite;
    }
public:
    List (const int *num = nullptr, int nums = 0) { // constructor
        this->nums = nums;
        this->num = new int[this->nums + 1];
        for (int i = 0; i < this->nums; i++) this->num[i] = num[i];
    }

    List (const List &l) { // copy-constructor
        copy(l);
    }

    int getNums () {
        return nums;
    }

    int sum () {
        int sum = 0;
        for (int i = 0; i < nums; i++) sum += num[i];
        return sum;
    }

    double average () {
        return (double) sum() / (double) nums;
    }

    void print () {
        cout << nums << ": ";
        for (int i = 0; i < nums; i++) cout << num[i] << " ";
        cout << "sum: " << sum() << " average: " << average() << endl;
    }

    List &operator = (const List &l) { // nes kako copy-constructorot
        if (this == &l) return *this;   // ako e istata lista
        delete [] num;                  // se brise pointerot
        copy(l);                        // se kopiraat rabotite
        return *this;
    }

    ~List () { // destructor
        delete [] num;
    };
};

class ListContainer {
private: // so treba da sodrzi
    List *list;
    int lists;
    int successful_attempts;
    int failed_attempts;
    void copy (const ListContainer &lc) { // copy function za ListContainer
        lists = lc.lists;
        successful_attempts = lc.successful_attempts;
        failed_attempts = lc.failed_attempts;
        list = new List[lists + 1];                             // you know already
        for (int i = 0; i < lists; i++) list[i] = lc.list[i];   // you know already
    }
public:
    ListContainer () { // default constructor
        list = nullptr; // initalizing pointer
        lists = 0;
        successful_attempts = 0;
        failed_attempts = 0;
    }

    ListContainer (const ListContainer &lc) { // copy-constructor
        copy(lc);
    }

    int sum () {
        int sum = 0;
        for (int i = 0; i < lists; i++) sum += list[i].sum();
        return sum;
    }

    double average () {
        int nums = 0;
        for (int i = 0; i < lists; i++) nums += list[i].getNums();
        return (double) sum() / nums;
    }

    void print () {
        if (!lists) cout << "The list is empty\n";
        else {
            for (int i = 0; i < lists; i++) {
                cout << "List number: " << i+1 << " List info: ";
                list[i].print();
            }
            cout << "Sum: " << sum() << " Average: " << average() << endl;
            cout << "Successful attempts: " << successful_attempts << " Failed attempts: " << failed_attempts << endl;
        }
    }

    void addNewList (List l) {
        for (int i = 0; i < lists; i++) if (list[i].sum() == l.sum()) { // proveruva ako se so isti sumi
            failed_attempts++;
            return;
        }

        List *tmp = list;                                   // za kopiranje
        list = new List[lists + 1];                         // se prosiruva pointerot so pravenje nov size
        for (int i = 0; i < lists; i++) list[i] = tmp[i];   // se kopiraat tmp listite na list pointerot
        list[lists] = l;                                    // nov list
        lists++;                                            // se zgolemuva brojot na listi
        successful_attempts++;                              // ako uspea da se addne nov list
    }

    ListContainer &operator = (const ListContainer &lc) { // isto nes
        if (this == &lc) return *this;  // ako e istiot container
        delete [] list;                 // se brise pointerot
        copy(lc);                       // se kopiraat rabotite
        return *this;
    }

    ~ListContainer () { // destructor
        delete [] list;
    };
};


// OD COURSES - ne od mene
int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}