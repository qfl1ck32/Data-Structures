#include <iostream>
#include <cstdlib>
#include <string.h>
#include <chrono>
#include <bits/stdc++.h>
#include <fstream>
#include <time.h>
#include <windows.h>

using namespace std;

#define MAXSIZE 40000000

int baza, n = 0, k = 0;
int *v = new int[MAXSIZE];
int *sortat = new int[MAXSIZE];
int *aux = new int[MAXSIZE];
int *corectitudine = new int[10];
long double *timpi = new long double[10];
string *numeRezultate = new string[10];

random_device rd;
default_random_engine eng {rd()};

/// Functii folositoare pentru programul principal.

void creareFisier() {
    ofstream fout("sortare.txt");
    int numar, nr_elemente, nr_maxim, j;
    cout<<"Cate numere: ";
    cin>>nr_elemente;
    cout<<"Numere naturale pana la: ";
    cin>>nr_maxim;
    uniform_int_distribution<> dist(1, nr_maxim);
    for (j = 1; j <= nr_elemente; j += 1) {
        numar = dist(eng);
        if (j == nr_elemente)
            fout<<numar;
        else
            fout<<numar<<"\n";
    }
    fout.close();
    system("CLS");
}

void interschimbare(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void afisare(int *v, int n) {
    int i;
    for (i = 0; i < n; i += 1)
        cout<<v[i]<<" ";
}

void *citire(int *v, int &n) {
    ifstream fin("sortare.txt");
    while (!fin.eof()) {
        fin>>v[n];
        n += 1;
    }
}

int verifica_sortare_corecta() {
    int i, ok = 1;
    for (i = 0; i < n; i++)
        if (v[i] != sortat[i])
            ok = 0;
    if (ok == 1)
        return 1;
    else
        return 0;
}

void copiaza_vector(int *v, int *w, int n) {
    int i;
    for (i = 0; i < n; i++)
        w[i] = v[i];
}

void Sortare(string(*g)()) {
    cout<<"Sortarea cu numarul "<<k + 1<<" are loc...\n";
    string tip;
    auto start = chrono::high_resolution_clock::now();
    tip = g();
    auto stop = chrono::high_resolution_clock::now();
    auto timp = chrono :: duration_cast <chrono :: nanoseconds>(stop - start);
    timpi[k] = double(timp.count()*1e-9);
    corectitudine[k] = verifica_sortare_corecta();
    numeRezultate[k] = tip;
    k += 1;
    copiaza_vector(aux, v, n);
    cout<<"Done.\n\n";
}

void initializare_vectori() {
    cout<<"Se citeste vectorul...\n\n";
    citire(v, n);
    cout<<"Se creaza o copie sortata a vectorului...\n";
    copiaza_vector(v, aux, n);
    copiaza_vector(v, sortat, n);
    sort(sortat, sortat + n);
    cout<<"\nVectorul dat are "<<n;
    if (n >= 20)
        cout<<" de elemente";
    else
        if (n == 1)
            cout<<" element";
        else
            cout<<" elemente";
    cout<<" cuprinse intre ["<<sortat[0]<<", "<<sortat[n-1]<<"].\n\n_______________________________________________________________________________________________________________________\n\n";
}

string evalueazaCorectitudine(int x) {
    if (x == 1)
        return "corect";
    else
        return "gresit";
}

void ordoneazaSortarileDupaTimp() {
    int i, j;
    double aux;
    string aux2;

    for (i = 0; i < k - 1; i += 1)
        for (j = i + 1; j < k; j += 1) {
            if (timpi[i] > timpi[j]) {
                aux = timpi[i];
                timpi[i] = timpi[j];
                timpi[j] = aux;
                aux2 = numeRezultate[i];
                numeRezultate[i] = numeRezultate[j];
                numeRezultate[j] = aux2;
            }
        }
}

void afisare_rezultate() {
    int i;
    system("CLS");
    cout<<"Ordonate crescator, dupa timpi, algoritmii de sortare folositi au avut urmatoarele rezultate: \n\n\n";
    for (i = 0; i < k; i += 1) {
        cout<<numeRezultate[i]<<" - a sortat "<<evalueazaCorectitudine(corectitudine[i])<<" - timpul de executie";
        if (timpi[i] == 0)
            cout<<" < 1e-6.\n\n";
        else
            cout<<" = "<<timpi[i]<<".\n\n";
    }
}

/// Functii folositoare/ necesare pentru algoritmii de sortare.

int maxim(int *numere, int n) {
    int numar_maxim = numere[0], i;
    for (i = 1; i < n; i += 1)
        if (numere[i] > numar_maxim)
            numar_maxim = numere[i];
    return numar_maxim;
}

int partitie(int *v, int s, int d, int pivot) {
    int i = s - 1, j;
    for (j = s; j < d; j += 1)
        if (v[j] < pivot) {
            i += 1;
            interschimbare(v[i], v[j]);
        }
    interschimbare(v[i+1], v[d]);
    return (i + 1);
}

void flip(int *v, int i) {
    int start = 0;
    while (start < i) {
        interschimbare(v[start], v[i]);
        start += 1;
        i -= 1;
    }
}

int maximPancake(int *v, int n) {
    int maxIndex = 0, i;
    for (i = 0; i < n; i += 1)
        if (v[i] > v[maxIndex])
            maxIndex = i;
    return maxIndex;
}

void CountSortR(int *numere, int n, int exponent, int baza) {
    int cifra, i;
    int *temporar = new int[n];
    int *frecventa = new int[baza];

    for (i = 0; i < baza; i += 1)
        frecventa[i] = 0;

    for (i = 0; i < n; i += 1) {
        cifra = (numere[i]/exponent) % baza;
        frecventa[cifra] += 1;
    }
    for (i = 1; i < baza; i += 1)
        frecventa[i] += frecventa[i-1];

    for (i = n - 1; i >= 0; i -= 1) {
        cifra = (numere[i]/exponent) % baza;
        temporar[frecventa[cifra] - 1] = numere[i];
        frecventa[cifra] -= 1;
    }
    for (i = 0; i < n; i += 1)
        numere[i] = temporar[i];
}

/// Algoritmii de sortare.

void QuickSort(int *v, int s, int d) {
    if (s < d) {
        ///int pi = partitie(v, s, d, mediana_medianelor(v, d));
        int pi = partitie(v, s, d, v[d]);
        QuickSort(v, s, pi - 1);
        QuickSort(v, pi + 1, d);
    }
}

void RadixSort(int *v, int n, int baza) {
    int m = maxim(v, n);
    long long int exponent;
    for (exponent = 1; m/exponent > 0; exponent *= baza)
        CountSortR(v, n, exponent, baza);
}

void BubbleSort(int *numere, int n) {
    int i, j;
    bool schimbat;
        for (i = 0; i < n - 1; i += 1) {
                schimbat = false;
                for (j = 0; j < n - i - 1; j += 1)
                    if (numere[j] > numere[j+1]) {
                        interschimbare(numere[j], numere[j + 1]);
                        schimbat = true;
                        }
                if (schimbat == false)
                    break;
        }
}

int PancakeSort(int *v, int n) {
    int dimensiune_curenta, indexMaxim;
    for (dimensiune_curenta = n; dimensiune_curenta > 1; dimensiune_curenta -= 1) {
        indexMaxim = maximPancake(v, dimensiune_curenta);
        if (indexMaxim != dimensiune_curenta - 1) {
            flip(v, indexMaxim);
            flip(v, dimensiune_curenta - 1);
        }
    }
}

void CocktailSort(int *v, int n) {
	bool schimb = true;
	int start = 0, sfarsit = n - 1, i;
	while (schimb) {
		schimb = false;
		for (i = start; i < sfarsit; i += 1) {
			if (v[i] > v[i + 1]) {
                interschimbare(v[i], v[i + 1]);
				schimb = true;
				}
			}
	if (!schimb)
		break;
	schimb = false;
	sfarsit -= 1;
	for (i = sfarsit - 1; i >= start; i -= 1) {
		if (v[i] > v[i + 1]) {
            interschimbare(v[i], v[i + 1]);
			schimb = true;
			}
		}
	start += 1;
	}
}

/// Functii folositoare pentru afisarea rezultatelor in urma sortarii.

string apeleazaQuickSort() {
    QuickSort(v, 0, n-1);
    return "QuickSort";
}

string apeleazaRadixSort() {
    RadixSort(v, n, baza);
    return "RadixSort - baza " + to_string(baza);
}

string apeleazaBubbleSort() {
    BubbleSort(v, n);
    return "BubbleSort";
}

string apeleazaPancakeSort() {
    PancakeSort(v, n);
    return "PancakeSort";
}

string apeleazaCocktailSort() {
    CocktailSort(v, n);
    return "CocktailSort";
}

string apeleazaSort() {
    sort(v, v + n);
    return "Sort";
}

void functiaPrincipala() {

    creareFisier();

    initializare_vectori();

    baza = 2;
    Sortare(apeleazaRadixSort);

    baza = 10;
    Sortare(apeleazaRadixSort);

    baza = 4096;
    Sortare(apeleazaRadixSort);

    baza = 8192;
    Sortare(apeleazaRadixSort);

    Sortare(apeleazaQuickSort);
    Sortare(apeleazaSort);
    Sortare(apeleazaBubbleSort);
    Sortare(apeleazaCocktailSort);
    Sortare(apeleazaPancakeSort);

    ordoneazaSortarileDupaTimp();

    afisare_rezultate();

}

int main() {

    int nr_teste;
    cout<<"Cate teste: ";
    cin>>nr_teste;
    system("CLS");

    for (int i = 1; i <= nr_teste; i += 1) {
            if (i == nr_teste) {
                functiaPrincipala();
		system("PAUSE");
	    }
        else {
            functiaPrincipala();
            system("PAUSE");
            system("CLS");
            k = 0;
        }
    }

    return 0;
}
