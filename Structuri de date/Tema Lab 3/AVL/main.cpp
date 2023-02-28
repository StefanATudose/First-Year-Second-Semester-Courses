#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");

int BF, BFst, BFdr;

struct nod
{
    int height;
    int info;
    nod * left, * right;
    nod (){left = nullptr; right = nullptr;}
    nod (int _info){left = nullptr; right = nullptr; info = _info; height = 0;}
} * aux1, *aux2;

int getInalt(nod * nodd){
    if (nodd == nullptr)
        return -1;
    else
        return nodd->height;

}

int getBF(nod * noddd){
    if (noddd == nullptr) return 0;
    return getInalt(noddd->left) - getInalt(noddd->right);
}

nod * rotStanga(nod * & rotit){
    aux1 = rotit -> right;
    aux2 = aux1->left;
    aux1 -> left = rotit;
    rotit -> right = aux2;
    rotit -> height = 1 + max (getInalt(rotit->left), getInalt(rotit->right));
    aux1 -> height = 1 + max(getInalt(aux1->left), getInalt(aux1-> right));
    return aux1;
}

nod *rotDreapta (nod * & rotit){
    aux1 = rotit -> left;
    aux2 = aux1 -> right;
    aux1 -> right = rotit;
    rotit-> left = aux2;
    rotit -> height = 1 + max (getInalt(rotit->left), getInalt(rotit->right));
    aux1 -> height = 1 + max(getInalt(aux1->left), getInalt(aux1-> right));
    return aux1;
}

nod * inserare(nod * & radacina, int valoare){
    if (radacina == nullptr){
        radacina = new nod(valoare);
        return radacina;
    }
    else if (valoare > radacina -> info)
        radacina -> right = inserare (radacina -> right, valoare);
    else if (valoare < radacina -> info)
        radacina -> left = inserare(radacina -> left, valoare);
    radacina -> height = 1 + max(getInalt(radacina->left), getInalt(radacina->right));

    BF = getBF(radacina);

    if (BF > 1 && valoare < radacina -> left -> info){ ///nu mai testez nulitalea fiului stang ptc imi e confirmata de BF pozitiv
        radacina = rotDreapta(radacina);
        return radacina;
    }
    if (BF > 1 && valoare > radacina -> left -> info){
        radacina -> left = rotStanga(radacina->left);
        radacina = rotDreapta(radacina);
        return radacina;
    }
    if (BF < -1 && valoare > radacina -> right -> info){
        radacina = rotStanga(radacina);
        return radacina;
    }
    if (BF < -1 && valoare < radacina -> right -> info){
        radacina-> right = rotDreapta(radacina->right);
        radacina = rotStanga(radacina);
        return radacina;
    }
    return radacina;
}
/*
nod * succStergere(nod * tata, nod * & plecare, bool directie){
    if (plecare -> left == nullptr){
        if (directie == 0)
            tata -> left = plecare -> right;
        else
            tata -> right = plecare -> right;
        return plecare;
    }
    else{
        aux1 = succStergere(plecare, plecare->left, 0);
        aux1->height = 1 + max(getInalt(aux1->left), getInalt(aux1->right));
        return aux1;
    }

}
*/
nod * cautare(nod * radacina, int valoare){
    if (radacina == nullptr){
        return nullptr;
    }
    if (valoare > radacina ->info){
        return cautare (radacina -> right, valoare);
    }
    else if (valoare < radacina ->info)
        return cautare(radacina -> left, valoare);
    else
        return radacina;
}

nod * succStergere(nod * plec){
    if (plec->left == nullptr)
        return plec;
    else
        return succStergere(plec->left);
}

int cautSuccesor(nod * curent, int valoare){
    if (curent -> info == valoare)
        return curent->info;
    nod * fiu;
    if (curent-> left != nullptr && curent -> right != nullptr){
        if (curent -> info > valoare) fiu = curent -> left;
        else fiu = curent -> right;
    }
    else if (curent -> left != nullptr) fiu = curent -> left;
    else if (curent -> right != nullptr) fiu = curent -> right;
    else return curent -> info;

    int best = cautSuccesor(fiu, valoare);
    if (best >= valoare && curent -> info >= valoare)
        return min(best, curent -> info);
    else
        return max(best, curent -> info);

}

