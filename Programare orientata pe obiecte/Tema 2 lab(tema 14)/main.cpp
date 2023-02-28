#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

class proces{
protected:
    int nrProces;
    string reclamant, reclamat;
    static int cateProcese;                                                         ///variabila statica
public:
    /*functie virtuala pentru modificarea stadiului, care va fi suprascrisa de clasele derivate*/
    virtual void modifState(){};

    /*constructori si constructori parametrizati*/
    static void plusProces(){cateProcese++;};                                       ///functii statice
    static void minusProces(){cateProcese--;};
    proces(){nrProces = cateProcese; reclamant = "necunoscut"; reclamat = "necunoscut"; plusProces();};
    proces(string victima, string agresor = "necunoscut"){nrProces = cateProcese; reclamant = victima; reclamat = agresor; plusProces();};

    /*constructor de copiere*/
    proces (const proces & ob){nrProces = cateProcese; reclamant = ob.reclamant; reclamat = ob.reclamat; plusProces();};

    /*destructor (virtual pentru downcasting)*/
    virtual ~proces(){minusProces(); cout << "\nAm sters un proces\n";};

    /*supraincarcare =, >>, <<*/
    proces & operator=(proces & ob);
    friend istream & operator>>(istream &in, proces & ob);
    friend ostream & operator<<(ostream &out, proces & ob);
};

class proces_civil : public proces{
    double dauneMorale, dauneMateriale;
    int nrMartori;
    bool stadiu;
public:
    /*cerinte suplimentare specifice temei*/
    void modifState(){stadiu = 1-stadiu;};
    int taxaTimbru(){return dauneMorale/10 + dauneMateriale/10;};

    /*constructori si constructori parametrizati*/
    proces_civil() : proces(){dauneMorale = 0; dauneMateriale = 0; nrMartori = 0; stadiu = 0;}          ///lista de  initializare pt constructori
    proces_civil(double Morale, double Materiale, int martori, string victima = "necunoscut", string agresor = "necunoscut")
    /*pentru mai sus*/      : proces(victima, agresor){dauneMateriale = Materiale; dauneMorale = Morale; nrMartori = martori; stadiu = martori > 5 ? 1 : 0;};

    /*constructor de copiere*/                  ///lista de  initializare pt constructori
    proces_civil(const proces_civil &ob) : proces(ob){dauneMorale = ob.dauneMorale; dauneMateriale = ob.dauneMateriale; nrMartori = ob.nrMartori; stadiu = ob.stadiu;};

    /*destructor*/
    ~proces_civil(){cout << "\nAm sters un proces civil\n";};

    /*supraincarcare =, >>, <<*/
    proces_civil & operator=(proces_civil & ob);
    friend istream & operator>>(istream &in, proces_civil & ob);
    friend ostream & operator<<(ostream &out, proces_civil & ob);
};

class proces_penal : public proces{
    int dovezi;
    bool stadiu;
public:
    void modifState(){stadiu = 1-stadiu;};

    /*constructori si constructori parametrizati*/
    proces_penal() : proces(){dovezi = 0; stadiu = 0;};
    proces_penal(int proof, string victima = "necunoscut", string agresor = "necunoscut") : proces(victima, agresor){
    /*pentru mai sus*/ dovezi = proof; stadiu = proof > 25 ? 1 : 0;};

    /*constructor de copiere*/
    proces_penal(const proces_penal &ob) : proces(ob){dovezi = ob.dovezi; stadiu = ob.stadiu;};         ///lista de  initializare pt constructori

    /*destructor*/
    ~proces_penal(){cout << "\nAm sters un proces penal\n";};

    /*supraincarcare =, >>, <<*/
    proces_penal & operator=(proces_penal & ob);
    friend istream & operator>>(istream &in, proces_penal & ob);
    friend ostream & operator<<(ostream &out, proces_penal & ob);
};

int proces::cateProcese(0);
int nrProceseTotale, i, tip, optiune;

int afisMeniu()
{
    int optiune;
    cout << "\nMeniu interactiv\n\n";
    cout << "Pentru adaugare proces la lista -> tasta 1\n";
    cout << "Pentru afisare lista procese -> tasta 2\n";
    cout << "Pentru afisarea procesului cu taxa timbru maxima-> tasta 3\n";
    cout << "Pentru afisarea unui singur proces din lista -> tasta 4\n";
    cout << "Pentru modificarea stadiului unui proces -> tasta 5\n";
    cout << "Pentru terminarea programului -> tasta 6\n";
    cin >> optiune;
    return optiune;
}


