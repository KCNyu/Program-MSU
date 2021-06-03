/*================================================================
* Filename:test10.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 01:32:25 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class X
{
    int j;
public:
    X ( int k )
    {
        try
        {
            if ( k == 10 ) throw k;
            if ( k == 0 ) throw '0';
            j = k;
        }
        catch ( char )
        {
            cout << "catch1\n";
        }
        catch (...)
        {
            cout << "catch2\n";
            throw;
        }
    }
};
void f ( int i )
{
    try
    {
        X a ( i );
        X b ( 5 );
    }
    catch ( int )
    {
        cout << "catch3\n";
        throw;
    }
    catch (...)
    {
        cout << "catch4\n";
    }
}
int main ()
{
    try
    {
        f ( 0 );
        f ( 10 );
        f ( 100 );
    }
    catch ( int )
    {
        cout << "catch5\n";
    };
 return 0;
}

