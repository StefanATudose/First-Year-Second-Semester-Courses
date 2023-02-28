///tema 7 (din cele propuse): lista dublu inlantuita

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");


class Nod{                                                                  ///pentru testul de lab am ales sa modific clasa Nod

    int info;
    Nod * prev, * next;
public:
    void set_info(int x){info = x;}
    int get_info (){return info;}
    void set_prev(Nod * x){prev = x;}
    Nod* get_prev(){return prev;}
    void set_next(Nod * x) {next = x;}
    Nod * get_next(){return next;}
    Nod(int input){info = input; prev = NULL; next = NULL;}                                                             ///constructor parametrizat
    Nod (const Nod & sursa_copiat) {info = sursa_copiat.info; prev = sursa_copiat.prev; next = sursa_copiat.next;}      ///constructor de copiere
    Nod(){info = 0; prev = NULL; next = NULL;}                                                                          ///constructor de initializare fara parametru
    Nod(bool schimbator){if (schimbator == true){int valoare; cin >> valoare; info = valoare;} else{int valoare; fin >> valoare; cin>>valoare; info = valoare;}}                                                                                     ///constructor parametrizat bool
    ~Nod(){cout << "\nodul cu valoarea " << info << " a fost distrus cu succes!!\n";}                                   ///destructor
    friend class Lista_dublu_inlantuita;
    Nod operator-(){Nod nou; nou.info = -info; return nou;}                                                              ///supraincarcare -(minus)
    Nod & operator--(){info--; return *this;}                                                                           ///--prefix
    Nod operator--(int x){Nod temporar; this->info--; return temporar;}                                                      ///--postfix
    bool operator!=(Nod comparat){return info != comparat.info;}
    operator float() const{return float(info);}                                                                         ///cast float supraincarcare

};


struct nod_de_inserat{                                              ///va fi folosit pentru inserarea unei valori pe o anumita pozitie cu operatorul >>
    int info, poz;
    nod_de_inserat(int inf, int pozitie){info = inf; poz = pozitie;}
    nod_de_inserat(){}
};


class Lista_dublu_inlantuita{
    Nod* primul, * ultimul;
public:
    Lista_dublu_inlantuita(){primul = NULL; ultimul = NULL;}
    void set_primul(Nod * x){ primul = x;}
    void set_ultimul(Nod*x){ultimul = x;}
    Nod * get_primul(){return primul;}
    Nod * get_ultimul(){return ultimul;}
    void adaugare(int info);
    bool adaugare(int info, int poz);
    bool stergere(int poz);
    int lungime();
    Lista_dublu_inlantuita operator+(Lista_dublu_inlantuita lista);
    Lista_dublu_inlantuita & operator>> (nod_de_inserat nod_nou);
    Lista_dublu_inlantuita & operator>> (const int info);
    friend void operator>>(istream &in, Lista_dublu_inlantuita lista)
    {
        int info;
        in >> info;
        lista.adaugare(info);

    }
    ostream &operator<<(ostream & iesire)                                   ///transformare din friend in membra
    {
        if (primul == NULL)
        {
            iesire << "Lista dumneavoastra nu contine niciun element!!!\n";
            return iesire;
        }
        Nod *parcurgere = primul;
        iesire << "Lista dumneavoastra este, dinspre inceput spre sfarsit:\n";
        while ((*parcurgere).get_next() != NULL)
        {
            iesire << (*parcurgere).get_info() << ' ';
            parcurgere = (*parcurgere).get_next();
        }
        iesire << (*parcurgere).get_info() << '\n';
        iesire << "Lista dumneavoastra este, dinspre sfarsit spre inceput:\n";
        while ((*parcurgere).get_prev() != NULL)
        {
            iesire << (*parcurgere).get_info() << ' ';
            parcurgere = (*parcurgere).get_prev();
        }
        iesire << (*parcurgere).get_info() << '\n';
        return iesire;
    }
};

void Lista_dublu_inlantuita::adaugare(int info)
{
    if (primul != NULL)
    {
        Nod * nou = new Nod;
        nou -> info = info;
        nou -> next = NULL;
        nou -> prev = ultimul;
        ultimul -> next = nou;
        ultimul = nou;
    }
    else
    {
        Nod * nou = new Nod;
        nou -> info = info;
        nou -> next = NULL;
        nou -> prev = NULL;
        primul = nou;
        ultimul = nou;
    }
}

