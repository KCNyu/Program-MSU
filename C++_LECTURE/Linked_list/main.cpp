#include <iostream>
#include <string>
using namespace std;

class Edge{
public:
    int nFrom, nInto;
    char Char;
public:
    void Init(int nFrom, int nInto, char Char) { this->nFrom=nFrom; this->nInto=nInto; this->Char=Char; }
};

class Automaton {
public:
    int nStates, nEdges;
    bool Inputs[10], Outputs[10];
    Edge Edges[50];
    bool RunDeep(string sWish);
    bool RunWide(string sWish);
private:
    bool RunDeep(string sWish, int nInput);
    bool RunWideRec();
};

bool Automaton::RunDeep(string sWish) {
    for(int i=0; i<nStates; i++){
        if(!Inputs[i]) continue;
        if(RunDeep(sWish,i)) return true;
    }
    return false;
}

bool Automaton::RunDeep(string sWish, int nInput) {
    cout << "*** " << sWish << " " << nInput << endl;

    if(sWish.size()==0) return Outputs[nInput];
    char CFirst=sWish[0];
    for(int i=0; i<nEdges; i++){
        if(Edges[i].nFrom!=nInput) continue;
        if(Edges[i].Char!=CFirst) continue;
        if(!RunDeep(sWish.substr(1),Edges[i].nInto)) continue;
        return true;
    }
    return false;
}

class ExtState{
public:
    string sWish;
    int nInput;
    void Print() { cout << sWish << " " << nInput; }
};

const int nMax=10000;
class ExtStateArray{
public:
    ExtState Arr[nMax];
    int nFirst, nLast;
    void Init() { nFirst=1; nLast=0; }
    bool Empty() { return nLast<nFirst; }
    bool Add(ExtState es) {
        if(++nLast>=nMax) return false;
        Arr[nLast]=es;
    }
    bool Extract(ExtState& es){
        es=Arr[nFirst++];
        return true;
    }
    void Print(){
        for(int i=nFirst; i<=nLast; i++){
            Arr[i].Print();
            cout<<endl;
        }
    }
};

ExtStateArray esa;

bool Automaton::RunWide(string sWish){
    esa.Init();
    ExtState es; es.sWish=sWish;
    for(int i=0; i<nStates; i++){
        if(!Inputs[i]) continue;
        es.nInput=i;
        esa.Add(es);
    }
    cout<< "***** " << endl; esa.Print();
    return RunWideRec();
}

bool Automaton::RunWideRec(){
    cout<< "************* " << endl; esa.Print();
    if(esa.Empty()) return false;
    ExtState es; esa.Extract(es);
    string sWish=es.sWish;
    char CFirst=sWish[0];
    for(int i=0; i<nEdges; i++){
        if(Edges[i].nFrom != es.nInput) continue;
        if(Edges[i].Char != CFirst) continue;
        string s=sWish.substr(1);
        if(s=="") return Outputs[Edges[i].nInto];
        ExtState eses; eses.sWish=s; eses.nInput=Edges[i].nInto;
        esa.Add(eses);
    }
    return RunWideRec();
}

int main()
{
    string str="abbaaab";
    Automaton Aut;
    Aut.Edges[0].Init(0,1,'a');
    Aut.Edges[1].Init(0,2,'b');
    Aut.Edges[2].Init(1,1,'a');
    Aut.Edges[3].Init(1,2,'b');
    Aut.Edges[4].Init(2,1,'a');
    Aut.Edges[5].Init(2,0,'b');
    Aut.RunDeep(str);
    Aut.nEdges=6;
    Aut.nStates=3;
    for(int i=0; i<10; i++){
        Aut.Inputs[i]=true;
        Aut.Outputs[i]=true;
    }
    cout<< Aut.RunDeep(str) << endl;
    cout<< Aut.RunWide(str) << endl;
    return 0;
}
