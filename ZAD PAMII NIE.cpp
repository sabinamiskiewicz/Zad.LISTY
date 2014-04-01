#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>

using namespace std;

template <class T>
class Node{
public:
    T dane;
    Node *poprzedni;
    Node *nastepny;
    
    Node(T dane, Node *poprz, Node *nast): dane(dane), poprzedni(poprz), nastepny(nast) {
	}
    
};

template <class T>
class MojIterator{
private:
	Node<T>* aktualny;
public:
	MojIterator():aktualny(0){}
	MojIterator(Node<T>* n): aktualny(n){}
	T operator*(){return aktualny->dane;} //wy³uskanie wartoœc na jak¹ wskazuje MojIterator
	//preinkrementacja
	MojIterator& operator ++(){
		aktualny=aktualny->nastepny;
		return *this;
	}
	MojIterator& operator --(){
	aktualny=aktualny->poprzedni;
	return *this;
	}
	//postintrementacja
	MojIterator operator ++(int){
		MojIterator pomoc=*this;
		aktualny=aktualny->nastepny;
		return pomoc;
	}
	MojIterator& operator --(int){
		MojIterator pomoc=*this;
		aktualny=aktualny->poprzedni;
		return pomoc;
	}
	//porownanie true jesli inetratory wskazuja na ten sam elem
	bool operator==(const MojIterator& i){
		if(aktualny==i.aktualny)
			return true;
		return false;
	}
	//nierownosc
	bool operator!=(const MojIterator& i){
		return !(*this==i);
	}
	//przypisania
	MojIterator& operator=(const MojIterator& i){
		aktualny=i.aktualny;
		return *this;
	}
	
};
template <class T>
 bool czyrozlacz(Node<T>& coss){
		if ((coss.nastepny==NULL) && (coss.poprzedni==NULL))
		return true;
	return false;
 }
 template <class T>
 bool czypodlacz(Node<T>& coss){
	return !czyrozlacz(coss);
}
//c)
Node<int> * pierwszy;
Node<int> * ostatni;

template <class T>
void wstawnakoncu(Node<T>& coss){
	ostatni->nastepny=&coss;
	coss->poprzedni=&ostatni;
	coss->nastepny=NULL;
	ostatni=&coss;
}
//d)
template <class T>
void wstawnapocz(Node<T>& coss){
	pierwszy->poprzedni=&coss;
	coss->poprezedni=NULL;
	coss->nastepny=&pierwszy;
	pierwszy=&coss;
}
// e)
template <class T>
void wstawprzediter(Node<T>& coss, Node<T> *iter){
	Node<T> * pomoc;
	iter->poprzedni=&coss;
	coss->poprezedni=&pomoc;
	coss->nastepny=&iter;
}
//f)
template <class T>
void wstawzaiter(Node<T>& coss, Node<T> *iter){
	Node<T> * pomoc;
	iter->nastepny=&coss;
	coss->poprzedni=&iter;
	coss->nastepny=&pomoc;
}
//zad 4
template <class T>
class Lista{
//private: 
public: //ZAMIENIC
	Node<T> *pierwszy;
    Node<T> *ostatni;  
public:
	Lista():pierwszy(NULL),ostatni(NULL){
		cout << "w konstruktorze\n";
		//konstruktor
	}
	//destruktor
	~Lista(){
		while(empty())
		pop_back();
		cout << "w destruktorze\n";
	}
	////////////////////////////////////////////////////////////////
	Lista(const Lista& stara) {
		Lista<T> *nowa = new Lista<T>();
		
		copy(stara.begin(),stara.end(),nowa);
		
	}
	
	MojIterator<T> begin() {
		return pierwszy;
	}
	MojIterator<T> end() {
		if(!empty()) return ostatni->nastepny;
		return NULL;
	}
	//dodaje
	void push_front(T const&coss){
		Node<T> *nowy = new Node<T>(coss, NULL, pierwszy);
		//nowy->dane = coss;
//		nowy->poprzedni=NULL;
//		nowy->nastepny=pierwszy;
		
		if(!empty()) pierwszy->poprzedni=nowy;
		else ostatni = nowy;
		pierwszy = nowy;
	}
	void push_back(T const&coss){
		Node<T> *nowy = new Node<T>(coss, ostatni, NULL);
		//nowy->dane = coss;
//		nowy->poprzedni=NULL;
//		nowy->nastepny=pierwszy;
		if(!empty()) ostatni->nastepny=nowy;
		else pierwszy = nowy;
		ostatni = nowy;
	}
	
	//usuwa
	T pop_front() {
		T stary;
		if(!empty()) {
			stary = pierwszy->dane;
			Node<T> *pomoc;
			pomoc = pierwszy;
			if(pierwszy == ostatni) ostatni = NULL;
			pierwszy = pierwszy->nastepny;
			delete pomoc;
			if(!empty()) pierwszy->poprzedni = NULL;
		}
		else cerr << "PUSTO\n";
		return stary;
	}
	T pop_back() {
		T stary;
		if(!empty()) {
			stary = ostatni->dane;
			Node<T> *pomoc;
			pomoc = ostatni;
			if(pierwszy == ostatni) pierwszy = NULL;
			ostatni = ostatni->poprzedni;
			delete pomoc;
			if(!empty()) ostatni->nastepny = NULL;
		}
		else cerr << "PUSTO\n";
		return stary;
	}
	
	void wyswietl(){
		for( MojIterator<T> iter = begin(); iter != end(); iter++)
			cout <<  *iter << "\n";
	}
	bool empty() {
		return (pierwszy == NULL);
	}
	size_t dlugosclisty(){
		int dlugosclist;
		for( MojIterator<T> iter = begin(); iter != end(); iter++)
			dlugosclist++;
		return dlugosclist;
		//	cout <<  *iter << "\n";
	}
	void zamien(Lista& lista1,Lista& lista2){
		Lista<T> *pomoc = new Lista<T>();
		while(!empty(lista1)){
			pomoc.push_front(lista1.pop_front());
		}
		while(!empty(lista2)){
			lista1.push_front(lista2.pop_front());
		}
		while(!empty(pomoc)){
			lista2.push_front(pomoc.pop_front());
		}
		delete pomoc;
	}

	void wczytaj(istream & wejscie)
	{
		for(MojIterator<T> iter = begin(); iter != end(); iter++)
		{
			wejscie >> pierwszy,ostatni;
		}
	}
};
template <typename T>
ostream & operator<<(ostream & out, Lista<T>& list) {
	list.wyswietl(out);
	return out;
}

template <typename T>
istream & operator>>(istream & in, Lista<T>& list) {
	list.wczytaj(in);
	return in;
}

int main()
{
	Lista<int> mojalista;
	mojalista.wyswietl();
	mojalista.push_back(2);
	mojalista.push_back(3);
	mojalista.push_back(4);
	
	mojalista.push_front(1);
	cerr << mojalista.pop_front();
	mojalista.push_front(0);
	
	cerr << mojalista.pop_back();
	
	//cerr <<'\n' << mojalista.pierwszy << mojalista.ostatni << '\n';
	cerr << "\n\n PRINT \n";
	mojalista.wyswietl();
	cerr << "dlugosc: " << mojalista.dlugosclisty()<<endl;
   return 0;
}

