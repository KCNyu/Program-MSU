#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

double DoubleRnd() {
    return rand()/32767.0;
}

class Matrix {
private:
    int nDim;
    double* Matr;
public:
    Matrix(int nDim);
    Matrix(Matrix& m);
    ~Matrix() { delete[] Matr; }
private:
    void InitMemory() { Matr=new double[nDim*nDim]; }
    int MakeIndex(int nX,int nY) { return (nX-1)*nDim+(nY-1); }
    void Set(int nX,int nY,double r) { Matr[MakeIndex(nX,nY)]=r; }
    void Set0(int nX,int nY) { Set(nX,nY,0); }
    void Set1(int nX,int nY) { Set(nX,nY,1); }
    double Get(int nX,int nY) { return Matr[MakeIndex(nX,nY)]; }
public:
    void InitNul();
    void InitOne();
    void InitRnd();
    friend ostream& operator<<(ostream& os,Matrix& m);
    double Koeff(int nNizz,int nVerh);
    void Divid(double R,int nVerh);
    void Minus(double R,int nNizz,int nVerh);
};

Matrix::Matrix(int nDim) {
    this->nDim=nDim;
    InitMemory();
}

Matrix::Matrix(Matrix& m) {
    nDim=m.nDim;
    InitMemory();
    for(int i=1;i<=nDim;i++) for(int j=1;j<=nDim;j++) Set(i,j,m.Get(i,j));
}

void Matrix::InitNul() {
    for(int i=1;i<=nDim;i++) for(int j=1;j<=nDim;j++) {
        Set0(i,j);
    }
}

void Matrix::InitOne() {
    for(int i=1;i<=nDim;i++) for(int j=1;j<=nDim;j++) {
        Set0(i,j);
        if(i!=j) continue;
        Set1(i,j);
    }
}

void Matrix::InitRnd() {
    for(int i=1;i<=nDim;i++) for(int j=1;j<=nDim;j++)
        Set(i,j,DoubleRnd());
}

ostream& operator<<(ostream& os,Matrix& m) {
    os << m.nDim << endl;
    for(int i=1;i<=m.nDim;i++) {
        for(int j=1;j<=m.nDim;j++) {
            cout.width(10);
            cout.precision(3);
            os << m.Get(i,j) << " ";
        }
        os << endl;
    }
    return os;
}

double Matrix::Koeff(int nNizz,int nVerh) {
    return Get(nNizz,nVerh);
}

void Matrix::Divid(double R,int nVerh) {
    for(int j=1;j<=nDim;j++)
        Set(nVerh,j,Get(nVerh,j)/R);
    Set(nVerh,nVerh,1);
}

void Matrix::Minus(double R,int nNizz,int nVerh) {
    for(int j=1;j<=nDim;j++)
        Set(nNizz,j,Get(nNizz,j)-R*Get(nVerh,j));
}

int main(int argc,char** argv) {
    srand(time(NULL));
    Matrix M(5);
    M.InitNul(); cout << M << endl;
    M.InitOne(); cout << M << endl;
    M.InitRnd(); cout << M << endl;
    cout << endl;
    double R=M.Koeff(1,1); M.Divid(R,1); cout << M << endl;
    R=M.Koeff(2,1); M.Minus(R,2,1); cout << M << endl;
    R=M.Koeff(2,2); M.Divid(R,2); cout << M << endl;
    R=M.Koeff(3,1); M.Minus(R,3,1); cout << M << endl;
    R=M.Koeff(3,2); M.Minus(R,3,2); cout << M << endl;
    R=M.Koeff(3,3); M.Divid(R,3); cout << M << endl;
    R=M.Koeff(4,1); M.Minus(R,4,1); cout << M << endl;
    R=M.Koeff(4,2); M.Minus(R,4,2); cout << M << endl;
    R=M.Koeff(4,3); M.Minus(R,4,3); cout << M << endl;
    R=M.Koeff(4,4); M.Divid(R,4); cout << M << endl;
    R=M.Koeff(5,1); M.Minus(R,5,1); cout << M << endl;
    R=M.Koeff(5,2); M.Minus(R,5,2); cout << M << endl;
    R=M.Koeff(5,3); M.Minus(R,5,3); cout << M << endl;
    R=M.Koeff(5,4); M.Minus(R,5,4); cout << M << endl;
    R=M.Koeff(5,5); M.Divid(R,5); cout << M << endl;
    cout << endl;
    return 0;
}