int main()
{
    cout << "Buna ziua! Proiectul meu centralizeaza o lista de procese, fie penale, civile, sau neclasificate!\n";
    cout << "Pentru inceput, introduceti numarul de procese care sa fie introduse in lista: ";
    vector <proces*> procesList;                                ///upcast in vector (pointeri de tip baza arata spre derivate)
    cin >> nrProceseTotale;
    if (nrProceseTotale)
    {
        cout << "Pentru fiecare dintre cele " << nrProceseTotale << " procese, introduceti datele caracteristice:\n";
        for (i = 0; i < nrProceseTotale; i++)
        {
            cout << "Tip de proces: 1-nespecificat; 2-civil; 3-penal: ";
            cin >> tip;
            if (tip == 1)
            {
                proces *nou = new proces;
                cin >> *nou;
                procesList.push_back(nou);
            }
            if (tip == 2)
            {
                proces_civil *nou = new proces_civil;
                cin >> *nou;
                procesList.push_back(nou);
            }
            if (tip == 3)
            {
                proces_penal *nou = new proces_penal;
                cin >> *nou;
                procesList.push_back(nou);
            }
        }
    }
    while (true)
    {
        try
        {
            optiune = afisMeniu();
            if (optiune < 1 || optiune > 6)
                throw optiune;
            if (optiune == 1)
            {
                cout << "Tip de proces: 1-nespecificat; 2-civil; 3-penal: ";
                cin >> tip;
                if (tip == 1)
                {
                    proces *nou = new proces;
                    cin >> *nou;
                    procesList.push_back(nou);
                }
                if (tip == 2)
                {
                    proces_civil *nou = new proces_civil;
                    cin >> *nou;
                    procesList.push_back(nou);
                }
                if (tip == 3)
                {
                    proces_penal *nou = new proces_penal;
                    cin >> *nou;
                    procesList.push_back(nou);
                }
                nrProceseTotale++;
            }
            if (optiune == 2)
            {
                if (procesList.size()== 0)
                    cout << "Lista e goala!\n";
                else
                {
                    for (auto i = procesList.begin(); i < procesList.end(); i++)
                    {
                        if (typeid(**i) == typeid(proces))                                      ///downcast in afisarea elementelor
                            cout << *dynamic_cast<proces*>(*i);                                 ///pointerul baza care inainte a fost upcastat se intoarce la tipul derivat
                        if (typeid(**i) == typeid(proces_civil))
                            cout << *dynamic_cast<proces_civil*>(*i);
                        if (typeid(**i) == typeid(proces_penal))
                            cout << *dynamic_cast<proces_penal*>(*i);
                    }
                }

            }
            if (optiune == 3)
            {
                int maxim = -1, pozmax;
                for (int i = 0; i < procesList.size(); i++)
                    if (typeid(*(procesList[i])) == typeid(proces_civil))
                        if ((*dynamic_cast<proces_civil*>(procesList[i])).taxaTimbru() > maxim)
                        {
                            maxim = (*dynamic_cast<proces_civil*>(procesList[i])).taxaTimbru();
                            pozmax = i;
                        }
                cout << "Procesul cu taxa pe timbru maxima este cel cu numarul " << pozmax << ", avand taxa egala cu " << maxim <<'\n';

            }
            if (optiune == 4)
            {
                cout << "Alegeti un indice de lista intre 0 si " << procesList.size()-1 <<": ";
                try {
                    cin >> i;
                    if (i < 0 || i >= procesList.size())
                        throw i;
                    if (typeid(*procesList[i]) == typeid(proces))
                        cout << *dynamic_cast<proces*>(procesList[i]);
                    if (typeid(*procesList[i]) == typeid(proces_civil))
                        cout << *dynamic_cast<proces_civil*>(procesList[i]);
                    if (typeid(*procesList[i]) == typeid(proces_penal))
                        cout << *dynamic_cast<proces_penal*>(procesList[i]);
                }
                catch (int i)
                {
                    cout << "Ati ales un proces inexistent! Incercati din nou!\n";
                }
            }
            if (optiune == 5)
            {
                cout << "Alegeti un indice de lista intre 0 si " << procesList.size()-1 <<": ";
                try {
                    cin >> i;
                    if (i < 0 || i >= procesList.size())
                        throw i;
                    if (typeid(*procesList[i]) == typeid(proces))
                        cout << "Ati ales un proces neidentificat care nu are stadiu! Incercati din nou!\n";
                    if (typeid(*procesList[i]) == typeid(proces_civil))
                    {
                        (*dynamic_cast<proces_civil*>(procesList[i])).modifState();
                        cout << "Stadiul procesului cu numarul " << i << " a fost modificat cu succes!!!\n";
                    }

                    if (typeid(*procesList[i]) == typeid(proces_penal))
                    {
                        (*dynamic_cast<proces_penal*>(procesList[i])).modifState();
                        cout << "Stadiul procesului cu numarul " << i << " a fost modificat cu succes!!!\n";
                    }

                }
                catch (int i)
                {
                    cout << "Ati ales un proces inexistent! Incercati din nou!\n";
                }
            }
            if (optiune == 6)
                return 0;
        }

        catch (int optiune)
        {
            cout << "Ati ales o optiune inexistenta! Incercati din nou!\n";
        }
    }


    return 0;
}

