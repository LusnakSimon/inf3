
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>

struct Lyziar {

    std::string priezvisko;
    std::string meno;
    int pocetPretekov = 0;
    int pocetBodov = 0;
    double priemer = 0.00;
    int* umiestnenia;

    Lyziar() : pocetPretekov(0), pocetBodov(0), priemer(0.0), umiestnenia(nullptr) {}

    ~Lyziar() {

        delete[] umiestnenia;
    }
};

void nacitanieSoSuboru(const std::string nazovSuboru, std::vector<Lyziar>& lyziari) {
    
    std::ifstream vstupnySubor(nazovSuboru);

    if (vstupnySubor.is_open()) {
        
        std::string priezvisko;
        std::string meno;
        int pocetPretekov = 0;
        int pocetBodov = 0;
        double priemer = 0.00;

        while (vstupnySubor >> priezvisko >> meno >> pocetPretekov) {
            
            Lyziar lyziar;
            lyziar.priezvisko = priezvisko;
            lyziar.meno = meno;
            lyziar.pocetPretekov = pocetPretekov;
            lyziar.umiestnenia = new int[pocetPretekov];

            for (int i = 0; i < pocetPretekov; i++) {
                
                lyziar.umiestnenia[i] = rand() % 30 + 1;
                priemer += lyziar.umiestnenia[i];
                pocetBodov += 30 - lyziar.umiestnenia[i] - 1;

            }

            lyziar.priemer = priemer / pocetPretekov;
            lyziar.pocetBodov = pocetBodov;

            lyziari.push_back(lyziar);

            priemer = 0;
            pocetBodov = 0;
        }
    }
    else {

        std::cerr << "subor sa nepodarilo otvorit";
    }

}

void vypisDoKonzoly(const std::vector<Lyziar>& lyziari) {

    for (const Lyziar& lyziar : lyziari) {

        std::cout << lyziar.priezvisko << " " << lyziar.meno
             << " " << lyziar.pocetBodov << " " << lyziar.pocetPretekov
             << " " << lyziar.priemer << " - [" << lyziar.pocetPretekov
             << "] ";

        for (int i = 0; i < lyziar.pocetPretekov; i++) {
            std::cout << lyziar.umiestnenia[i] << " ";
        }
        std::cout << std::endl;
    }
}

void zapisDoSuboru(const std::vector<Lyziar>& lyziari, const std::string nazovSuboru) {

    std::ofstream vystupnySubor(nazovSuboru);

    if (vystupnySubor.is_open()) {

        for (const Lyziar& lyziar : lyziari) {

            vystupnySubor << lyziar.priezvisko << " " << lyziar.meno
                << " " << lyziar.pocetBodov << " " << lyziar.pocetPretekov
                << " " << lyziar.priemer << " - [" << lyziar.pocetPretekov
                << "] ";

            for (int i = 0; i < lyziar.pocetPretekov; i++) {
                vystupnySubor << lyziar.umiestnenia[i] << " ";
            }
            vystupnySubor << std::endl;
        }
    }
    else {

        std::cerr << "subor sa nepodarilo otvorit";
    }

}

bool porovnajLyziarov(const Lyziar& prvyLyziar, const Lyziar& druhyLyziar) {

    return prvyLyziar.pocetBodov > druhyLyziar.pocetBodov;
}


int main(int argc, char* argv[])
{
    srand(time(nullptr));

    std::vector<Lyziar> lyziari;

    nacitanieSoSuboru(argv[1], lyziari);

    std::sort(lyziari.begin(), lyziari.end(), porovnajLyziarov);

    vypisDoKonzoly(lyziari);

    zapisDoSuboru(lyziari, "vystup.txt");

    return 0;
}
