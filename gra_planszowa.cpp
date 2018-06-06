//POP 2015-12-07 projekt 1 Kubok Dominika AiR 3 160735 DEVC++ 5.11 TDM-GCC 4.9.2 64-bit Release

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

//wypisanie zasad gry
void zasady_gry(){
	cout << " Celem gracza jest umieszczenie ktoregos ze stosow o wysokosci 1 na przeciwleglym koncu planszy. Jesli gracz nie ma zadnego stosu o wysokosci 1 przegrywa." << endl;
	cout << " W swojej kolejce gracz moze: " << endl;
	cout << " 1. Zwiekszyc wysokosc ktoregos ze stosow o wysokosci 1 wpisujac jego pozycje, np. A2, zatwierdzajac enterem, a nastepnie naciskajac + " << endl;
	cout << " 2. Przesunac ktorys ze swoich stosow o jedno pole w dowolnym kierunku ( w pionie, w poziomie i po skosie ), wpisujac pozycje stosu, a nastepnie pozycje, na ktora ma sie przesunac.  " << endl;
	cout << " 3. Zbic ktorys ze stosow przecinika, jesli zbijany stos jest dokladnie o 1 mniejszy od stosu zbijajacego, wpisujac pozycje swojego stosu, a nastepnie pozycje stosu zbijanego. " << endl;
}

//wypelnianie mapy i planszy na start nullami
void mapa_plansza_null(char plansza[37][19], char mapa[6][6][2]) {
	for (int i = 0; i < 37; i++) {
		for (int j = 0; j < 19; j++) {
			plansza[i][j] = NULL;
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			for (int z = 0; z < 2; z++)
			{
				mapa[i][j][z] = NULL;
			}
		}
	}
}

//ustawianie pionkow w poczatkowe ustawienie
void poczatkowe_ustawienie(char mapa[6][6][2]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			for (int z = 0; z < 2; z++) {
				if (j < 2) {
					mapa[i][j][0] = '1';
					mapa[i][j][1] = '1';
				}
				else if (j>3) {
					mapa[i][j][0] = '2';
					mapa[i][j][1] = '1';
				}
			}
		}
	}
}

//ladowanie do planszy poziomo krawiedzi +-----+ itd
void krawedz_pozioma(char plansza[37][19], int wiersz) {
	for (int i = 0; i < 37; i++) {
		if (i % 6 == 0) {
			plansza[i][wiersz] = '+';
		}
		else {
			plansza[i][wiersz] = '-';
		}
	}
}

//ladowania do planszy wiersza w ktorym jest wysyokosc stosu
void wysokosc_stosu(char plansza[37][19], int wiersz, char mapa[6][6][2]) {
	for (int i = 0; i < 37; i++) {
		if (i % 6 == 0) {
			plansza[i][wiersz] = '|';
		}
		else if (i % 6 == 3) {
			if (mapa[i / 6][wiersz / 3][0] != NULL) {
				plansza[i][wiersz] = mapa[i / 6][wiersz / 3][1];			//wczytywanie z mapy do planszy
			}
			else {															//jezeli zaden gracz to null w plansze
				plansza[i][wiersz] = NULL;
			}
		}
	}
}

//ladowanie do planszy wiersza gdzie sa znaki graczy
void znak_gracza(char plansza[37][19], int wiersz, char mapa[6][6][2]) {
	for (int i = 0; i < 37; i++) {
		if (i % 6 == 0) {
			plansza[i][wiersz] = '|';
		}
		else if (i % 6 == 2 || i % 6 == 3 || i % 6 == 4) {
			if (mapa[i / 6][wiersz / 3][0] == '1') {
				plansza[i][wiersz] = '#';								//jezeli gracz 1 to wstawia ###
			}
			else if (mapa[i / 6][wiersz / 3][0] == '2') {				//jezeli gracz 2 to wstawia OOO
				plansza[i][wiersz] = 'O';
			}
			else {														//jezeli zaden gracz to wstaw null w plansze
				plansza[i][wiersz] = NULL;
			}
		}
	}
}

