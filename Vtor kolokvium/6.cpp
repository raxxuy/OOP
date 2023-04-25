#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame {
private:
    char *exception;
public:
    ExistingGame (const char *exception = "") {
        this->exception = new char[strlen(exception) + 1];
        strcpy(this->exception, exception);
    }

    void message () {
        cout << exception << endl;
    }
};

class Game {
protected:
    char name[100];
    float price;
    bool onSale;
public:
    Game (const char *name = "", float price = 0.0, bool onSale = false) {
        this->price = price;
        this->onSale = onSale;
        strcpy(this->name, name);
    }

    virtual double getPrice () {
        return (onSale ? price * 0.3 : price);
    }

    bool operator == (const Game &g) {
        return not strcmp(name, g.name);
    }

    friend ostream &operator << (ostream &out, Game &g) {
        return out << "Game: " << g.name << ", regular price: $" << g.price << (g.onSale ? ", bought on sale" : "") << endl;
    }

    friend istream &operator >> (istream &in, Game &g) {
        in.get();
        in.getline(g.name, 100);
        in >> g.price >> g.onSale;

        return in;
    }
};

class SubscriptionGame : public Game {
private:
    float monthlyFee;
    int month;
    int year;
public:
    SubscriptionGame (const char *name = "", float price = 0.0, bool onSale = false, float monthlyFee = 0.0, int month = 0, int year = 0) : Game(name, price, onSale) { //, year(year), month(month), monthlyFee(monthlyFee)
        this->year = year;
        this->month = month;
        this->monthlyFee = monthlyFee;
    }

    double getPrice () override {
        return Game::getPrice() + (double) (year < 2018 ? (17 - month + (2017 - year) * 12) : 5 - month) * monthlyFee;
    }

    friend ostream &operator << (ostream &out, SubscriptionGame &sg) {
        out << "Game: " << sg.name << ", regular price: $" << sg.price << (sg.onSale ? ", bought on sale" : "");
        out << ", monthly fee: $" << sg.monthlyFee << ", purchased: " << sg.month << "-" << sg.year << endl;

        return out;
    }

    friend istream &operator >> (istream &in, SubscriptionGame &sg) {
        in.get();
        in.getline(sg.name, 100);
        in >> sg.price >> sg.onSale >> sg.monthlyFee >> sg.month >> sg.year;

        return in;
    }
};

class User {
private:
    char name[100];
    Game **games;
    int numGames;
public:
    User (const char *name = "") {
        games = nullptr;
        numGames = 0;
        strcpy(this->name, name);
    }

    User &operator += (Game &g) {

        for (int i = 0; i < numGames; i++) if (*games[i] == g) throw ExistingGame("The game is already in the collection");

        Game **tmp = games;
        games = new Game*[numGames + 1];
        for (int i = 0; i < numGames; i++) games[i] = tmp[i];
        games[numGames++] = &g;

        return *this;
    }

    double total_spent () {
        double total = 0;

        for (int i = 0; i < numGames; i++) total += games[i]->getPrice();
        return total;
    }

    friend ostream &operator << (ostream &out, User &u) {
        out << endl << "User: " << u.name << endl;

        for (int i = 0; i < u.numGames; i++) {
            if (dynamic_cast<SubscriptionGame *>(u.games[i])) out << "- " << *dynamic_cast<SubscriptionGame *>(u.games[i]);
            else out << "- " << *u.games[i];
        }

        return out << endl;
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}