

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

struct Krajina {
    string nazov;
    int pocetBodov;
    vector<string> protivnici;
    Krajina() {
        this->pocetBodov = 0;
        this->nazov = "";
    }
    Krajina(string nazov) {
        this->pocetBodov = 0;
        this->nazov = nazov;
    }
    void vyhra() {
        this->pocetBodov += 3;
    }
    void remiza() {
        this->pocetBodov++;
    }

};


int generator(int cislo1, int cislo2) {
    return time(0) * (cislo1 + 1) * (cislo2 + 1);
}

int main()
{
    ifstream inputFile("krajiny.txt");
    if (inputFile.is_open()) {

        vector<Krajina> krajiny;
        string krajina;
        while (inputFile >> krajina) {
            krajiny.push_back(Krajina(krajina));
        }
        for (int i = 0; i < krajiny.size(); i++) {
            for (int j = 0; j < krajiny.size(); j++) {
                if (krajiny.at(i).nazov.compare(krajiny.at(j).nazov) == 0) {
                    continue;
                }
                if (find(krajiny.at(i).protivnici.begin(), krajiny.at(i).protivnici.end(), krajiny.at(j).nazov) == krajiny.at(i).protivnici.end()) {
                    krajiny.at(i).protivnici.push_back(krajiny.at(j).nazov);
                    krajiny.at(j).protivnici.push_back(krajiny.at(i).nazov);
                    srand(generator(i, j));
                    int vysledok1 = rand() % 7;
                    srand(generator(i + 1, j + 1));
                    int vysledok2 = rand() % 7;
                    if (vysledok1 > vysledok2) {
                        krajiny.at(i).vyhra();
                    }
                    if (vysledok1 < vysledok2) {
                        krajiny.at(j).vyhra();
                    }
                    if (vysledok1 == vysledok2) {
                        krajiny.at(i).remiza();
                        krajiny.at(j).remiza();
                    }
                    cout << krajiny.at(i).nazov << " : " << krajiny.at(j).nazov << " "
                        << vysledok1 << " : " << vysledok2 << endl;
                }
            }
        }
        cout << endl;
        for (int c = 0; c < krajiny.size(); c++) {
            cout << krajiny.at(c).nazov << ": " << krajiny.at(c).pocetBodov << endl;
        }
    }
    else {
        cerr << "dobree";
    }
}

