
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;
//A
//Simon Lusnak
//5ZYI22
//Tavac


class Pretekar {
private:
    string oznacenie;
    int body;
    vector<int> bodyZaKolo;
    bool vyradeny;
    int poradoveCislo;
public:
    Pretekar() {
        this->oznacenie = "";
        this->body = 0;
        this->vyradeny = false;
        this->poradoveCislo = 0;
    }
    Pretekar(int poradoveCislo) {
        this->oznacenie = "P" + to_string(poradoveCislo);
        this->body = 0;
        this->vyradeny = false;
        this->poradoveCislo = poradoveCislo;
    }
    int getBody() {
        return this->body;
    }
    void pridajBody(int body) {
        this->body += body;
    }
    string getOznacenie() {
        return this->oznacenie;
    }
    void pridajBodyZaKolo(int body) {
        this->bodyZaKolo.push_back(body);
    }
    void vypisBodyZaKolo() {
        for (int i = 0; i < this->bodyZaKolo.size(); i++) {
            cout << " " << bodyZaKolo.at(i) << " ";
        }
    }
    void vyrad() {
        this->vyradeny = true;
    }
    bool jeVyradeny() {
        return this->vyradeny;
    }
    void vymazBodyZaKolo() {
        this->bodyZaKolo.clear();
    }
    int getPoradoveCislo() {
        return this->poradoveCislo;
    }
    ~Pretekar() {}
};


bool porovnaj(Pretekar pretekar1, Pretekar pretekar2) {
    if (pretekar1.getBody() == pretekar2.getBody()) {
        return pretekar1.getPoradoveCislo() > pretekar2.getPoradoveCislo();
    }
    return pretekar1.getBody() > pretekar2.getBody();
}

void zacniSutaz() {
    srand(time(0));
    int pocetSutaziacich = rand() % 26 + 5;
    vector<Pretekar> pretekari;
    for (int i = 1; i < pocetSutaziacich + 1; i++) {
        pretekari.push_back(Pretekar(i));
    }
    for (int i = 0; i < 5; i++) {
        cout << "kolo " << i + 1 << ":" << endl;
        for (int j = 0; j < pretekari.size(); j++) {
            if (pretekari.at(j).jeVyradeny()) {
                continue;
            }
            for (int k = 0; k < 5; k++) {
                int vystrel = rand() % 11;
                pretekari.at(j).pridajBody(vystrel);
                pretekari.at(j).pridajBodyZaKolo(vystrel);
            }
        }
        sort(pretekari.begin(), pretekari.end(), porovnaj);
        vector<string> postup;
        cout << "postupili:" << endl;
        for (int m = 0; m < 5 - i; m++) {
            postup.push_back(pretekari.at(m).getOznacenie());
            cout << pretekari.at(m).getOznacenie();
            pretekari.at(m).vypisBodyZaKolo();
            cout << ": " << pretekari.at(m).getBody() << endl;
        }
        cout << endl;
        if (postup.size() == 1) {
            cout << "vitaz : " << endl << pretekari.at(0).getOznacenie() << " " << pretekari.at(0).getBody();
            break;
        }
        cout << "Vypadli:" << endl;
        for (int c = 0; c < pretekari.size(); c++) {
            if (pretekari.at(c).jeVyradeny()) {
                continue;
            }
            if (find(postup.begin(), postup.end(), pretekari.at(c).getOznacenie()) == postup.end()) {
                pretekari.at(c).vyrad();
                cout << pretekari.at(c).getOznacenie();
                pretekari.at(c).vypisBodyZaKolo();
                cout << ": " << pretekari.at(c).getBody() << endl;
            }
            pretekari.at(c).vymazBodyZaKolo();
        }
        cout << endl;
        
        
    }


}

int main()
{
    zacniSutaz();
    return 0;
}