proces & proces::operator=(proces & ob){
    if (this != &ob)
    {
        this -> reclamant = ob.reclamant;
        this ->reclamat = ob.reclamat;
        nrProces = cateProcese;
        plusProces();
    }
    return *this;
}

proces_civil & proces_civil::operator=(proces_civil & ob)
{
    if (this != &ob)
    {
        this -> proces::operator=(ob);
        this -> dauneMateriale = ob.dauneMateriale;
        dauneMorale = ob.dauneMorale;
        nrMartori = ob.nrMartori;
        stadiu = ob.stadiu;
    }
    return *this;
}

proces_penal & proces_penal::operator=(proces_penal &ob)
{
    if (this != &ob)
    {
        this -> proces::operator=(ob);
        dovezi = ob.dovezi;
        stadiu = ob.stadiu;

    }
    return *this;
}

istream & operator>>(istream &in, proces & ob)
{
    cout << "Introduceti numele reclamantului: ";
    in >> ob.reclamant;
    cout << "Introduceti numele reclamatului: ";
    in >> ob.reclamat;
}

istream & operator >> (istream &in, proces_civil &ob)
{
    cout << "Introduceti numele reclamantului: ";
    in >> ob.reclamant;
    cout << "Introduceti numele reclamatului: ";
    in >> ob.reclamat;
    cout << "Introduceti valoarea daunelor MATERIALE(double): ";
    in >> ob.dauneMateriale;
    cout << "Introduceti valoarea daunelor MORALE(double): ";
    in >> ob.dauneMorale;
    cout << "Introduceti numarul de martori(int): ";
    in >> ob.nrMartori;
    if (ob.nrMartori > 5)
        ob.stadiu = 1;
    else
        ob.stadiu = 0;
    return in;
}

istream & operator >> (istream &in, proces_penal &ob)
{
    cout << "Introduceti numele reclamantului: ";
    in >> ob.reclamant;
    cout << "Introduceti numele reclamatului: ";
    in >> ob.reclamat;
    cout << "Introduceti numarul de dovezi(int): ";
    in >> ob.dovezi;
    if (ob.dovezi > 25)
        ob.stadiu = 1;
    else
        ob.stadiu = 0;
    return in;
}

ostream & operator << (ostream &out, proces &ob)
{
    out << "Procesul cu numarul " << ob.nrProces << ", avand ca reclamant pe " << ob.reclamant << ", si ca reclamat pe " << ob.reclamat << ", nu este clasificat.\n";
    return out;
}

ostream &operator<< (ostream &out, proces_civil &ob)
{
    out << "Procesul cu numarul " << ob.nrProces << ", avand ca reclamant pe " << ob.reclamant << ", si ca reclamat pe " << ob.reclamat << " este un proces civil.\n";
    out << "Sumele pretinse sunt " << ob.dauneMateriale << " RON in daune materiale si " << ob.dauneMorale << " RON in daune morale.\n";
    out << "El are " << ob.nrMartori << " martori, asadar stadiul sau este " << ob.stadiu << '\n';
    return out;
}

ostream &operator << (ostream &out, proces_penal &ob)
{
    out << "Procesul cu numarul " << ob.nrProces << ", avand ca reclamant pe " << ob.reclamant << ", si ca reclamat pe " << ob.reclamat << " este un proces penal.\n";
    out << "El are " << ob.dovezi << " dovezi, asadar stadiul sau este " << ob.stadiu << '\n';
    return out;
}





