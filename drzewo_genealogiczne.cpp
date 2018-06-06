#include <iostream>
#include <iomanip>

using namespace std;

struct wezel;

struct para {
    wezel *wskaznik_na_wezel;
    string rodzic_1;
    string rodzic_2;
};

struct wezel {
    wezel *wskaznik_na_wezel;
    para *wskaznik_na_para;
};
 
void pisz_menu ();
void menu_main(para *wsk);
para* szukaj_w_wezel(wezel *wsk, string imie);
para* szukaj_w_para(para *wsk, string imie);
wezel* przeszukaj_pare(para*wsk);
para* przeszukaj_wezel(wezel *wsk);
void zmiana_imienia (para *wsk);	
void dodawanie_malzonka(para *wsk);
void dodawanie_dziecka (para *wsk);
void dodaj_kolejne_dziecko(wezel* wsk,  string imie2);
void wypisz_z_pary(para *wsk);
void wypisz_wezel(para *wsk);  
void wypisz_z_wezla(wezel *wsk_wezel);
void drukowanie_dzieci (para *wsk);
void drukowanie_wnukow(para *wsk);
void korzen(para *wsk);
void drukowanie_bledu();
  
int main()
  {
  	para *wsk_para_1 = new para;
	menu_main(wsk_para_1);
  	
  	return 0;
  	
  }

void pisz_menu (void)
{
  
             cout << endl;
             cout << "MENU" << endl;
             cout << "----------------------" << endl;
             cout << "1 - zmiana imienia " << endl;
             cout << "2 - dodawanie malzonka " << endl;
             cout << "3 - dodawanie dziecka " << endl;
             cout << "4 - drukowanie drzewa " << endl;
             cout << "5 - drukowanie dzieci" << endl;
             cout << "6 - drukowanie wnukow" << endl;
              cout << "7  - korzen" << endl;
             cout << "0 - koniec pracy" << endl;
             cout << "> ";
  }
 
void menu_main(para *wsk)
  {
  	int wybor;
  do {
  	system("cls"); 
     pisz_menu();
     cin >> wybor;
     switch(wybor)
     {
		case 1:zmiana_imienia(wsk); 
				system ("pause");
               break;
		case 2: dodawanie_malzonka(wsk);
					system ("pause");
               break; 
		case 3: dodawanie_dziecka(wsk);
					system ("pause");
               break;
		case 4: wypisz_z_pary(wsk);
					system ("pause");
               break; 
		case 5: drukowanie_dzieci(wsk);
				system ("pause");
               break;
		case 6: drukowanie_wnukow(wsk);
				system ("pause");
               break; 
        case 7: korzen(wsk);
				system ("pause");
               break; 
     }
     
  } while(wybor!=0); 
  
  } 
 
para* szukaj_w_wezel(wezel *wsk, string imie){
	para* wynik = NULL; 
	
	if (wsk->wskaznik_na_para != NULL)
		wynik = szukaj_w_para(wsk->wskaznik_na_para, imie);
	
	if (wynik == NULL && wsk->wskaznik_na_wezel != NULL)
		wynik = szukaj_w_wezel(wsk->wskaznik_na_wezel, imie);

	return wynik;
}

para* szukaj_w_para(para *wsk, string imie){

	para* wynik = NULL;
	if (wsk->rodzic_1 == imie || wsk->rodzic_2 == imie)
		wynik = wsk;
	if (wynik == NULL && wsk->wskaznik_na_wezel != NULL)
		wynik = szukaj_w_wezel(wsk->wskaznik_na_wezel, imie);
	
	return wynik;
} 
 
wezel* przeszukaj_pare(para*wsk)
{
	if (wsk->wskaznik_na_wezel!=NULL)
	{
		wypisz_z_wezla(wsk->wskaznik_na_wezel);
	}
} 
  
para* przeszukaj_wezel(wezel *wsk)
{
	if (wsk->wskaznik_na_para!=NULL)przeszukaj_pare(wsk->wskaznik_na_para);
	if (wsk->wskaznik_na_wezel!=NULL)przeszukaj_wezel(wsk->wskaznik_na_wezel);
}

void korzen (para *wsk)
{    

	string imie1, imie2;
	cout<< "Podaj imiona przodkow "<<endl;
	cin>>imie1>>imie2;
	wsk->rodzic_1=imie1;
	wsk->rodzic_2=imie2;
	wsk->wskaznik_na_wezel=NULL;
	
	
}

void zmiana_imienia(para *wsk){
	string nowe_imie, imie;
	cout << "Podaj imie osoby, ktorej imie chcesz zmienic" << endl;
	cin >> imie;
  	cout << "Podaj nowe imie dla tej osoby" << endl;
  	cin >> nowe_imie;

	para*znaleziona_para=szukaj_w_para(wsk, imie);
	if(znaleziona_para==NULL){drukowanie_bledu();
	}
	else {
	
	  	if( znaleziona_para->rodzic_1 == imie )
	  	{
	  		znaleziona_para->rodzic_1 = nowe_imie;
	  	}
	  	else if( znaleziona_para->rodzic_2 == imie )
	  	{
	  		znaleziona_para->rodzic_2 = nowe_imie;
  	}
  }
} 

