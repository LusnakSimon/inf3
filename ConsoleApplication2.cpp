
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main(int argc, char * argv[]) {
    ifstream newfile;
    srand(time(nullptr));
    const char * filename = argv[1];
    newfile.open(filename);
    int size;
    newfile >> size;
    int* numbers = new int[size];

    int first_rand = rand() % size;
    int second_rand = rand() % size;
    int third_rand = rand() % size;

    numbers[0] = size;
    int number;
    int count = 1;

    while (count < size && newfile >> number) {
        numbers[count] = number;
        count++;
    }
    newfile.close();

    cout << "cisla : ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";

    }

    cout << endl << "random index: " << first_rand << " "
         << second_rand << " " << third_rand;

    cout << endl << "cisla na random indexoch: " << numbers[first_rand]
         << " " << numbers[second_rand]
         << " " << numbers[third_rand];

    cout << endl << "najmensie cislo : " 
         << min({ numbers[first_rand], numbers[second_rand], numbers[third_rand] });
    return 0;
} 

