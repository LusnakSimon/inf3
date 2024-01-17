

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
struct Lyziar {
    string meno;
    int cas1;
    int cas2;
    Lyziar() {
        this->meno = "";
        this->cas1 = 0;
        this->cas2 = 0;
    }
    Lyziar(string meno, int cas1, int cas2) {
        this->meno = meno;
        this->cas1 = cas1;
        this->cas2 = cas2;
    }
};

bool porovnaj(Lyziar lyziar1, Lyziar lyziar2) {
    return lyziar1.cas1 < lyziar2.cas1;
}

bool porovnaj2(Lyziar lyziar1, Lyziar lyziar2) {
    return lyziar1.cas2 < lyziar2.cas2;
}

bool porovnaj3(Lyziar lyziar1, Lyziar lyziar2) {
    return (lyziar1.cas1 + lyziar1.cas2) < (lyziar2.cas1 + lyziar1.cas2);
}

string casMinutySekundy(int cas) {
    string minuty = to_string(cas / 60);
    string sekundy = to_string(cas % 60);
    if (minuty.size() == 1) {
        string temp = minuty;
        minuty = "0" + temp;
    }
    if (sekundy.size() == 1) {
        string temp = sekundy;
        sekundy = "0" + temp;
    }
    return minuty + ":" + sekundy;
}



int main()
{
    ifstream inputFile("lyziari.txt");
    if (!inputFile.is_open()) {
        cerr << "chyba";
    }
    vector<Lyziar> lyziari;
    string meno;
    string priezvisko;
    srand(time(0));
    while (inputFile >> meno >> priezvisko) {
        int cas1 = rand() % 21 + 60;
        int cas2 = rand() % 21 + 60;

        lyziari.push_back(Lyziar((meno + " " + priezvisko), cas1, cas2));
    }
    sort(lyziari.begin(), lyziari.end(), porovnaj);
    for (int i = 0; i < lyziari.size(); i++) {
        cout << lyziari.at(i).meno << " " << casMinutySekundy(lyziari.at(i).cas1) << ", ";
    }
    cout << endl;
    sort(lyziari.begin(), lyziari.end(), porovnaj2);
    for (int i = 0; i < lyziari.size(); i++) {
        cout << lyziari.at(i).meno << " " << casMinutySekundy(lyziari.at(i).cas2) << ", ";
    }
    cout << endl;
    sort(lyziari.begin(), lyziari.end(), porovnaj3);
    for (int i = 0; i < lyziari.size(); i++) {
        cout << lyziari.at(i).meno << " " << casMinutySekundy(lyziari.at(i).cas1 + lyziari.at(i).cas2) << ", ";
    }


}


