


#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

class Kocka {
private:
    string farba;
    int cislo;
public:
    Kocka() {
        this->cislo = 0;
    }
    Kocka(string farba) {
        this->farba = farba;
        this->cislo = 0;
    }
    void hodKockou(int seed) {
        srand(time(0) + this->farba[0] + (seed + 1));
        this->cislo = rand() % 6 + 1;

    }
    int getCislo() {
        return this->cislo;
    }
    string getFarba() {
        return this->farba;
    }
    int getPriorita() {
        if (this->farba.compare("BIELA") == 0) {
            return 1;
        }
        if (this->farba.compare("MODRA") == 0) {
            return 2;
        }
        if (this->farba.compare("HNEDA") == 0) {
            return 3;
        }
        if (this->farba.compare("ZLATA") == 0) {
            return 4;
        }
        return 0;
    }
};

class Hrac {
private:
    string meno;
    Kocka kocka;
public:
    Hrac() {}
    Hrac(string meno) {
        this->meno = meno;
    }
    string getMeno() {
        return this->meno;
    }
    void setKocka(Kocka kocka) {
        this->kocka = kocka;
    }
    Kocka getKocka() {
        return this->kocka;
    }
    ~Hrac() {}
};

int najdiMaximum(int cislo1, int cislo2, int cislo3, int cislo4) {
    return max(max(cislo1, cislo2), max(cislo3, cislo4));
}

void simulujHru() {
    vector<string> farby = { "BIELA", "MODRA", "HNEDA", "ZLATA" };
    vector<Hrac> hraci = {Hrac("Peter"), Hrac("Jozef"), Hrac("Pavol"), Hrac("Milan")};
    vector<Kocka> kocky = {Kocka("BIELA"), Kocka("MODRA"), Kocka("HNEDA"), Kocka("ZLATA")};
    for (int i = 0; i < 10; i++) {
        srand(time(0) * (i + 1));
        random_shuffle(kocky.begin(), kocky.end());
        for (int j = 0; j < hraci.size(); j++) {
            kocky.at(j).hodKockou(i);
            hraci.at(j).setKocka(kocky.at(j));

            cout << hraci.at(j).getKocka().getCislo() << " "
                << hraci.at(j).getKocka().getFarba()
                << " - " << hraci.at(j).getMeno() << ", ";
        }
        int vitaz = najdiMaximum(kocky.at(0).getCislo(), kocky.at(1).getCislo(), kocky.at(2).getCislo(), kocky.at(3).getCislo());
        vector<Hrac> vitazi;
        for (int k = 0; k < hraci.size(); k++) {
            if (hraci.at(k).getKocka().getCislo() == vitaz) {
                vitazi.push_back(hraci.at(k));
            }
        }
        int minPriorita = 10;
        for (int m = 0; m < vitazi.size(); m++) {
            if (vitazi.at(m).getKocka().getPriorita() < minPriorita) {
                minPriorita = vitazi.at(m).getKocka().getPriorita();
            }
        }
        for (int n = 0; n < hraci.size(); n++) {
            if (hraci.at(n).getKocka().getPriorita() == minPriorita) {
                cout << " vitaz : " << hraci.at(n).getMeno()
                    << " - " << hraci.at(n).getKocka().getCislo()
                    << " " << hraci.at(n).getKocka().getFarba();
            }
        }

        cout << endl;

        
    }
    
}

int main()
{
    simulujHru();
}


