///https://pastebin.com/Hb2NCXw
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

/*** mostenire in diamant + upcast/downcast + RTTI / Typeid - problema admitere locuri IF,ID,A 2 FAC. Se cere: stocarea tuturor
cererilor pentru locuri, afisarea tuturor, afisarea doar a celor care doresc ID, stergerea celor care doresc 2 fac  ***/

/// depunctare - folosire necorespunzatoare a destructorilor ---> MEMORY LEAK ---> se rezolva prin destructpr virtual

class Candidat
{
protected:
    string nume;
    float bac;
public:
    virtual void citire(); /// to do - clasa abstracta
    friend ostream& operator<< (ostream&, Candidat&);
    virtual ~Candidat(){cout<<"\n~Candidat";}
};

class Candidat_ID : virtual public Candidat
{
protected:
    float mate;
public:
    void citire();
    friend ostream& operator<< (ostream&, Candidat_ID&);
    ~Candidat_ID(){cout<<"\n~Candidat_ID";}
};

class Candidat_2FAC : virtual public Candidat
{
protected:
    float licenta;
public:
    void citire();
    friend ostream& operator<< (ostream&, Candidat_2FAC&);
    ~Candidat_2FAC(){cout<<"\n~Candidat_2FAC";}
};

/// Mostenire multipla

class Candidat_ID_2FAC : public Candidat_ID, public Candidat_2FAC
{
public:
    void citire();
    friend ostream& operator<< (ostream&, Candidat_ID_2FAC&);
    ~Candidat_ID_2FAC(){cout<<"\n~Candidat_ID_2FAC";}
};


int main()
{
    vector<Candidat*> v;
    int n;
    cin>>n;
    for(int i = 0; i<n; i++)
    {
        cout<<"Tip de loc: 1 - ID; 2 - 2 FAC; 3 - ID 2 FAC";
        int op;
        cin>>op;
        switch(op)
        {
            case 1: { v.push_back(new Candidat_ID()); break;}
            case 2: { v.push_back(new Candidat_2FAC()); break;}
            case 3: { v.push_back(new Candidat_ID_2FAC()); break;}
        }
    }

    for(auto p = v.begin(); p != v.end(); p++)
        (**p).citire();

    for(auto p = v.begin(); p != v.end(); p++)
        if (typeid(**p) == typeid(Candidat_ID)) cout<<*dynamic_cast<Candidat_ID*>(*p);
        else if (typeid(**p) == typeid(Candidat_2FAC)) cout<<*dynamic_cast<Candidat_2FAC*>(*p);
        else if (typeid(**p) == typeid(Candidat_ID_2FAC)) cout<<*dynamic_cast<Candidat_ID_2FAC*>(*p);

   /// afisare doar ID
       for(auto p = v.begin(); p != v.end(); p++)
        if (typeid(**p) == typeid(Candidat_ID)) cout<<*dynamic_cast<Candidat_ID*>(*p);
        else if (typeid(**p) == typeid(Candidat_ID_2FAC)) cout<<*dynamic_cast<Candidat_ID_2FAC*>(*p);

    /// stergere IF
    for(auto p = v.begin(); p != v.end(); p++)
        if ((typeid(**p) == typeid(Candidat_2FAC)) || (typeid(**p) == typeid(Candidat_ID_2FAC)))
        {
            v.erase(p);
            p--;
        }

            for(auto p = v.begin(); p != v.end(); p++)
        if (typeid(**p) == typeid(Candidat_ID)) cout<<*dynamic_cast<Candidat_ID*>(*p);
        else if (typeid(**p) == typeid(Candidat_2FAC)) cout<<*dynamic_cast<Candidat_2FAC*>(*p);
        else if (typeid(**p) == typeid(Candidat_ID_2FAC)) cout<<*dynamic_cast<Candidat_ID_2FAC*>(*p);

    /*
    Candidat *p = new Candidat_ID_2FAC();
    p->citire();
    cout<<* dynamic_cast<Candidat_ID_2FAC*> (p);   /// exemplificare downcast

    delete p;
*/
    return 0;
}

/*** clasa Candidat ***/

void Candidat::citire(){cout<<"Nume: "; cin>>nume; cout<<"Medie bac: "; cin>>bac;}
ostream& operator<<( ostream& out, Candidat& c)
{
    out<<"\nCandidat: "<<c.nume<<" are bacul: "<<c.bac;
    return out;
}

/*** clasa Candidat_ID ***/
void Candidat_ID::citire(){ Candidat::citire(); cout<<"Mate bac: "; cin>>mate;}
ostream& operator<< (ostream& out, Candidat_ID& c)
{
    out<<dynamic_cast<Candidat&> (c);
    out<<" si are media la Mate: "<<c.mate;
    return out;
}

/*** clasa Candidat_2FAC ***/
void Candidat_2FAC::citire(){ Candidat::citire(); cout<<"Licenta: "; cin>>licenta;}
ostream& operator<< (ostream& out, Candidat_2FAC& c)
{
    out<<dynamic_cast<Candidat&> (c);
    out<<" si are nota la Licenta: "<<c.licenta;
    return out;
}

/*** clasa Candidat_ID_2FAC ***/
void Candidat_ID_2FAC::citire(){ Candidat_ID::citire(); cout<<"Licenta: "; cin>>licenta;}
ostream& operator<< (ostream& out, Candidat_ID_2FAC& c)
{
    out<<dynamic_cast<Candidat_ID&> (c);
    out<<" si are nota la Licenta: "<<c.licenta;
    return out;
}
