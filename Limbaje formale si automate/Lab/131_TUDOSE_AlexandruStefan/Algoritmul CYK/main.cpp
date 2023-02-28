/*
Exemplu input                   //neterminalul de start trebuie sa fie neaparat S
baabca 4                        //cuvantul testat si numarul de neterminale
1 S BA                          //numarul de productii al neterminalului curent(elementul drept), elementul stang(neterminalul din care plec), si terminalele/neterminalele in care se deriveaza
3 A a BA CA
3 B b AA AB
3 C c BC BB
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

ifstream fin("cyk.in");
ofstream fout("cyk.out");

unordered_map <string, vector <char>> productii;
vector <vector <vector <char>>> tabel;

string cuvant, membruDreapta, prod;
int nrNeterminale, nrProductii, lungCuv, i, j, k;
char membruStanga;

int main()
{

    fin >> cuvant >> nrNeterminale;
    while (nrNeterminale--){
        fin >> nrProductii;
        fin >> membruStanga;
        while (nrProductii--){
            fin >> membruDreapta;
            productii[membruDreapta].push_back(membruStanga);
        }
    }
    lungCuv = cuvant.length();
    vector <vector <char>> linieTabel(lungCuv);
    tabel.assign(lungCuv, linieTabel);

    for (i = 0; i < lungCuv; i++){
        string litera;
        litera += cuvant[i];
        for (k = 0; k < productii[litera].size(); k++)
            tabel[i][0].push_back(productii[litera][k]);
    }
    for (j = 1; j < lungCuv; j++){

        for (i = 0; i + j < lungCuv; i++){

            vector <string> aux;
            for (k = 0; k < j; k++){
                for (auto h : tabel[i][k]){
                    prod = h;
                    for (auto g : tabel[i+k+1][j-k-1]){
                        prod += g;
                        aux.push_back(prod);
                        prod = h;
                    }
                }
            }
            unordered_set <char> prodUnice;
            for (auto h : aux){
                for (auto g : productii[h])
                    if (prodUnice.find(g) == prodUnice.end()){
                        prodUnice.insert(g);
                        tabel[i][j].push_back(g);
                    }
            }
        }
    }
    /*
    for (j = 0; j < 6; j++){
        for (i = 0; i + j < lungCuv; i++){
            fout << '{';
            for (auto g : tabel[i][j])
                fout << g << ',';
            fout << "}  ";
        }
        fout << '\n';
    }*/         ///decomentati asta daca doriti sa vedeti matricea
    if (find(tabel[0][lungCuv-1].begin(), tabel[0][lungCuv-1].end(), 'S') != tabel[0][lungCuv-1].end())
        fout << "DA!";
    else
        fout << "NU!";
    return 0;
}
