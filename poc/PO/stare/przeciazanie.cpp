#include <iostream>
using namespace std;

class zes
{
    public:
      float a;
      float b;

      zes()
      {
          this->a=0;
          this->b=0;
      }

    zes( float a, float b )
    {
        this->a = a;
        this->b = b;
    }

       void input()
       {
           cout << "a=";
           cin >> a;
           cout << "b=";
           cin >> b;
       }

       zes operator +(const zes & z2)
       {
           return zes(this->a + z2.a, this->b + z2.b);
       }

       void output()
       {
            cout << a << "+" << b << "i" << endl;
       }

       bool operator >( const zes & z2 )
        {
            if( this->a > z2.a )
            return true;
            else
            return false;

}
};

int main()
{
    float a = 10.0, b = 20.0, c = 200.0;

    zes z1, z2, wynik;

    cout<<"pierwsza liczba\n";
    z1.input();

    cout<<"druga liczba\n";
    z2.input();

    wynik = z1 + z2;
    wynik.output();

    return 0;
}
