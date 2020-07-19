/*================================================================
* Filename:Matrix.cpp
* Author: KCN_yu
* Createtime:Fri 13 Dec 2019 02:47:32 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

const int DIM = 255;

class Graf{
    int nDim;
    bool Adj[DIM][DIM];
};

class Array;

class Graph{
    private:
        int nDim;
        bool* Adj;
    public:
        Graph(){}
        Graph(int nDim);
        Graph(const Graph& gOther);
    private:
        void InitMemory(){ Adj = new bool[nDim*nDim]; }
    public:
        ~Graph(){ delete[] Adj; }
        void InitEmpty();
        void InitRnd(double rPlotn);
    private:
        int MakeIndex(int nX, int nY){ return (nX-1)*nDim + (nY-1); }
        void Set(int nX, int nY, bool b){ Adj[MakeIndex(nX,nY)] = b; Adj[MakeIndex(nY,nX)] = b; }
        void SetFalse(int nX, int nY){ Set(nX, nY, false); }
        void SetTrue(int nX, int nY){ Set(nX, nY, true); }
        bool Get(int nX, int nY){ return Adj[MakeIndex(nX,nY)]; }
    public:
        friend ostream& operator << (ostream& os, Graph& g);
        void WriteFile(int Nomer);
        friend istream& operator >> (istream& is, Graph& g);
        void ReadFile(int Nomer);i
        bool StopTransi();
        void Transi();
    private:
        int* Parent;
    public:
        void ParentInitMemory();
};

Graph::Graph(int nDim){
    this->nDim = nDim;
    InitMemory();
}
Graph::Graph(Graph& g){
    nDim = g.nDim;
    InitMemory();
    for (int i = 0; i <= nDim; i++)
        for (int j = 0; j <= nDim; j++)
            Set(i,j,g.Get(i,j));
}
void Graph::InitEmpty(){
    for (int i = 0; i <= nDim; i++)
        for (int j = 0; j <= nDim; j++)
            SetFalse(i,j);
}
void Graph::InitRnd(double rPlotn){
    for (int i = 1; i <= nDim; i++) {
        SetFalse(i,i);
        for (int j = 0; j <= nDim; j++) {
            int n = rand()%1000;
            bool b = n < 1000*rPlotn;
            Set(i,j,b);
        }
    }
}
ostream& operator << (ostream& os, Graph& g){
    os << g.nDim << endl;
    for (int i = 1; i <= g.nDim; i++) {
       for (int j = 0; j < g.nDim; j++)
           os << (g.Get(i,j) ? "1 " : "0 ");
       os << endl;
    }
    return os;
}
void Graph::WriteFile(int Nomer){
    char Str[9];
    Str[0] = 'g';
    Str[1] = 'r';
    Str[2] = '0'+Nomer%10; Nomer/=10;
    Str[3] = '0'+Nomer%10;
    Str[4] = '-';
    Str[5] = 't';
    Str[6] = 'x';
    Str[7] = 't';
    Str[8] = '\0';
    ofstream FileOut(str);
    if (!FileOut) cout << "error!" << endl;
    FileOut << *this;
    FileOut.close();
}

