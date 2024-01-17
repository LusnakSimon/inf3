
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;

class Hrac {
private :
    string meno;
    vector<string> karty;
    int pocetVyhier;
public :
    Hrac(string meno) {
        this->meno = meno;
        this->pocetVyhier = 0;
    }
    string getMeno() {
        return this->meno;
    }
    int getPocetVyhier() {
        return this->pocetVyhier;
    }
    void vyhral() {
        this->pocetVyhier++;
    }
    void setKarty(vector<string> karty) {
        this->karty = karty;
    }
    vector<string> getKarty() {
        return this->karty;
    }
    ~Hrac() {

    }
};

int najvyssiaKarta(string karta1, string karta2, string karta3, string karta4) {
    return max(max((int)karta1[0], (int)karta2[0]), max((int)karta3[0], (int)karta4[0]));
}


void vytvorKarty() {
    string pismena = "ABCD";
    string cisla = "12345678";
    string karta = "";
    vector<string> balicek;
    for (char ch : cisla) {
        karta += ch;
        for (char c : pismena) {
            karta += c;
            balicek.push_back(karta);
            karta = ch;
        }
        karta = "";
    }

    srand(time(0));
    random_shuffle(balicek.begin(), balicek.end());
    
    vector<Hrac> hraci;
    vector<string> mena = { "Peter", "Pavol", "Jozef", "Milan" };
    for (int i = 0; i < 4; i++) {
        Hrac hrac(mena.at(i));
        vector<string> deck(8);
        copy(balicek.begin() + i * 8, balicek.begin() + (i + 1) * 8, deck.begin());
        hrac.setKarty(deck);
        hraci.push_back(hrac);
    }

    for (int i = 0; i < 8; i++) {
        int vitaz = najvyssiaKarta(hraci.at(0).getKarty().at(i), hraci.at(1).getKarty().at(i), hraci.at(2).getKarty().at(i), hraci.at(3).getKarty().at(i));
        vector<Hrac> vitazi;
        for (Hrac h : hraci) {
            if ((int)h.getKarty().at(i)[0] == vitaz) {
                vitazi.push_back(h);
            }
        }
        cout << hraci.at(0).getKarty().at(i) << " " << hraci.at(1).getKarty().at(i)
            << " " << hraci.at(2).getKarty().at(i) << " " << hraci.at(3).getKarty().at(i) << " ";
        if (vitazi.size() != 1) {
            char min = 'E';
            for (Hrac h : vitazi) {
                if (h.getKarty().at(i)[1] < min) {
                    min = h.getKarty().at(i)[1];
                }
            }
            string neger;
            for (Hrac h : vitazi) {
                if (h.getKarty().at(i)[1] == min) {
                    neger = h.getMeno();
                }
            }
            for (int i = 0; i < 4; i++) {
                if (hraci.at(i).getMeno().compare(neger) == 0) {
                    cout << ": " << hraci.at(i).getMeno() << " " << hraci.at(i).getKarty().at(i) << " ";
                    hraci.at(i).vyhral();
                }
            }
        }
        else {
            cout << ": " << vitazi.at(0).getMeno() << " " << vitazi.at(0).getKarty().at(i) << " ";
            string negro = vitazi.at(0).getMeno();
            for (int i = 0; i < 4; i++) {
                if (hraci.at(i).getMeno().compare(negro) == 0) {
                    hraci.at(i).vyhral();
                }
            }
        }
        cout << endl;
    }

    cout << "Vysledok :" << endl;
    
    for (Hrac h : hraci) {
        //h.vyhral();
        cout << h.getMeno() << ": " << h.getPocetVyhier() << endl;
    }



}


int main()
{
    vytvorKarty();
}

