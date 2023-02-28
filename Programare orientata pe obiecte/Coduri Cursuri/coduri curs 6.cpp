#include <iostream>

using namespace std;

class Baza
{
protected:
    int x,y;
    char z;
protected:
    void afis(){cout<<"Baza ";}//x <<"\n";}
};

class Derivata : virtual private Baza{
int t;
public:
    void afis2(){cout<<"Derivata\n"<<x<<"\n";}
///    void afis(){cout<<"D\n"; Baza::afis();}
};

class Derivata2 : public Derivata{};

class Derivata3 : virtual public Baza{};
class X{};
class Derivata4 : public Baza, public X{};   /// mostenire multipla/din baza multipla

class Derivata5 : public Derivata, public Derivata3{};  /// mostenire in romb, diamant

int main()
{
    Derivata2 ob;
    ob.afis();
    /*
    Derivata ob;
    cout<<sizeof(ob)<<endl;
    ob.afis();
    ob.afis2();

    Baza ob2;
///    ob2.afis2(); /// obiect din baza NU POATE ACCESA functie proprie derivatei
*/
    return 0;
}
