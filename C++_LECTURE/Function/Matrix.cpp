/*================================================================
* Filename:Matrix.cpp
* Author: KCN_yu
* Createtime:Thu 12 Mar 2020 04:08:48 PM CST
================================================================*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

using namespace std;

//////////////////////////////////////////////////////////////////////
class Matrix{
    private:
        int nDim;
        double* M;
    public:
        Matrix(int nDim);
        Matrix(Matrix& m);
        ~Matrix() { delete[] M; }
        void InitRand(double r);
        //void Gauss();
        void Divid(double R, int nVerh);
        void Minus(double R, int nNizz, int nVerh);
        int Getdim(){ return nDim; }
        double& Getelem(int i, int j) { return M[i*nDim+j]; }
        void Set(int i, int j, double R) { Getelem(i,j) = R; }
        friend ostream& operator<<(ostream&os,Matrix& Mat);
    private:
        void InitMemory(){ M = new double[nDim*nDim]; }
};
Matrix::Matrix(int nDim){
    this->nDim = nDim;
    InitMemory();
}
Matrix::Matrix(Matrix& m){
    nDim = m.nDim;
    InitMemory();
    for(int i = 0; i < nDim*nDim; i++) M[i] = m.M[i];
}
void Matrix::InitRand(double r){
    for(int i = 0; i < nDim*nDim; i++) M[i] = (rand()/32767.0)*r;
}
ostream& operator<<(ostream&os,Matrix& Mat){
    for(int i = 0; i < Mat.nDim; i++){
        for(int j = 0; j < Mat.nDim; j++){
            cout.width(10);
            cout.precision(3);
            os << Mat.Getelem(i,j) << " ";
        }
        os << endl;
    }
    os << endl;
    return os;
}
void Matrix::Divid(double R, int nVerh){
    for(int j = 0; j < nDim; j++) Set(nVerh,j,Getelem(nVerh,j)/R);
}
void Matrix::Minus(double R, int nNizz, int nVerh){
    for(int j = 0; j < nDim; j++) Set(nNizz,j,Getelem(nNizz,j)-R*Getelem(nVerh,j));
}
/*
void Matrix::Gauss(){
    for(int i = 0; i < nDim-1; i++){
        for(int j = i+1; j < nDim; j++){
            double temp = Getelem(j,i)/Getelem(i,i);
            for(int k = 0; k < nDim; k++){
                Getelem(j,k) -= Getelem(i,k)*temp;
            }
        }
    }
}
*/

//////////////////////////////////////////////////////////////////////

class Vector{
    private:
        int nDim;
        double* Vect;
    public:
        Vector(int nDim);
        Vector(Vector& v);
        ~Vector() { delete[] Vect; }
        void InitRand(double r);
        void Divid(double R, int nVerh);
        void Minus(double R, int nNizz, int nVerh);
        int Getdim(){ return nDim; }
        double& Getelem(int i) { return Vect[i]; }
        void Set(int i, double R) { Getelem(i) = R; }
        friend ostream& operator<<(ostream&os,Vector& V);
    private:
        void InitMemory(){ Vect = new double[nDim]; }
};
Vector::Vector(int nDim){
    this->nDim = nDim;
    InitMemory();
}
Vector::Vector(Vector& v) {
    nDim = v.nDim;
    InitMemory();
    for(int i = 0; i < nDim; i++) Vect[i] = v.Vect[i];
}
void Vector::InitRand(double r){
    for(int i = 0; i < nDim; i++) Vect[i] = (rand()/32767.0)*r;
}
ostream& operator<<(ostream&os,Vector& V){
    for(int i = 0; i < V.nDim; i++){
        cout.width(10);
        cout.precision(3);
        os << V.Getelem(i) << " ";
    }
    os << endl;
    return os;
}
void Vector::Divid(double R, int nVerh){
    Set(nVerh,Getelem(nVerh)/R);
}
void Vector::Minus(double R, int nNizz, int nVerh){
    Set(nNizz,Getelem(nNizz)-R*Getelem(nVerh));
}

//////////////////////////////////////////////////////////////////////

class MatrixVector{
    private:
        int nDim;
        Matrix MMM;
        Vector VVV;
    public:
        MatrixVector(int nDim);
        void InitMatrix(Matrix& M);
        void InitVector(Vector& V);
        Matrix& GetMatrix(){ return MMM; }
        Vector& GetVector(){ return VVV; }
        void InitRand(double r);
        void Divid(double R, int nVerh){ MMM.Divid(R,nVerh); VVV.Divid(R,nVerh); }
        void Minus(double R, int nNizz, int nVerh) { MMM.Minus(R,nNizz,nVerh); VVV.Minus(R,nNizz,nVerh); }
        friend ostream& operator<<(ostream&os,MatrixVector& mv);
        void Tuda();
        void Obratno();
};
MatrixVector::MatrixVector(int nDim):MMM(nDim),VVV(nDim){
    this->nDim = nDim;
}
void MatrixVector::InitMatrix(Matrix& M){
    for(int i = 0; i < nDim; i++) for(int j = 0; j < nDim; j++)
        M.Set(i,j,MMM.Getelem(i,j));
}

void MatrixVector::InitVector(Vector& V){
    for(int i = 0; i < nDim; i++) V.Set(i,VVV.Getelem(i));
}
void MatrixVector::InitRand(double r){
    MMM.InitRand(r);
    VVV.InitRand(r);
}
ostream& operator<<(ostream&os,MatrixVector& mv){
    for(int i = 0; i < mv.nDim; i++){
        for(int j = 0; j < mv.nDim; j++){
            cout.width(10);
            cout.precision(3);
            os << mv.MMM.Getelem(i,j) << " ";
        }
        cout.width(14);
        cout.precision(3);
        os << mv.VVV.Getelem(i) << " ";
        os << endl;
    }
    os << endl;
    return os;
}
void MatrixVector::Tuda(){
    for(int i = 0; i < nDim; i++){
        Divid(MMM.Getelem(i,i),i);
        for(int j = i+1; j < nDim; j++) Minus(MMM.Getelem(j,i),j,i);
    }
}
void MatrixVector::Obratno(){
    for(int i = nDim-1; i >= 1; i--)
        for(int j = i-1; j >= 0; j--)
            Minus(MMM.Getelem(j,i),j,i);
}
void Multi(Matrix& MMM, Vector& VVV, Vector& VVVotv){
    int nDim = MMM.Getdim();
    for(int i = 0; i < nDim; i++){
        double R = 0;
        for(int j = 0; j < nDim; j++) R += MMM.Getelem(i,j)*VVV.Getelem(j);
        VVVotv.Set(i,R);
    }
}
double Nevya(Vector& VVV1, Vector& VVV2){
    int nDim = VVV1.Getdim();
    double R = 0;
    for(int i = 0; i < nDim; i++) R += pow(VVV1.Getelem(i)-VVV2.Getelem(i),2);
    return pow(R,0.5);
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int nDim = 4;
    MatrixVector MV(nDim);
    MV.InitRand(0.001);
    cout << MV;
    Matrix M(nDim); MV.InitMatrix(M);
    Vector V(nDim); MV.InitVector(V);
    MV.Tuda();MV.Obratno();
    cout << MV;
    Vector VV(nDim);
    Multi(M,MV.GetVector(),VV); cout << VV;
    cout << Nevya(VV,V);
    return 0;
}
