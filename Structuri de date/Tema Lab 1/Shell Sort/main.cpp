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

void ShellSort(vector <long long> & numere, long long nr_elem)
{
    int i, j, aux;
    for (int gap = nr_elem / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < nr_elem; i++)
        {
            aux = numere[i];
            for (j = i; j >= gap && numere[j-gap] > aux; j -= gap)
                numere[j] = numere[j-gap];
            numere[j] = aux;
        }
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
    val_max = 100;
    vector <long long> numere;
    numere.reserve(nr_elem);
    for (long long i = 0; i < nr_elem; i++)
        numere[i] = uniform_int_distribution <long long>(0, val_max)(rng);
    ShellSort(numere, nr_elem);
    //for (int i = 0; i < nr_elem; i++)
     //   cout << numere[i] << ' ' << i << '\n';
    testsort(numere, nr_elem);
    return 0;
}
