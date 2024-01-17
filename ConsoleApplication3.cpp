
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <iomanip>
struct Lyziar {
    std::string priezvisko;
    std::string meno;
    int pocetZapasov = 0;
    double priemer = 0.00;
    int pocetBodov = 0;
    int* umiestnenia;

    ~Lyziar() {
        delete[] umiestnenia;
    }
};

bool compareByAgeDescending(const Lyziar& a, const Lyziar& b) {
    return a.pocetBodov > b.pocetBodov;
}

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    std::vector<Lyziar> lyziari;

    std::ifstream inputFile(argv[1]);

    if (inputFile.is_open()) {
        std::string priezvisko;
        std::string meno;
        int pocetZapasov = 0;
        while (inputFile >> priezvisko >> meno >> pocetZapasov) {
            Lyziar lyziar;
            lyziar.priezvisko = priezvisko;
            lyziar.meno = meno;
            lyziar.pocetZapasov = pocetZapasov;
            lyziar.umiestnenia = new int[pocetZapasov];
            lyziari.push_back(lyziar);
        }
        
        int** umiestnenia = new int* [lyziari.size()];
        for (int i = 0; i < lyziari.size(); i++) {
            umiestnenia[i] = new int[lyziari.at(i).pocetZapasov];
            double priemer = 0;
            int pocetBodov = 0;
            for (int j = 0; j < lyziari.at(i).pocetZapasov; j++) {
                int poradie = rand() % 30 + 1;
                umiestnenia[i][j] = poradie;
                priemer += poradie;
                pocetBodov += 30 - poradie - 1;
                lyziari.at(i).umiestnenia[j] = poradie;
            }
            priemer /= lyziari.at(i).pocetZapasov;

            lyziari.at(i).priemer = priemer;
            lyziari.at(i).pocetBodov = pocetBodov;
        }
        std::sort(lyziari.begin(), lyziari.end(), compareByAgeDescending);
        std::ofstream outputFile("vysledky.txt");
        for (int i = 0; i < lyziari.size(); i++) {

            std::cout << lyziari.at(i).priezvisko << " "
                << lyziari.at(i).meno << " " << lyziari.at(i).pocetBodov
                << " " << lyziari.at(i).pocetZapasov << " "
                << std::fixed << std::setprecision(2) << lyziari.at(i).priemer
                << " - [" << lyziari.at(i).pocetZapasov << "] ";

            outputFile << lyziari.at(i).priezvisko << " "
                << lyziari.at(i).meno << " " << lyziari.at(i).pocetBodov
                << " " << lyziari.at(i).pocetZapasov << " "
                << std::fixed << std::setprecision(2) << lyziari.at(i).priemer
                << " - [" << lyziari.at(i).pocetZapasov << "] ";

            for (int j = 0; j < lyziari.at(i).pocetZapasov; j++) {
                std::cout << " " << lyziari.at(i).umiestnenia[j] << " ";
                outputFile << " " << lyziari.at(i).umiestnenia[j] << " ";
            }
            std::cout << std::endl;
            outputFile << std::endl;
        }

        outputFile.close();
        delete[] umiestnenia;
        
    }
}