//uzupelnienie calej planszy
void uzupelnianie_planszy(char mapa[6][6][2], char plansza[37][19]) {

	krawedz_pozioma(plansza, 0);
	wysokosc_stosu(plansza, 1, mapa);
	znak_gracza(plansza, 2, mapa);

	krawedz_pozioma(plansza, 3);
	wysokosc_stosu(plansza, 4, mapa);
	znak_gracza(plansza, 5, mapa);

	krawedz_pozioma(plansza, 6);
	wysokosc_stosu(plansza, 7, mapa);
	znak_gracza(plansza, 8, mapa);

	krawedz_pozioma(plansza, 9);
	wysokosc_stosu(plansza, 10, mapa);
	znak_gracza(plansza, 11, mapa);

	krawedz_pozioma(plansza, 12);
	wysokosc_stosu(plansza, 13, mapa);
	znak_gracza(plansza, 14, mapa);

	krawedz_pozioma(plansza, 15);
	wysokosc_stosu(plansza, 16, mapa);
	znak_gracza(plansza, 17, mapa);

	krawedz_pozioma(plansza, 18);
}

//rysowanie planszy na ekranie
void rysowanie_planszy(char mapa[6][6][2], char plansza[37][19]) {
	//czyszczenie konsoli
	system("cls");
	zasady_gry();
	char temp1 = 'A';
	int temp2 = 1;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 37; j++) {
			cout << plansza[j][i];
		}
		//rysowanie cyferek z boku
		if (i % 3 == 2) {
			cout << temp2;
			temp2++;
		}
		cout << endl;
	}
	//rysowanie literek na dole planszy
	for (int i = 0; i < 37; i++) {
		if (i % 6 == 3) {
			cout << temp1;
			temp1++;
		}
		else {
			cout << " ";
		}
	}
	cout << endl;
}

//przepisywanie w inne pole i usuwanie z poprzedniego
void poruszanie_pionka(char mapa[6][6][2], char plansza[37][19], int na_ktore_int_x, int na_ktore_int_y, int ktore_pole_int_x, int ktore_pole_int_y) {
	mapa[na_ktore_int_x][na_ktore_int_y][0] = mapa[ktore_pole_int_x][ktore_pole_int_y][0];
	mapa[na_ktore_int_x][na_ktore_int_y][1] = mapa[ktore_pole_int_x][ktore_pole_int_y][1];
	mapa[ktore_pole_int_x][ktore_pole_int_y][0] = NULL;
	mapa[ktore_pole_int_x][ktore_pole_int_y][1] = NULL;
}

