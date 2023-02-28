#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cstring>
#include <math.h>


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

void CountSort(vector <long long> & numere, long long nr_elem, long long val_max)
{
    long long i;
    vector <long long> frecventa;
    frecventa.assign(val_max+1, 0);
    for ( i = 0; i < nr_elem; i++)
        frecventa[numere[i]]++;
    int poz = 0;

    for (i = 0; i <= val_max; i++)
        while (frecventa[i])
        {
            numere[poz++] = i;
            frecventa[i]--;
        }
}



int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ///cout << "Radix Sort\nIntroduceti, va rog, numarul de elemente ce urmeaza a fi generate aleator, apoi sortate: ";
    ///cin >> nr_elem;
    ///cout << "\nAcum introduceti, va rog, valoarea maxima a elementelor: ";
    ///cin >> val_max;
    nr_elem = 10000000;
    val_max = 10000000; ///NU 10^6
    vector <long long> numere;
    numere.reserve(nr_elem);
    for (long long i = 0; i < nr_elem; i++)
        numere[i] = uniform_int_distribution <long long>(0, val_max)(rng);
    CountSort(numere, nr_elem, val_max);
    ///for (long long i = 0; i < nr_elem; i++)
     ///   cout << numere[i] << ' ' << i << '\n';
    testsort(numere, nr_elem);
    return 0;
}
