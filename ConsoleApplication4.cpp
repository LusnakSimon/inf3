
#include <iostream>
#include "Generator.h"
int main(int argc, char* argv[])
{
    Generator generator;
    generator.nacitajSoSuboru(argv[1]);
    generator.vygeneruj();
    generator.zoradLyziarov();
    generator.vypisDoKonzoly();
    generator.zapisDoSuboru("vysledky.txt");
    return 0;
}

