#include <iostream>

using namespace std;

class Test
{
    int *v;
public:
    Test(){v = new int[20]; v[0]=100; v[1]=200;}
    ~Test() { delete[] v;}
    void afis(){cout<<v[0]<<" "<<v[1]<<endl;}
};

void f(Test& ob) {ob.afis();} /// ob.v = ob1.v bit cu bit
void g(Test* ob2) { ob2->afis();}
int main()
{
    Test ob1;
    ob1.afis();
    f(ob1);
    ob1.afis();
    g(&ob1);
    ob1.afis();

    Test* ob3;
    ob3 = &ob1;
    Test& ob4 = ob1;
    cout<<sizeof(ob3)<<" "<<sizeof(ob4)<<"\n";
}

/**********************************************************/
/*
int f(int *x) {*x = 789;}
int g(int& y) { y = 123;}
int main()
{
    int a = 70;
    cout<<a<<"\n";
    f(&a);
    cout<<a<<"\n";
    g(a);
    cout<<a<<"\n";
}
*/

/******************** constructori si destructor EXPLICIT - utilizare supraincarcare si valori implicite *********/
/*
class Test
{
    int x, y, z;
public:
    /// supraincarcare de functii constructor

    Test(){x = 1; y = 2; z = 3;}  /// creare explicita de constr de initializare, care ascunde varianta implicita
    Test(int a){x = a; y = 2; z = 3;}
    Test(int a, int b){x = a; y = b; z = 3;}
    Test(int a, int b, int c){x = a; y = b; z = c;}

    Test(int a = 1, int b = 2, int c = 3);  /// utilizare valori implicite pentru parametrii din constructor
    void afisare();
};

    Test::Test(int a, int b, int c){x = a; y = b; z = c;}  /// :: operator de rezolutie de scop
    void Test::afisare(){cout<<x<<" "<<y<<" "<<z<<"\n";}

int main()
{
    Test ob4;
    ob4.afisare();
    Test ob5(100);
    ob5.afisare();
    Test ob6(123, 34);
    ob6.afisare();
    Test ob7(56,78,90);
    ob7.afisare();

    Test ob1;   /// exista by default constructor de initializare in orice clasa
    ob1.afisare();
    Test ob2 = ob1; /// exista by default constructor de copiere in orice clasa
    ob2.afisare();
    Test ob3;
    ob3 = ob1;
    ob3.afisare(); /// exista by default operator de atribuire (=) in orice clasa

}
*/

/******************** trecere de la struct la class *******************************/
/*
class Test
{
    int x;
    public:
    void citire(){ x = 20;}
    void afisare(){cout<<x<<"\n";}
};

int main()
{
    Test ob;
    ob.citire();
    ob.afisare();
///    cout<<ob.x;
    return 0;
}
*/