int cautPredecesor(nod * curent, int valoare){
    if (curent -> info == valoare)
        return curent->info;
    nod * fiu;
    if (curent-> left != nullptr && curent -> right != nullptr){
        if (curent -> info > valoare) fiu = curent -> left;
        else fiu = curent -> right;
    }
    else if (curent -> left != nullptr) fiu = curent -> left;
    else if (curent -> right != nullptr) fiu = curent -> right;
    else return curent -> info;

    int best = cautPredecesor(fiu, valoare);
    if (best <= valoare && curent -> info <= valoare)
        return max(best, curent -> info);
    else
        return min(best, curent -> info);

}
/*                  ce scrisesem inainte de partea de AVL
nod * stergere(nod * tata, nod * & radacina, int valoare, bool directie){
    if (radacina == nullptr)
        return radacina;
    if (radacina -> info > valoare){
        radacina -> left = stergere(radacina, radacina -> left, valoare, 0);
    }
    else if (radacina -> info < valoare){
        radacina -> right = stergere(radacina, radacina ->right, valoare, 1);
    }
    else{
        if (radacina -> left == nullptr || radacina -> right == nullptr){
            if (tata == nullptr){
                radacina = (radacina -> left == nullptr) ? (radacina -> right) : (radacina -> left);
            }
            else{
                if (directie == 1)
                    tata -> right = (radacina -> left == nullptr) ? (radacina->right) : (radacina->left);
                else
                    tata -> left = (radacina -> left == nullptr) ? (radacina->right) : (radacina->left);
            }
        }
        else{
            nod * succ = succStergere(radacina, radacina -> right, 1);
            radacina->height = 1 + max(getInalt(radacina -> left), getInalt(radacina-> right));
            if (tata != nullptr){
                if (directie == 1)
                    tata -> right = succ;
                else
                    tata -> left = succ;
            }
            else
                radacina -> info = succ -> info;

        }
    }
    //if (radacina == nullptr){
     //   return radacina;
    //}
    return radacina;
}
*/

nod * stergere(nod * & radacina, int valoare){
    if (radacina == nullptr){
        return radacina;
    }
    else if(radacina -> info < valoare){
        radacina -> right = stergere(radacina -> right, valoare);
    }
    else if(radacina -> info > valoare){
        radacina -> left = stergere(radacina->left, valoare);
    }
    else{
        if (radacina -> left == nullptr || radacina -> right == nullptr){
            nod * fiu = (radacina -> left == nullptr) ? (radacina ->right) : (radacina ->left);
            radacina = fiu;
        }
        else{
            nod * succ = succStergere(radacina->right);
            radacina -> info = succ-> info;
            radacina -> right = stergere(radacina -> right, succ->info);
        }
    }
    if (radacina == nullptr)
        return radacina;
    radacina->height = 1+ max(getInalt(radacina->left), getInalt(radacina->right));
    BF = getBF(radacina);
    BFst = getBF(radacina -> left);
    BFdr = getBF(radacina -> right);
    if (BF > 1 && BFst > 0){
        radacina = rotDreapta(radacina);
        return radacina;
    }
    if (BF > 1 && BFst < 0){
        radacina -> left = rotStanga(radacina->left);
        radacina = rotDreapta(radacina);
        return radacina;
    }
    if (BF < -1 && BFdr < 0){
        radacina = rotStanga(radacina);
        return radacina;
    }
    if (BF < -1 && BFdr > 0){
        radacina -> right = rotDreapta(radacina-> right);
        radacina = rotStanga(radacina);
        return radacina;
    }
    return radacina;

}

void afis6(nod * radacina, int st, int dr)
{
    if (radacina ->left != nullptr && radacina -> info > st)
        afis6(radacina->left, st, dr);
    if (st <= radacina ->info && radacina ->info <= dr)
        fout << radacina -> info << ' ';
    if (radacina -> right != nullptr && radacina-> info < dr)
        afis6(radacina -> right, st, dr);
    return;
}

int nrOperatii, tipOperatie, nr1, nr2;
bool init = true;

int main()
{
    fin >> nrOperatii;
    nod * rezFct1, *rezFct2, *radacina = nullptr;
    while (nrOperatii--)
    {
        fin >> tipOperatie;
        if (tipOperatie == 1){
            fin >> nr1;
            inserare(radacina, nr1);
            continue;
        }
        if (tipOperatie == 2){
            fin >> nr1;
            stergere(radacina, nr1);
            continue;
        }
        if (tipOperatie == 3){
            fin >> nr1;
            rezFct1 = cautare(radacina, nr1);
            if (rezFct1 != nullptr)
                fout << 1 << '\n';
            else
                fout << 0 << '\n';
            continue;

        }
        if (tipOperatie == 4){
            fin >> nr1;
            fout << cautPredecesor(radacina, nr1) << '\n';
            continue;

        }
        if (tipOperatie == 5){
            fin >> nr1;
            fout << cautSuccesor(radacina, nr1) << '\n';
            continue;
        }
        if (tipOperatie == 6){
            fin >> nr1 >> nr2;
            afis6(radacina, nr1, nr2);
            fout << '\n';
            continue;
        }

    }

    return 0;
}