bool Lista_dublu_inlantuita::adaugare(int info, int poz)
{
    if (poz == 1 && primul == NULL)
    {
        Nod * nou = new Nod;
        nou -> info = info;
        nou -> next = NULL;
        nou -> prev = NULL;
        primul = nou;
        ultimul = nou;
        return true;
    }
    if (poz == 1 && primul != NULL)
    {
        Nod * nou = new Nod;
        nou -> info = info;
        nou -> next = primul;
        nou -> prev = NULL;
        primul -> prev = nou;
        primul = nou;
        return true;
    }
    if (poz < 1 || (poz>1 && primul == NULL))
        return false;
    if (poz > 1 && primul != NULL)
    {
        int pozlocal = 1;
        Nod * parcurgere = primul->next;
        Nod * trecut = primul;
        if (parcurgere == NULL){
            if (poz == 2)
            {
                Nod * nou = new Nod;
                nou -> info = info;
                nou -> prev = parcurgere;
                nou -> next = NULL;
                parcurgere -> next = nou;
                ultimul = nou;
                return true;
            }
        }
        else
        {
            while (parcurgere->next != NULL)
            {
                pozlocal++;
                if (poz == pozlocal)
                {
                    Nod * nou = new Nod;
                    nou -> info = info;
                    nou -> prev = trecut;
                    nou -> next = parcurgere;
                    trecut -> next = nou;
                    parcurgere -> prev = nou;
                    return true;
                }
                trecut = parcurgere;
                parcurgere = parcurgere -> next;
            }
            pozlocal++;
            if (poz == pozlocal)
            {
                Nod * nou = new Nod;
                nou -> info = info;
                nou -> prev = trecut;
                nou -> next = parcurgere;
                trecut -> next = nou;
                parcurgere -> prev = nou;
                return true;
            }
            if (poz == pozlocal + 1)
            {
                Nod * nou = new Nod;
                nou -> info = info;
                nou -> prev = parcurgere;
                nou -> next = NULL;
                parcurgere -> next = nou;
                ultimul = nou;
                return true;
            }
            return false;
        }
    }
}

bool Lista_dublu_inlantuita::stergere(int poz)
{
    if (primul == NULL)
        return false;
    else
    {
        int pozlocal = 1;
        Nod * parcurgere = primul -> next;
        Nod * trecut = primul;
        if (parcurgere == NULL)
            if (poz == 1)
            {
                primul = NULL;
                ultimul = NULL;
                return true;
            }
            else
                return false;
        else
        {
            if (poz == 1)
            {
                primul = parcurgere;
                parcurgere -> next -> prev = primul;
                parcurgere -> prev = NULL;
                delete trecut;
                return true;
            }
            while (parcurgere -> next != NULL)
            {
                pozlocal++;
                if (pozlocal == poz)
                {
                    trecut -> next = parcurgere -> next;
                    parcurgere -> next -> prev = trecut;
                    delete parcurgere;
                    return true;
                }
                trecut = parcurgere;
                parcurgere = parcurgere -> next;
            }

            pozlocal++;
            if (pozlocal == poz)
            {
                ultimul = trecut;
                if (trecut ->prev != NULL)
                    trecut -> prev -> next = ultimul;
                ultimul -> next = NULL;
                delete parcurgere;

                return true;
            }
            return false;
        }
    }
}

Lista_dublu_inlantuita & Lista_dublu_inlantuita::operator>>(const int info)
{
    (*this).adaugare(info);
    return (*this);
}

Lista_dublu_inlantuita & Lista_dublu_inlantuita::operator>>(nod_de_inserat nodnou)
{
    (*this).adaugare(nodnou.info, nodnou.poz);
    return (*this);
}

int Lista_dublu_inlantuita::lungime()
{
    if (primul == NULL)
        return 0;
    else
    {
        int lung = 0;
        Nod *parcurgere = primul;
        while(parcurgere -> next != NULL)
        {
            lung++;
            parcurgere = parcurgere -> next;
        }
        lung++;
        return lung;
    }
}

