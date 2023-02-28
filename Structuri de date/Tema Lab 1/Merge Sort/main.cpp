#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cstring>

using namespace std;

long long nr_elem, val_max;

void testsort(vector <long long> & numere, long long nr_elem)
{
    bool sortat = true;
    for (long long i = 0; i < nr_elem-1; i++)
        if (numere[i] > numere[i+1])
            sortat = false;
    if (sortat)
        cout << "MERGE!!";
    else
        cout << "nu merge";
}

void mergesort(vector <long long> & numere, long long st, long long dr, vector <long long> & vectaux)
{
    /*
    if (dr > 250000)
    {
        cout << "\nNu pot sorta atat de mult cu mergesort (limita: 250.000)\n";
        return;
    }*/
    if (st == dr-1)
    {
        if (numere[st] > numere[dr])
        {
            long long aux = numere[st];
            numere[st] = numere[dr];
            numere[dr] = aux;
        }
        return;
    }
    else if (st == dr)
        return;
    long long mijloc = st + (dr-st)/2;
    mergesort (numere, st, mijloc, vectaux);
    mergesort (numere, mijloc+1, dr, vectaux);
    long long i = st, j = mijloc+1, aux = 0;
    while (i <= mijloc && j <= dr)
        if (numere[i] < numere[j])
            vectaux[aux++] = numere[i++];
        else
            vectaux[aux++] = numere[j++];
    while (j <= dr)
        vectaux[aux++] = numere[j++];
    while (i <= mijloc)
        vectaux[aux++] = numere[i++];
    for (aux = 0; aux < dr-st+1; aux++)
        numere[aux+st] = vectaux[aux];

}


int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    nr_elem = 1000000000;
    val_max = 10000000;
    vector <long long> numere;
    vector <long long> vectaux;
    vectaux.reserve(nr_elem);
    numere.reserve(nr_elem);
    for (long long i = 0; i < nr_elem; i++)
        numere[i] = uniform_int_distribution <long long>(0, val_max)(rng);
    mergesort(numere, 0, nr_elem-1, vectaux);
    testsort(numere, nr_elem);
    return 0;
}
