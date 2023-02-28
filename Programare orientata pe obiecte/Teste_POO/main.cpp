#include <iostream>
using namespace std;
class loc {   int longitude, latitude;
public:
   loc() {cout << "da ba chiar asa e";} // needed to construct temporaries
   loc(int lg, int lt) { longitude = lg; latitude = lt; }
    void show() { cout<<longitude<<" "<<latitude<<"\n";}
   friend loc operator+(loc op1, loc op2); // friend
};

// Now, + is overloaded using friend function.
    loc operator+(loc op1, loc op2){
       loc temp;
       temp.longitude = op1.longitude + op2.longitude;
       temp.latitude = op1.latitude + op2.latitude;
   return temp;
}


int main()
{
    loc aici(50, 60), acolo (70, 10);
    loc mergem(5, 5);
    mergem = aici + acolo;
    return 0;
}