Lista_dublu_inlantuita Lista_dublu_inlantuita::operator+(Lista_dublu_inlantuita lista)
{
    Lista_dublu_inlantuita listanoua;
    if (this -> primul != NULL)
    {
        //Nod * primnou = new Nod((*this).primul -> info);
        //listanoua.primul = primnou;
        Nod * parcurgere = this->primul;
        while (parcurgere -> next != NULL)
        {
            listanoua >> (parcurgere -> info);
            parcurgere = parcurgere -> next;
        }
        listanoua >> (parcurgere -> info);
    }
    if (lista.primul != NULL)
    {
        Nod * parcurgere = lista.primul;
        while (parcurgere -> next != NULL)
        {
            listanoua >> (parcurgere -> info);
            parcurgere = parcurgere -> next;
        }
        listanoua >> (parcurgere -> info);
    }

    ///listanoua.primul;
    return listanoua;

}

int x, nrlistacurenta, nrlistetotale = -1;

int meniu_alegere_operatii()
{
    int x;
    cout << "Pentru a crea o lista noua -> Introduceti tasta 1\n";
    cout << "Pentru a afisa o lista -> Introduceti tasta 2\n";
    cout << "Pentru a adauga un element la o lista -> Introduceti tasta 3\n";
    cout << "Pentru a sterge un element dintr-o lista -> Introduceti tasta 4\n";
    cout << "Pentru a concatena doua liste -> Introduceti tasta 5\n";
    cout << "Pentru a afisa lungimea unei liste -> Introduceti tasta 6\n";
    cout << "Pentru a inchide programul -> Introduceti numarul 7\n";
    cin >> x;
    return x;
}

int y;

void terminare_eroare(){
    cout << "\nProgramul a fost terminat brusc, din cauza unei neconformari cu instructiunile!";
    exit(1);
}

int nrvalori, valoare, nroperatie, info, poz;
nod_de_inserat nod_cu_poz_specificata;