int main() {
		
	char mapa[6][6][2];
	char plansza[37][19];

	mapa_plansza_null(plansza, mapa);

	poczatkowe_ustawienie(mapa);

	uzupelnianie_planszy(mapa, plansza);

	rysowanie_planszy(mapa, plansza);

	//flagi zakonczenia programu i ktory gracz
	bool koniec = 0;
	int gracz = 1;

	while (koniec == 0) {

		cout << endl << "Ruch gracza ";
		if (gracz == 1) {
			cout << "###" << endl;
		}
		else {
			cout << "OOO" << endl;
		}

		//pobieranie pionka i gdzie ma sie posunac
		string ktore_pole;
		cin >> ktore_pole;
		string na_ktore;
		cin >> na_ktore;

		//konwersja wejsca na indeksy tablicy
		ktore_pole[0] = ktore_pole[0] - 17;
		ktore_pole[1] = ktore_pole[1] - 1;

		//konwersja z char na int
		int ktore_pole_int_x = ktore_pole[0] - 48;
		int ktore_pole_int_y = ktore_pole[1] - 48;

		if (na_ktore.length() == 1 && na_ktore[0] == '+') {
			if (mapa[ktore_pole_int_x][ktore_pole_int_y][0] - 48 == gracz) {			//sprawdzenie czy poprawne wybrane dla aktualnego gracza
				mapa[ktore_pole_int_x][ktore_pole_int_y][1]++;						//jezeli plusik dla pola to zwiekszanie stosu 
			}
			else {
				//jezeli zly gracz to od nowa
				cout << "Bledny ruch: ruch zlym pionkiem" << endl;
				continue;
			}
		}
		else {
			//sprawdznie poprawnosci gracza
			if (mapa[ktore_pole_int_x][ktore_pole_int_y][0] - 48 == gracz) {

				//konwersja wejsca na indeksy tablicy
				na_ktore[0] = na_ktore[0] - 17;
				na_ktore[1] = na_ktore[1] - 1;

				//konwersja z char na int
				int na_ktore_int_x = na_ktore[0] - 48;
				int na_ktore_int_y = na_ktore[1] - 48;

				//sprawdzenie czy ruch miesci sie w planszy
				if (na_ktore_int_x >= 0 && na_ktore_int_x < 6 && na_ktore_int_y >= 0 && na_ktore_int_y < 6) {

					//sprawdzenie czy ruch na sasiednie pole
					if ((abs(ktore_pole_int_x - na_ktore_int_x) == 1 && abs(ktore_pole_int_y - na_ktore_int_y) == 0) || (abs(ktore_pole_int_x - na_ktore_int_x) == 0 && abs(ktore_pole_int_y - na_ktore_int_y) == 1) || (abs(ktore_pole_int_x - na_ktore_int_x) == 1 && abs(ktore_pole_int_y - na_ktore_int_y) == 1)) {

						//sprawdzanie kto stoi na docelowym polu
						if (mapa[na_ktore_int_x][na_ktore_int_y][0] == NULL) {
							poruszanie_pionka(mapa, plansza, na_ktore_int_x, na_ktore_int_y, ktore_pole_int_x, ktore_pole_int_y);
						}
						else if (mapa[na_ktore_int_x][na_ktore_int_y][0] - 48 != gracz && mapa[na_ktore_int_x][na_ktore_int_y][0] != NULL && (mapa[ktore_pole_int_x][ktore_pole_int_y][1] - mapa[na_ktore_int_x][na_ktore_int_y][1] == 1)) {
							poruszanie_pionka(mapa, plansza, na_ktore_int_x, na_ktore_int_y, ktore_pole_int_x, ktore_pole_int_y);
						}
						else {
							//jezeli docelowe pole zajete to od nowa
							cout << "Bledny ruch: na docelowym polu stoi twoj pionek" << endl << "lub liczba stosu przeciwnika nie jest nizsza, aby zbic" << endl;
							continue;
						}
					}
					else {
						//jezeli ruch inny niz o 1 to od nowa
						cout << "Bledny ruch: mozna porusza sie tylko na sasiednie pola" << endl;
						continue;
					}
				}
				else {
					//jezeli wyjdzie za mape to od nowa
					cout << "Bledny ruch: wyjscie za plansze" << endl;
					continue;
				}
			}
			else {
				//jezeli bledny gracz to od nowa
				cout << "Bledny ruch: ruch zlym pionkiem" << endl;
				continue;
			}
		}
		uzupelnianie_planszy(mapa, plansza);

		rysowanie_planszy(mapa, plansza);

		//sprawdzenie czy gra powinna byc zakonczona
		for (int i = 0; i < 6; i++) {
			//jezeli 1 gracz na wygranych polach i stos 1
			if (mapa[i][5][0] == '1' && mapa[i][5][1] == '1') {
				koniec = 1;
			}
			//jezeli 2 gracz na wygranych polach i stos 1
			else if (mapa[i][0][0] == '2' && mapa[i][5][1] == '1') {
				koniec = 1;
			}
		}

		//zliczanie pionkow graczy i pionkow z stosem 1
		int liczba_pionkow_1 = 0;
		int liczba_pionkow_stos_1 = 0;
		int liczba_pionkow_2 = 0;
		int liczba_pionkow_stos_2 = 0;

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (mapa[i][j][0] == '1') {
					liczba_pionkow_1++;
				}
				if (mapa[i][j][1] == '1' && mapa[i][j][0] == '1') {
					liczba_pionkow_stos_1++;
				}
				if (mapa[i][j][0] == '2') {
					liczba_pionkow_2++;
				}
				if (mapa[i][j][1] == '1' && mapa[i][j][0] == '2') {
					liczba_pionkow_stos_2++;
				}
			}
		}

		//sprawdzanie czy zostal jakis pionek o stosie 1 i ewentualny koniec gry
		if ((liczba_pionkow_1 - liczba_pionkow_stos_1 == liczba_pionkow_1) && liczba_pionkow_1 != 0) {
			koniec = 1;
			gracz = 2;
		}
		else if ((liczba_pionkow_2 - liczba_pionkow_stos_2 == liczba_pionkow_2) && liczba_pionkow_1 != 0) {
			koniec = 1;
			gracz = 1;
		}

		//na koniec rundy zamiana graczy jezeli nie skonczono gry
		if (gracz == 1 && koniec == 0) {
			gracz = 2;
		}
		else if (gracz == 2 && koniec == 0) {
			gracz = 1;
		}
	}

	//wypisanie zwyciezcy
	cout << endl << endl << "Wygrywa gracz ";
	if (gracz == 1) {
		cout << "###" << endl << endl;
	}
	else {
		cout << "OOO" << endl << endl;
	}
	return 0;
}
