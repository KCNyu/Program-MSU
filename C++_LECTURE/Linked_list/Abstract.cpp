/*================================================================
* Filename:Abstract.cpp
* Author: KCN_yu
* Createtime:Wed 13 May 2020 11:41:08 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class Abstract{
    private:
    public:
        Abstract() { cout << "constructor A" << endl; }
        virtual ~Abstract() { cout << "destructor A" << endl; }
        virtual void InitOne() = 0;
        virtual void Print() = 0;
        void Vmeste(){ InitOne(); Print(); }
};
////////////////////////////////////////////////////////
class Complex : public Abstract {
    private:
        int Re, Im;
    public:
        Complex() : Abstract() { cout << "constructor C" << endl; }
        virtual ~Complex() { cout << "destructor C" << endl; }
        void Init(int Re, int Im) { this->Re = Re; this->Im = Im; }
        virtual void InitOne() { Init(1,0); }
        virtual void Print() {cout << "(" << Re << "," << Im << ")"; }
        
};
////////////////////////////////////////////////////////
class Matrix: public Abstract {
    private:
        int A11, A12, A21, A22;
    public:
        Matrix() : Abstract() { cout << "constructor M" << endl; }
        virtual ~Matrix() { cout << "destructor M" << endl; }
        void Init(int A11, int A12, int A21, int A22) { this->A11 = A11; this->A12 = A12; this->A21 = A21; this->A22 = A22; }
        virtual void InitOne() { Init(1,0,0,1); }
        virtual void Print() { cout << A11 << " " << A12 << endl << A21 << " " << A22 << endl; }
};
////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    
    //Abstract A;
    
    Complex C; C.Vmeste(); cout << endl;
    cout << endl << endl;
    Matrix M; M.Vmeste(); cout << endl;
    
    Complex* CPtr = new Complex; CPtr->Vmeste(); cout << endl;
    Matrix* MPtr = new Matrix; MPtr->Vmeste(); cout << endl;
    Complex* CTmpPtr = CPtr; CTmpPtr->Vmeste(); cout << endl;   
    Abstract* ATmpPtr = CPtr; ATmpPtr->Vmeste(); cout << endl; 
    ATmpPtr = MPtr; ATmpPtr->Vmeste(); cout << endl;
    delete CPtr; delete MPtr;
    return 0;
}