int main()
{

    cout << "Buna ziua! Acest program face accesibila gestionarea listelor dublu inlantuite!\nIndicatii: Programul poate crea pana la maximum 10 liste inlantuite.\n";
    cout << "Daca doriti sa treceti la operatiile posibile, tastati un numar nenul: ";
    Lista_dublu_inlantuita toate[10];
    cin >> x;
    while (x)
    {
        nroperatie = meniu_alegere_operatii();
        if (nroperatie == 1)
        {
            nrlistetotale++;
            nrlistacurenta = nrlistetotale;
            cout <<"\nLista a fost creata!\n";
            cout <<"Doriti sa o initializati?\n Da - introduceti 1        Nu - introduceti 2:\n";
            cin >> y;
            if (y == 1)
            {
                cout << "Cu cate valori doriti sa fie initializata lista?(introduceti un intreg)\n";
                cin >> nrvalori;
                cout << "\nIntroduceti " << nrvalori << " valori:\n";
                while (nrvalori)
                {
                    cin >> valoare;
                    toate[nrlistacurenta] >> valoare;
                    nrvalori--;
                }
                cout << "\nLista a fost initializata cu succes! Veti fi redirectionat catre meniul principal!\n\n";
            }
            if (y != 1 && y != 2)
                terminare_eroare();
        }
        if (nroperatie == 2)
        {
            cout << "\nExista " << nrlistetotale + 1 << " liste dintre care puteti alege.\n";
            cout << "Introduceti un numar cuprins intre " << 1 << " si " << nrlistetotale+1 << " pentru a selecta una dintre ele:\n";
            cin >> nrlistacurenta;
            nrlistacurenta--;
            if (nrlistacurenta < 0 || nrlistacurenta > nrlistetotale)
                terminare_eroare();
            else
            {
                ///cout << toate[nrlistacurenta];
                toate[nrlistacurenta] << cout;
                cout << "\nVeti fi redirectionat catre meniul principal!\n\n";
            }
        }
        if (nroperatie == 3)
        {
            cout << "\nExista " << nrlistetotale + 1 << " liste dintre care puteti alege.\n";
            cout << "Introduceti un numar cuprins intre " << 1 << " si " << nrlistetotale+1 << " pentru a selecta una dintre ele:\n";
            cin >> nrlistacurenta;
            nrlistacurenta--;
            cout << "\nCate valori doriti sa inserati?\n";
            cin >> nrvalori;
            cout << "\nVa rugam inserati fiecare valoare dorita in lista sub forma unei perechi de 2 elemente, unde primul element este numarul intreg pe care doriti sa il inserati, iar al doilea este pozitia in lista inainte de care doriti inserata valoarea respectiva.\n";
            cout << "Elementele sunt indexate de la 1!\n";
            cout << "Perechile cu o pozitie mai mare decat numarul de elemente al listei nu vor fi adaugate!\n";
            cout << "Daca nu doriti sa specificati o pozitie, va rugam sa introduceti numarul 0 pe a doua pozitie a perechii (valoarea va fi adaugata pe ultima pozitie a listei)\n";
            cout << "Lista aleasa are " << toate[nrlistacurenta].lungime() << " elemente!\n";
            if (nrlistacurenta < 0 || nrlistacurenta > nrlistetotale)
                terminare_eroare();
            else
            {
                while (nrvalori)
                {
                    cin >> info >> poz;
                    if (poz != 0)
                    {
                        nod_cu_poz_specificata.info = info;
                        nod_cu_poz_specificata.poz = poz;
                        toate[nrlistacurenta] >> nod_cu_poz_specificata;
                        nrvalori--;
                    }
                    if (poz == 0)
                    {
                        toate[nrlistacurenta] >> info;
                        nrvalori--;
                    }
                }
                cout << "\nVeti fi redirectionat catre meniul principal!\n\n";
            }
        }
        if (nroperatie == 4)
        {
            cout << "\nExista " << nrlistetotale + 1 << " liste dintre care puteti alege.\n";
            cout << "Introduceti un numar cuprins intre " << 1 << " si " << nrlistetotale+1 << " pentru a selecta una dintre ele:\n";
            cin >> nrlistacurenta;
            nrlistacurenta--;
            cout << "\nLista aleasa are " << toate[nrlistacurenta].lungime() << " elemente!\n";
            cout << "Alegeti un element dintre acestea pentru a-l sterge! (Elementele sunt indexate de la 1)\n";
            cin >> poz;
            if (nrlistacurenta < 0 || nrlistacurenta > nrlistetotale)
                terminare_eroare();
            else
            {
                if (toate[nrlistacurenta].stergere(poz))
                    cout << "Elementul a fost sters cu succes! Veti fi redirectionat catre meniul principal!\n";
                else
                    cout << "Elementul nu a putut fi sters deoarece pozitia introdusa nu se afla in lista! Veti fi redirectionat catre meniul principal!\n\n";
            }
        }
        if (nroperatie == 5)
        {
            cout << "\nExista " << nrlistetotale + 1 << " liste dintre care puteti alege.\n";
            cout << "Introduceti doua numere cuprinse intre " << 1 << " si " << nrlistetotale+1 << " pentru a selecta DOUA dintre ele:\n";
            cin >> nrlistacurenta >> nrvalori;
            nrlistacurenta--;
            nrvalori--;
            if (nrlistacurenta < 0 || nrlistacurenta > nrlistetotale || nrvalori < 0 || nrvalori > nrlistetotale)
                terminare_eroare();
            else
            {
                nrlistetotale++;
                toate[nrlistetotale] = toate[nrlistacurenta] + toate[nrvalori];
                cout << "Noua lista formata prin concatenarea celor doua introduse a fost generata! Ea este lista cu numarul " << nrlistetotale + 1 << "! Veti fi Veti fi redirectionat catre meniul principal!\n\n";
            }
        }
        if (nroperatie == 6)
        {
            cout << "\nExista " << nrlistetotale + 1 << " liste dintre care puteti alege.\n";
            cout << "Introduceti un numar cuprins intre " << 1 << " si " << nrlistetotale+1 << " pentru a selecta una dintre ele:\n";
            cin >> nrlistacurenta;
            nrlistacurenta--;
            if (nrlistacurenta < 0 || nrlistacurenta > nrlistetotale)
                terminare_eroare();
            else
                cout << "Lungimea listei selectate este de " << toate[nrlistacurenta].lungime() << " elemente! Veti fi redirectionat catre meniul principal!\n\n";
        }
        if (nroperatie == 7)
        {
            cout << "Program finalizat cu succes!\n";
            break;
        }
        if (nroperatie < 1 || nroperatie > 7)
            terminare_eroare();

    }


    return 0;
}
