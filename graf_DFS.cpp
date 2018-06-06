#include<iostream>
#include<iomanip>
#include <cstdlib>
#include<stack>
#include<vector>
using namespace std;

void DFS (vector < vector<int> >, vector<bool>&, stack<int>&, int);
void graf (vector < vector<int> >& , vector<bool>&);
void menu_main(vector < vector<int> >,  vector <bool>& ,stack<int>& );
void zacznij_DFS(vector < vector<int> >, vector<bool>&, stack<int>&);
void pisz_lista(vector < vector<int> >);
void pisz_menu (void);
void dodaj_krawedz(vector < vector<int> >&);
void  dodaj_wierzcholek(vector < vector<int> >&, vector<bool> &);
void visited_false(vector<bool>&);

int main ()
{ 
	stack<int> stos;
	vector< vector<int> > sasiedzi;
	vector <bool> visited;
	menu_main(sasiedzi, visited, stos);
    system ("pause");
	return 0;
} 

void dodaj_wierzcholek(vector < vector<int> > &sasiedzi,vector <bool>  &visited)
{
	int n=sasiedzi.size();
	sasiedzi.resize(n+1);
	visited.push_back(false);
	cout<< "Dodales wierzcholek "<< n+1<<endl;
}

void menu_main(vector < vector<int> > sasiedzi,vector <bool>  &visited, stack<int>  &stos )
{
	int wybor;
	do {
   	system("cls");
  	pisz_menu();
    cin >> wybor;
    switch(wybor)
    {
    	case 1: graf(sasiedzi,visited );
   			system ("pause");
     	   	break;               
		case 2: dodaj_krawedz(sasiedzi);
   	  		system ("pause");
        	break;            
		case 3:  dodaj_wierzcholek(sasiedzi, visited);
       		system ("pause");
            break;            
    	case 4: pisz_lista(sasiedzi);
       		system ("pause");
            break;          
    	case 5: zacznij_DFS(sasiedzi,visited, stos);
       		system ("pause");
            break;
    }  
  }while(wybor!=0);
}

void blad (void)
{
	cout<<" Nie ma takiego wierzcholka "<<endl;
}

void dodaj_krawedz(vector < vector<int> > &sasiedzi)
{
	int u,v;
	cout<< " podaj pary sasiednich wierzcholkow "<<endl;
		cout << ":"; cin >> u; 
		cout << ":"; cin >> v;
		if (u>sasiedzi.size()||v>sasiedzi.size())
			blad();		
		else {
			cout << endl;
			sasiedzi[u-1].push_back(v-1);
			sasiedzi[v-1].push_back(u-1);
			cout<<"Dodales krawedz " <<u<<" - " <<v<<endl;
	}
}

void pisz_menu (void)
{
  
             cout << endl;
             cout << "MENU" << endl;
             cout << "----------------------" << endl;
             cout << "1 - stworz graf " <<endl;
             cout << "2 - dodaj krawedz "  << endl;
             cout << "3 - dodaj wierzcholek "      << endl;
             cout << "4 - wypisz liste sasiedztw " << endl;
             cout << "5 - DFS  " << endl;
             cout << "0 - koniec pracy"     << endl;
             cout << "> ";
  }
  
 void zacznij_DFS(vector < vector<int> > sasiedzi, vector<bool> &visited, stack<int> &stos)
 { 	
 	int v;
 	cout<< "Podaj wierzcholek startowy "<<endl;
 	cin>>v;
 	if(v>sasiedzi.size())
 		blad();
 	else{
 		v--;
		stos.push( v+1 );
 		DFS(sasiedzi, visited, stos, v);
 		visited_false(visited);
	 	}	
 }
 
void visited_false(vector<bool> &visited)
 {
 	for(int i=0; i<visited.size(); i++)
 	{
 		visited[i]=false;
	}
 }
 
void DFS (vector < vector<int> > sasiedzi, vector<bool> &visited, stack<int> &stos, int v)
{
	visited[v] = true;
	for (int i=0; i<sasiedzi[v].size(); i++){
	for(int u=0; u<sasiedzi.size(); u++)
	{
		if ((sasiedzi[v][i] == u) and not visited[u])
		{
			cout << stos.top( ) << "-->";
			stos.push( u+1 );
			cout<< stos.top( )<<endl;
			
			DFS(sasiedzi,visited,stos, u);
			cout << stos.top()  << "-->";
			stos.pop( );
			cout<< stos.top()<<endl;
		}
	}
}
}

void graf(vector < vector<int> > &sasiedzi, vector<bool> &visited )	
{

		if (sasiedzi.size()!=0)
			cout<<" Graf juz istnieje "<<endl;
		else{
			int n;
			cout<<" Podaj liczbe wierzcholkow "<<endl;
			cin>>n;
			sasiedzi.resize(n);
			visited.resize(n);
			for(int i=0; i<visited.size(); i++)
			{
				visited[i]=false;
			}
			int u,v;
			cout<< " podaj pary sasiednich wierzcholkow "<<endl;
			cout << ":"; cin >> u; // Podanie 0 dla u lub v konczy wpisywanie
			if (u!=0) {
				if (u>sasiedzi.size())
				blad();
				else{
					cout << ":"; cin >> v;
					cout << endl;
				}	
			}
			while((u!=0) and (v!=0)){
				if (u>sasiedzi.size()||v>sasiedzi.size())
				{
					blad();
					break;
				}
				else{
					sasiedzi[u-1].push_back(v-1);
					sasiedzi[v-1].push_back(u-1);
					cout << ":"; cin >> u;
					if (u!=0) {
						cout << ":";
						cin >> v;
						cout << endl;
					}		
				}
			}
		}
}

void pisz_lista(vector < vector<int> > sasiedzi)
{		
		cout<< "wierzcholek| sasiedzi "<<endl;
		cout<< "______________________"<<endl;
		for (int i=0; i<sasiedzi.size(); i++){ 
	    	cout<<setw(6)<<i+1<<setw(6)<<"|";
		for (int j=0; j<sasiedzi[i].size(); j++)
			cout <<setw(4) <<sasiedzi[i][j]+1;
			cout <<endl;
		}
		
}

	
	


