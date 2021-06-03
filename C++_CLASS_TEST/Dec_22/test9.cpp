/*================================================================
* Filename:test9.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 01:28:02 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

void f ( char c )
{
    try
    {
        if ( c >='1' && c<='9')
            c++;
        else
            throw "error";
        try
        {
            if ( c == '8' )
                throw c;
                c++;
        }
        catch ( const char *c )
        {
            cout << c << "\ncatch1\n";
        }
        catch ( char c )
        {
            cout << "catch2\n";
            throw;
        }
        cout << c << endl;
    }
    catch ( int k )
    {
        cout << k << "\ncatch3\n";
    }
    catch ( char *c )
    {
        cout << c << "\ncatch4\n";
    }
}
int main ()
{
    try
    {
        f ( 'a' );
        f ( '2' );
        f ( '7' );
        f ( '5' );
    }
    catch ( char c )
    {
        cout << c << "\ncatch5\n";
    }
    catch ( ... )
    {
        cout << "all exceptions\n";
    };
    return 0;
}
