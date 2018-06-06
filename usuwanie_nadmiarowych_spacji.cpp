//POP 2016-01-10 projekt 2 Kubok Dominika AiR 3 160735 DEVC++ 5.11 TDM-GCC 4.9.2 64-bit Release

#include <iostream>
#include <fstream>
#include <stdio.h>

#define ZNAK ' '

using namespace std;

//zliczacz spacji
int licznie_spacji(fstream &wejscie) {
	int ilosc_linii = 0;
	char *temp = new char[1000];

	while (wejscie.eof() == false) {
		ilosc_linii++;
		wejscie.getline(temp, 1000);
	}
	delete[] temp;
	int ilosc_spacji = 0;
	while (ilosc_linii / 10 != 0) {
		ilosc_linii = ilosc_linii / 10;
		ilosc_spacji++;
	}
	return ilosc_spacji;
}

//dlugosc linii
int dlugosc_linii_char(char *linia) {
	int dlugosc = 0;
	while (linia[dlugosc] != NULL) {
		dlugosc++;
	}
	return dlugosc;
}

//wczytanie linii z pliku, przetworzenie, gotowe w nowa_linia
void wczytywanie_linii(char *linia_string, char *nowa_linia) {

	//zliczenie ilosci znakow linii wejsciowej
	int dlugosc_linii = dlugosc_linii_char(linia_string);

	//linia finalna, null na koncu, dlugosc = dlugosc linii bez usuwania znakow
	nowa_linia[0] = NULL;

	//flaga zapisujaca czy wystapila juz w tekscie litera
	bool czy_pierwsza_litera = 0;

	//ilosc spacji wystepujacych po sobie i miejsce na ktore mamy wpisac kolejny znak wyjsciowego stringa
	int spacje = 0;
	int miejsce_znaku = 0;
	for (int i = 0; i < dlugosc_linii; i++) {

		//sprawdzenie czy wystapila spcja
		if (linia_string[i] != ZNAK) {
			czy_pierwsza_litera = 1;
			spacje = 0;
		}

		//jezeli nie bylo jeszcze liter w linii i spacja
		if (linia_string[i] == ZNAK && czy_pierwsza_litera == 0) {
			continue;
		}

		//zliczaj spacje i jak wiecej niz 1 to przerwij
		if (linia_string[i] == ZNAK) {
			spacje++;
			if (spacje > 1) {
				continue;
			}
		}

		//dopisywanie do finalnego stringa wlasciwego znaku, zwiekszenie iteratora i zakonczenie nullem
		nowa_linia[miejsce_znaku] = linia_string[i];
		miejsce_znaku++;
		nowa_linia[miejsce_znaku] = NULL;
	}

	//zliczanie dlugosci nowego stringa do wpisania w plik
	int dlugosc_nowego = dlugosc_linii_char(nowa_linia);

	//usuwanie ostatniego znaku jezeli jest spacja
	if (nowa_linia[dlugosc_nowego - 1] == ZNAK) {
		nowa_linia[dlugosc_nowego - 1] = NULL;	
	}
}

//odejmowanie spacji w zaleznosci od dlugosci liczby
int odejmowanie_spacji(int numer_linii) {
	int liczba_do_odjecia = 0;
	while (numer_linii / 10 != 0) {
		numer_linii = numer_linii / 10;
		liczba_do_odjecia++;
	}
	return liczba_do_odjecia;
}

//zapisaywanie przygotowanej linii do pliku
void zapis_linii(fstream &wyjscie, int numer_linii, int ilosc_spacji, char *nowa_linia) {
	//zapis numeru linii do pliku
	wyjscie << numer_linii;

	//ile spacji ma byc odjetych wzgledem dlugosci numeru linii
	int spacje_do_odjecia = odejmowanie_spacji(numer_linii);

	//wypisywanie spacji po numerze linii, przed wlasciwa czescia wersu
	for (int z = 0; z < ilosc_spacji + 1 - spacje_do_odjecia; z++) {

		wyjscie << " ";
	}

	//wypisanie sformatowanego stringa z wejscia
	wyjscie << nowa_linia << "\n";
}

int main()
{
	//otwieranie i sprawdzanie pliku wejscia
	fstream wejscie;
	wejscie.open("wejscie.txt", ios::in);
	if (wejscie.good() == false) {
		cout << "Nie wczytano pliku wejscia" << endl;
	}

	//otwieranie i sprawdzanie pliku wyjscia
	fstream wyjscie;
	wyjscie.open("wyjscie.txt", ios::out);
	if (wyjscie.good() == false) {
		cout << "Nie wczytano pliku do zapisu" << endl;
	}

	//zliczanie ile spacji potrzebnych do przesuniecia wiersza
	int ilosc_spacji = licznie_spacji(wejscie);

	//przesuwanie wskaznika wewnatrz pliku na jego poczatek
	wejscie.clear();
	wejscie.seekg(0);

	//zakonczenie wczytywania jak dotrze do znaku konca pliku
	int numer_linii = 0;
	while (wejscie.eof() == false) {
		numer_linii++;

		//tymczasowa tablica do wczytania za pomoca getline
		char * linia_temp = new char[1000];
		wejscie.getline(linia_temp, 1000);

		int dlugosc_linia_temp = dlugosc_linii_char(linia_temp) + 1;

		char * linia_wejscie = new char[dlugosc_linia_temp];

		for (int i = 0; i < dlugosc_linia_temp; i++) {
			linia_wejscie[i] = linia_temp[i];
		}
		delete[] linia_temp;
		char *nowa_linia = new char[dlugosc_linia_temp];

		wczytywanie_linii(linia_wejscie, nowa_linia);
		delete[] linia_wejscie;

		zapis_linii(wyjscie, numer_linii, ilosc_spacji, nowa_linia);
		delete[] nowa_linia;
	}

	//zamkniecie otwartych plikow wejscia i wyjscia
	wyjscie.close();
	wejscie.close();

	return 0;
}

