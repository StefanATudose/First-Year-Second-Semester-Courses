#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cstring>

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
long long nr_elem, val_max, mediane[3];
long long aux, pivot, pozpivot;
long long stlocal, drlocal, duble;


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

void quicksort(vector <long long> & numere, long long stanga, long long dreapta)
{
    if (stanga < dreapta)
    {

        mediane[0] = uniform_int_distribution <long long>(stanga, dreapta)(rng);
        mediane[1] = uniform_int_distribution <long long>(stanga, dreapta)(rng);
        mediane[2] = uniform_int_distribution <long long>(stanga, dreapta)(rng);
        pivot = max(min(numere[mediane[1]],numere[mediane[2]]), min(max(numere[mediane[1]],numere[mediane[2]]),numere[mediane[0]]));
        if (pivot == numere[mediane[0]])
                pozpivot = mediane[0];
        if (pivot == numere[mediane[1]])
                pozpivot = mediane[1];
        if (pivot == numere[mediane[2]])
                pozpivot = mediane[2];

        ///pozpivot = uniform_int_distribution <long long>(stanga, dreapta)(rng);
        ///pivot = numere[pozpivot];
        ///partitie
        stlocal = stanga;
        drlocal = dreapta-1;
        numere[pozpivot] = numere[dreapta];
        numere[dreapta] = pivot;
        while (true)
        {
            if (pivot <= numere[drlocal])
                drlocal--;
            if (numere[stlocal] < pivot)
                stlocal++;
            else
                if (stlocal < drlocal)
                {
                    aux = numere[stlocal];
                    numere[stlocal] = numere[drlocal];
                    numere[drlocal] = aux;
                }
                else
                    break;
        }
        aux = numere[dreapta];
        numere[dreapta] = numere[stlocal];
        numere[stlocal] = aux;
        drlocal = dreapta;
        aux = 0;
        while(drlocal > stlocal)
        {
            if (numere[drlocal] == pivot)
            {
                aux++;
                numere[drlocal] = numere[dreapta-aux+1];
                numere[dreapta-aux+1] = pivot;
            }
            drlocal--;
        }
        duble = aux;
        while (aux)
        {
            numere[dreapta-aux+1] = numere[stlocal+aux];
            numere[stlocal+aux] = pivot;
            aux--;
        }

        quicksort(numere, stanga, stlocal-1);
        quicksort(numere, stlocal+1+duble, dreapta);
    }
}

int main()
{

    nr_elem = 10000000;
    val_max = 10000000;
    vector <long long> numere;
    numere.reserve(nr_elem);
    ///long long numere[] = {3, 4, 4, 3, 6, 3, 5, 6, 8, 12, 4, 5, 6, 7};
    for (long long i = 0; i < nr_elem; i++)
        numere[i] = uniform_int_distribution <long long>(0, val_max)(rng);

    quicksort(numere, 0, nr_elem-1);
    //for (long long i = 0; i < nr_elem; i++)
      //  cout << numere[i] << ' ' << i << '\n';

    testsort(numere, nr_elem);
    return 0;
}
