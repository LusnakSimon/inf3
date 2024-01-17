
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char * argv[]) {

    int size = stoi(argv[1]);
    int rozsah = stoi(argv[2]);
    int* pole = new int[size];

    ofstream file("cisla.txt");
    srand(time(nullptr));
    for (int i = 0; i < size; i++) {
        pole[i] = rand() % (2*rozsah + 1) - rozsah;
        cout << pole[i] << " ";
    }
    int min = rozsah + 1;
    int max = -rozsah - 1;
    for (int i = 0; i < size; i++) {
        if (pole[i] > max) {
            max = pole[i];
        }
        if (pole[i] < min) {
            min = pole[i];
        }
    }
    file << "min :" << min << endl << "max :" << max;
    cout << endl << "min : " << min << endl << "max :" << max;
}
