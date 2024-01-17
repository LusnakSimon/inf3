
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

void zakoduj(string meno, string datum) {
    char tabulka[27];
    tabulka[26] = 32;
    char kodovanaTabulka[27];
    kodovanaTabulka[26] = 32;
    int a = 65;
    for (int i = 0; i < 26; i++) {
        tabulka[i] = a;
        kodovanaTabulka[i] = a;
        a++;
    }
    int den = 0;
    int mesiac = 0;
    int rok = 0;
    int counter = 0;
    string cislo;
    for (char ch : datum) {
        if (counter == 2) {
            den = stoi(cislo);
            cislo = "";
        }
        if (counter == 5) {
            mesiac = stoi(cislo);
            cislo = "";

        }
        if (ch != '.') {
            cislo += ch;
        }
        counter++;

    }
    rok = stoi(cislo);
    srand(rok * 10000 + mesiac * 100 + den);
    random_shuffle(begin(kodovanaTabulka), end(kodovanaTabulka));
    string kodovaneMeno;
    for (char ch : meno) {
        for (int i = 0; i < 27; i++) {
            if (ch == tabulka[i]) {
                kodovaneMeno += kodovanaTabulka[i];
            }
        }
    }
    cout << meno << " " << kodovaneMeno << endl;
    ofstream outputFile("vystup.txt", ios::app);
    if (outputFile.is_open()) {
        for (int i = 0; i < 27; i++) {
            outputFile << i << ". " << tabulka[i] << " - " << kodovanaTabulka[i] << endl;
        }
        outputFile << endl;
        outputFile.close();
    }
    else {
        cerr << "nigga";
    }
}

void nacitaj() {
    ifstream inputFile("zoznam.txt");
    if (inputFile.is_open()) {
        vector<string> riadky;
        vector<string> mena;
        vector<string> datumy;
        string line;
        for (line; getline(inputFile, line);) {
            riadky.push_back(line);
        }
        int medzera;
        string meno;
        string datum;
        bool jeMeno;
        for (int i = 0; i < riadky.size(); i++) {
            medzera = 0;
            meno = "";
            datum = "";
            jeMeno = true;
            for (char ch : riadky.at(i)) {
                if (jeMeno) {
                    if (ch == ' ') {
                        medzera++;
                    }
                    if (medzera == 2) {
                        jeMeno = false;
                        medzera++;
                    }
                    if (medzera < 3) {
                        meno += ch;
                    }
                    continue;
                }
                if (!jeMeno) {
                    datum += ch;
                }
            }
            mena.push_back(meno);
            datumy.push_back(datum);
        }
        for (int i = 0; i < mena.size(); i++) {
            zakoduj(mena.at(i), datumy.at(i));
        }
        
    }
    else {
        cerr << "niga";
    }
    
    

}



int main()
{ 
    nacitaj();
}

