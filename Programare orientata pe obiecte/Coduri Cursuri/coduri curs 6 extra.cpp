#include <iostream>

using namespace std;

class Baza
{
protected:
    int x;
public:
    Baza(){cout<<"B";}
    Baza(int xx){x = xx; cout<<"Param B";}
    Baza (Baza& ob){x = ob.x;}
};

class Derivata : public Baza
{
    int y;
public:
    Derivata(){cout<<"D"; x = -123; y = - 456;}
    Derivata(int u) : Baza(u){ y = 300;}
    Derivata(Derivata& ob) : Baza(ob){y = ob.y; cout<<x<<" "<<y<<endl;}
};

int main()
{
    Derivata ob1;
    Derivata ob2(100);
    cout<<endl;
    Derivata ob3(ob2);
}

/************************/
/*
class Baza
{
    int x;
protected:
    int y;
public:
    void xx(){}
};

class Derivata1 : Baza{

public:
    using Baza::xx;
    void f() {
///    cout<<x<<" ";
    cout<<y<<endl;
    }
};

class Derivata2 : public Derivata1
{
public:
    void g()
    {
///        cout<<x<<" ";
///        cout<<y<<endl;
    }
};

/// void h(Baza o){cout<<o.y;}   /// datele private si protected inaccesibile

int main()
{
///    Baza ob0;
///    h(ob0);
    Derivata1 ob1;
    ob1.f();
    ob1.xx();

    Derivata2 ob2;
    ob2.xx();
///    Derivata2 ob2;
///    ob2.g();
}
*/

/*******************************/
/*
class Baza
{
public:
    void afis(){cout<<"B\n";}
};

class Derivata : public Baza
{
public:
    void afis(){cout<<"D\n";}
};

class C
{
    Baza x;
};
void f(Baza ob){ ob.afis(); }   /// object slicing dar ok

int main()
{
    Derivata ob;
///    ob.afis();
    Baza b;
    f(b);
    f(ob);
    C ob2;
    f(ob2);
    return 0;
}
*/
