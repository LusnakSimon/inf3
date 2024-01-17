#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Lyziar {
    string priezvisko;
    string meno;
    int pocetPretekov = 0;
    int pocetBodov = 0;
    double priemer = 0.00;
    int* umiestnenia = nullptr;
};

void zapisDoSuboru(const vector<Lyziar>& lyziari, string nazovSuboru) {
    ofstream vystupnySubor(nazovSuboru);
    if (vystupnySubor.is_open()) {
        for (int i = 0; i < lyziari.size(); i++) {
            vystupnySubor << lyziari.at(i).priezvisko << " " << lyziari.at(i).meno
                << " " << lyziari.at(i).pocetBodov << " "
                << lyziari.at(i).pocetPretekov << " " 
                << fixed << setprecision(2) << lyziari.at(i).priemer
                << " - [" << lyziari.at(i).pocetPretekov << "] ";
            for (int j = 0; j < lyziari.at(i).pocetPretekov; j++) {
                vystupnySubor << lyziari.at(i).umiestnenia[j] << " ";
            }
            vystupnySubor << endl;
        }
    } 
    else {
        cerr << "chybaaaa";
    }
    vystupnySubor.close();
    
}

void vypisDoKonzoly(const vector<Lyziar>& lyziari) {
    for (int i = 0; i < lyziari.size(); i++) {
        cout << lyziari.at(i).priezvisko << " " << lyziari.at(i).meno
            << " " << lyziari.at(i).pocetBodov << " "
            << lyziari.at(i).pocetPretekov << " "
            << fixed << setprecision(2) << lyziari.at(i).priemer
            << " - [" << lyziari.at(i).pocetPretekov << "] ";
        for (int j = 0; j < lyziari.at(i).pocetPretekov; j++) {
            cout << lyziari.at(i).umiestnenia[j] << " ";
        }
        cout << endl;
    }
}

bool porovnajLyziarov(const Lyziar& a, const Lyziar& b) {
    return a.pocetBodov > b.pocetBodov;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "niga";
    }
    vector<Lyziar> lyziari;
    srand(time(nullptr));
    ifstream inputFile(argv[1]);
    if (inputFile.is_open()) {
        string priezvisko;
        string meno;
        int pocetBodov = 0;
        int pocetPretekov = 0;
        double priemer = 0.00;

        while (inputFile >> priezvisko >> meno >> pocetPretekov) {
            Lyziar lyziar;
            lyziar.priezvisko = priezvisko;
            lyziar.meno = meno;
            lyziar.pocetPretekov = pocetPretekov;
            lyziar.umiestnenia = new int[pocetPretekov];
            for (int i = 0; i < pocetPretekov; i++) {
                lyziar.umiestnenia[i] = rand() % 30 + 1;
                lyziar.priemer += lyziar.umiestnenia[i];
                lyziar.pocetBodov += 30 - lyziar.umiestnenia[i] - 1;
            }
            lyziar.priemer /= pocetPretekov;
            lyziari.push_back(lyziar);
        }
    }
    else {
        cerr << "chybaaa chrapa";
    }
    inputFile.close();

    sort(lyziari.begin(), lyziari.end(), porovnajLyziarov);
    vypisDoKonzoly(lyziari);
    zapisDoSuboru(lyziari, "negus.txt");
    for (int i = 0; i < lyziari.size(); i++) {
        delete[] lyziari.at(i).umiestnenia;
    }
}



