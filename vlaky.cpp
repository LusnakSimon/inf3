
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;
class Vlak {
private:
	int cisloVlaku;
	vector<string> stanice;
public:
	Vlak(int cisloVlaku)
	{
		this->cisloVlaku = cisloVlaku;
	}
	
	int getCisloVlaku() {
		return this->cisloVlaku;
	}
	void pridajStanicu(string stanica) {
		this->stanice.push_back(stanica);
	}
	vector<string> getStanice() {
		return this->stanice;
	}
	~Vlak() {}
};

class Stanica {
private:
	string nazov;
	vector<int> vlaky;
public:
	Stanica(string nazov) {
		this->nazov = nazov;
	}
	string getNazov() {
		return this->nazov;
	}
	void pridajVlak(int vlak) {
		this->vlaky.push_back(vlak);
	}
	vector<int> getVlaky() {
		return this->vlaky;
	}
	~Stanica() {}
};

bool compareByName(Stanica& obj1, Stanica& obj2) {
	return obj1.getNazov() < obj2.getNazov();
}

void nacitajVlaky(string nazovSuboru) {
	ifstream vstupnySubor(nazovSuboru);
	if (vstupnySubor.is_open()) {
		int cisloVlaku = 0;
		string nazovStanice;
		string cas;
		map<int, vector<string>> vlaky;
		map<string, vector<int>> stanice;
		while (vstupnySubor >> cisloVlaku >> nazovStanice >> cas) {


			if (vlaky.find(cisloVlaku) == vlaky.end()) {
				vector<string> zoznamStanic;
				zoznamStanic.push_back(nazovStanice);
				vlaky[cisloVlaku] = zoznamStanic;
			}
			else {
				vlaky[cisloVlaku].push_back(nazovStanice);
			}


			if (stanice.find(nazovStanice) == stanice.end()) {
				vector<int> zoznamVlakov;
				zoznamVlakov.push_back(cisloVlaku);
				stanice[nazovStanice] = zoznamVlakov;
			}
			else {
				stanice[nazovStanice].push_back(cisloVlaku);
			}
		}

		vector<Vlak> vlakyZoznam;
		vector<Stanica> staniceZoznam;

		for (const auto& entry : vlaky) {
			Vlak vlak(entry.first);
			for (const auto& station : entry.second) {
				vlak.pridajStanicu(station);
			}
			vlakyZoznam.push_back(vlak);
		}

		for (const auto& entry : stanice) {
			Stanica stanica(entry.first);
			for (const auto& train : entry.second) {
				stanica.pridajVlak(train);
			}
			staniceZoznam.push_back(stanica);
		}

		sort(staniceZoznam.begin(), staniceZoznam.end(), compareByName);

		for (Stanica stanica : staniceZoznam) {
			cout << stanica.getNazov() << ": ";
			for (int cisloVlaku : stanica.getVlaky()) {
				cout << cisloVlaku << ",";
			}
			cout << endl;
		}
		cout << "Zadaj pismeno:";
		char pismeno;
		cin >> pismeno;
		cout << endl;
		for (Stanica stanica : staniceZoznam) {
			if (stanica.getNazov()[0] == pismeno) {
				cout << stanica.getNazov() << endl;
			}
		}

		
	}
	else {
		cerr << "chyba";
	}
}

int main()
{
	nacitajVlaky("vlaky.txt");
}