void dodawanie_malzonka (para *wsk)
 {
 	string imie1;
 	cout<< "Podaj imie osoby, ktorej dodac malzonka "<<endl;
 	cin>>imie1;
 	para *wskaznik;
 	wskaznik=szukaj_w_para(wsk, imie1);
 	if(wskaznik==NULL){drukowanie_bledu();
	 }
	 else{
	 
 	string imie2;
 	cout<< "Podaj imie malzonka "<<endl;
 	cin>>imie2;
 	wskaznik->rodzic_2=imie2;
 }
 }
 
void dodawanie_dziecka (para *wsk)
 {
 	string imie1, imie2;
 	cout<< "Podaj imie osoby, ktorej dodac dziecko "<<endl;
 	cin>>imie1;
 	cout<< "Podaj imie dziecka "<<endl;
 	cin>>imie2;
 	para *wskaznik_para=szukaj_w_para(wsk, imie1);
 	if (wskaznik_para==NULL){drukowanie_bledu();
	}
 	else {
	 
	 	if(wskaznik_para->wskaznik_na_wezel==NULL)
		 	{
			wezel *wsk_wezel_nowy = new wezel;
			wezel *wsk_1=wskaznik_para->wskaznik_na_wezel;
		
		   	wskaznik_para->wskaznik_na_wezel=wsk_wezel_nowy;
		   	wsk_wezel_nowy->wskaznik_na_wezel=NULL;
		   	wsk_wezel_nowy->wskaznik_na_para=NULL;
		   	para *wsk_para= new para;
		   	wsk_wezel_nowy->wskaznik_na_para=wsk_para;
		   	wsk_para->rodzic_1=imie2;
		   	wsk_para->rodzic_2=" ";
		   	wsk_para->wskaznik_na_wezel=NULL;
			 }
			 
			else
			{
			dodaj_kolejne_dziecko(wskaznik_para->wskaznik_na_wezel, imie2);
			}
		}	
	}
	
void dodaj_kolejne_dziecko(wezel* wsk,  string imie2)
{

	if (wsk->wskaznik_na_wezel==NULL)
	{
		wezel *wsk_wezel_nowy = new wezel;
	   	wsk->wskaznik_na_wezel=wsk_wezel_nowy;
	   	wsk_wezel_nowy->wskaznik_na_wezel=NULL;
	   	wsk_wezel_nowy->wskaznik_na_para=NULL;
	   	para *wsk_para= new para;
	   	wsk_wezel_nowy->wskaznik_na_para=wsk_para;
	   	wsk_para->rodzic_1=imie2;
	   	wsk_para->rodzic_2=" ";
	   	wsk_para->wskaznik_na_wezel=NULL;
	}
	else  dodaj_kolejne_dziecko(wsk->wskaznik_na_wezel,  imie2);

}	

void wypisz_wezel(wezel *wsk)
{
	if (wsk->wskaznik_na_para!=NULL)wypisz_z_pary(wsk->wskaznik_na_para);
	if(wsk->wskaznik_na_wezel!=NULL)wypisz_wezel(wsk->wskaznik_na_wezel);
	
}
 
void wypisz_z_pary(para *wsk)
 {
  	cout<< setw(2) <<wsk->rodzic_1 << " + "<< wsk->rodzic_2<<endl;
	if(wsk->wskaznik_na_wezel!=NULL)wypisz_wezel( wsk->wskaznik_na_wezel);

	
 }

void wypisz_z_wezla(wezel *wsk_wezel)
 {
 	cout<< wsk_wezel->wskaznik_na_para->rodzic_1<<endl;
 if (wsk_wezel->wskaznik_na_wezel!=NULL) wypisz_z_wezla(wsk_wezel->wskaznik_na_wezel);
 else return;
 }

void drukowanie_dzieci (para *wsk)
 {
 	string imie1;
 	cout<< " Podaj imie rodzica "<<endl;
 	cin>>imie1;
 	para *wsk_para=szukaj_w_para(wsk, imie1);
 	if (wsk_para==NULL){drukowanie_bledu();
	}
	
	else{
	
	 	if(wsk_para->wskaznik_na_wezel==NULL)
	 	{
	 		cout<< "Ta para nie ma dzieci";
		 }
		if (wsk_para->wskaznik_na_wezel!=NULL)
		{
			wypisz_z_wezla(wsk_para->wskaznik_na_wezel);

	}
}
}

void drukowanie_wnukow(para *wsk)
{
	string imie1;
	cout<<" Podaj imie dziadka " <<endl;
	cin>>imie1;
	para *wsk_para=szukaj_w_para(wsk, imie1);
	if (wsk_para==NULL){drukowanie_bledu();
	}
	
	else{

			if(wsk_para->wskaznik_na_wezel==NULL)
	 	{
	 		cout<< "Ta para nie ma wnukow";
	 		
		 }
		if (wsk_para->wskaznik_na_wezel!=NULL)
		{
			przeszukaj_wezel(wsk_para->wskaznik_na_wezel);
	
		}
	}
}

void drukowanie_bledu()
{
	
	cout<<"Taka osoba nie istnieje "<<endl;
	
}



  	

  

 

 
 









