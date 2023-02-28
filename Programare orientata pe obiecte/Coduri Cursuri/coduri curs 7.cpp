#include <iostream>
#include<typeinfo>

using namespace std;

class Baza
{
public:
   virtual ~Baza(){cout<<"dB\n";} /// destructor virtual pentru a elimina portiuni alocate dinamic in derivata
};

class Derivata : public Baza
{
    int *v;
public:
    Derivata(){ v = new int[10];}
    ~Derivata(){delete[] v;cout<<"dD\n";}
};

int main()
{
///    Baza b;
///    Derivata d;
///    Baza * p = new Baza();
///    delete p;  /// delete apeleaza destructorul care nu se apeleeaza automat
///    Derivata *d = new Derivata();
///    delete d;
    Baza *x = new Derivata();
    delete x;
}

/*
class Baza   /// a devenit clasa abstracta
{
public:
    virtual void f() = 0;
    virtual void x(){}
};

class Derivata : public Baza
{
public:
    void f(){}
};

int main()
{
///    Baza b;  /// nu pot exista obiecte de tip Baza
    Baza *pb;
    Derivata d;
}
*/

/*
class Baza
{
public:
    virtual void afis(){cout<<"B\n";}
    virtual void f(){}
};

class Derivata : public Baza{
public:
    void afis(){cout<<"D\n";}
    virtual void g(){}
};

int main()
{
///    cout<<sizeof(Baza)<<" "<<sizeof(Derivata);
    Baza *p;
    p = new Derivata();
    p->afis();
    p->g();
}

*/
/*
class Baza{
public:
///    virtual void f(){}
};

class Derivata : public Baza{};

int main()
{
    int x;
    float y;
    Baza b, *p;
    Derivata d;

    cout<<typeid(x).name()<<"\n";
    cout<<typeid(y).name()<<"\n";
    cout<<typeid(b).name()<<"\n";
    cout<<typeid(d).name()<<"\n";
    p = &b;
    cout<<typeid(*p).name()<<"\n";
    p = &d;   /// upcasting
    cout<<typeid(*p).name()<<"\n";
    p = new Baza();
    cout<<typeid(*p).name()<<"\n";

    Derivata *dd;
///    dd = dynamic_cast<Derivata*>(&b);   /// tentativa de downcasting
dd = dynamic_cast<Derivata*>(p);
    return 0;
}
*/
