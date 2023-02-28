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


void RadixSort10(vector <long long> & numere, long long nr_elem, long long val_max)
{
    vector <long long> frecventa[(1 << 12)];
    int zece = 1, j, i, k;
    while (zece <= val_max)
    {
        for (i = 0; i < nr_elem; i++)
            frecventa[numere[i] / zece % (1 << 12)].push_back(numere[i]);
        i = 0;
        for (j = 0; j < (1 << 12); j++)
        {
            k = 0;
            while (k < frecventa[j].size())
                numere[i++] = frecventa[j][k++];
            frecventa[j].clear();
        }
        zece *= (1 << 12);
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
    val_max = 100000;
    vector <long long> numere;
    numere.reserve(nr_elem);
    for (long long i = 0; i < nr_elem; i++)
        numere[i] = uniform_int_distribution <long long>(0, val_max)(rng);
    RadixSort10(numere, nr_elem, val_max);
    //for (int i = 0; i < nr_elem; i++)
     //   cout << numere[i] << ' ' << i << '\n';
    testsort(numere, nr_elem);
    return 0;
}
