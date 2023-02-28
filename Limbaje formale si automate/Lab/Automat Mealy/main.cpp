#include <fstream>                                  ///automat mealy determinist
#include <vector>                                   ///citire din fisier
#include <string>
using namespace std;

ifstream fin("mealy.in");
ofstream fout("mealy.out");

struct vecin
{
    int destinatie;
    string output;
    char nume;
} intrat;

int nrstari, nrtranzitii, i, input, nrteste, start, nrfinale, copystart;
bool gasittranz, gasittot;

int main()
{
    fin >> nrstari >> nrtranzitii;
    string test;
    vector <vecin> adiacenta[nrstari];
    for (i = 0; i < nrtranzitii; i++)
    {
        fin >> input >> intrat.destinatie >> intrat.nume >> intrat.output;
        adiacenta[input].push_back(intrat);
    }
    fin >> start >> nrfinale;
    vector <int> finale(nrfinale, 0);
    for (i = 0; i < nrfinale; i++)
        fin >> finale[i];
    fin >> nrteste;

    while (nrteste--)
    {
        fin >> test;
        copystart = start;
        vector <int> traseu;
        vector <string> afis;
        traseu.push_back(start);
        for (i = 0; i < test.length(); i++)
        {
            gasittranz = 0;
            for (auto j : adiacenta[copystart])
                if (j.nume == test[i])
                {
                    gasittranz = 1;
                    copystart = j.destinatie;
                    traseu.push_back(j.destinatie);
                    afis.push_back(j.output);
                    break;
                }
            if (!gasittranz)
                break;
        }

        if (i == test.length())
        {
            gasittot = 0;
            for (auto j : finale)
                if (copystart == j)
                {
                    fout << "DA\n";
                    for (auto k : afis)
                        fout << k;
                    fout << "\nTraseu: ";
                    for (auto k : traseu)
                        fout << k;
                    fout << '\n';
                    gasittot = 1;
                    break;
                }
            if (!gasittot)
                fout << "NU\n";
        }
        else
            fout << "NU\n";
    }
    return 0;
}
