/*================================================================
* Filename:test.cpp
* Author: KCN_yu
* Createtime:Wed 18 Mar 2020 11:26:41 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

//string S = "(a+b)*a";
string S = "(a*(b*a)+a+(a*b))+b*a";

int L = S.size();

bool ThisT (string S);
bool ThisF (string S);


bool ThisE (string S) {
    if (ThisT(S)) return true;
    int L = S.size();
    for (int i=1; i<L-1; i++) {
        if (S[i]!='+') continue;
        if (!ThisT(S.substr(0,i))) continue;
        if (ThisE(S.substr(i+1))) return true;
    }
    return false;
}

bool ThisT (string S) {
    if (ThisF(S)) return true;
    int L = S.size();
    for (int i=1; i<L-1; i++) {
        if (S[i]!='*') continue;
        if (!ThisF(S.substr(0,i))) continue;
        if (ThisT(S.substr(i+1))) return true;
    }
    return false;
}

bool ThisF (string S) {
    if (S=="a") return true;
    if (S=="b") return true;
    int L = S.size();
    if (S[0]!='(') return false;
    if (S[L-1]!=')') return false;
    return ThisE(S.substr(1,L-2));
}

//////////////////////////////////////////////////////////////////////////////////

bool DasT (int Beg, int End);
bool DasF (int Beg, int End);


bool DasE (int Beg, int End) {
    if (DasT(Beg,End)) return true;
    for (int i=Beg+1; i<=End-1; i++) {
        if (S[i]!='+') continue;
        if (!DasT(Beg,i-1)) continue;
        if (DasE(i+1,End)) return true;
    }
    return false;
}

bool DasT (int Beg, int End) {
    if (DasF(Beg,End)) return true;
    for (int i=Beg+1; i<=End-1; i++) {
        if (S[i]!='*') continue;
        if (!DasF(Beg,i-1)) continue;
        if (DasT(i+1,End)) return true;
    }
    return false;
}

bool DasF (int Beg, int End) {
    if (Beg==End) return (S[Beg]=='a') || (S[Beg]=='b');
    if (S[Beg]!='(') return false;
    if (S[End]!=')') return false;
    return DasE(Beg+1,End-1);
}


//////////////////////////////////////////////////////////////////////////////////

bool EtoT (int Beg, int End);
bool EtoF (int Beg, int End);


bool EtoE (int Beg, int End) {
    if (EtoT(Beg,End)) return true;
    int NB = 0;
    for (int i=Beg; i<=End-1; i++) {
        char C = S[i];
        if (C=='(') NB++; else if (C==')' && --NB<0) return false;
        if (i==Beg || NB>0 || C!='+') continue;
        if (EtoT(Beg,i-1) && EtoE(i+1,End)) return true;
    }
    return false;
}

bool EtoT (int Beg, int End) {
    if (EtoF(Beg,End)) return true;
    int NB = 0;
    for (int i=Beg; i<=End-1; i++) {
        char C = S[i];
        if (C=='(') NB++; else if (C==')' && --NB<0) return false;
        if (i==Beg || NB>0 || C!='*') continue;
        if (EtoF(Beg,i-1) && EtoT(i+1,End)) return true;
    }
    return false;

}

bool EtoF (int Beg, int End) {
    if (Beg==End) return (S[Beg]=='a') || (S[Beg]=='b');
    if (S[Beg]!='(') return false;
    if (S[End]!=')') return false;
    return EtoE(Beg+1,End-1);

}


//////////////////////////////////////////////////////////////////////////////////

class Production {
    public:
        char Left;
        string Right;
        void Init(char L, string R){ Left = L; Right = R; }
};

class Grammar {
    public:
        Production PPP[7];
        bool Run(string Input);
        bool Run(string Input, string Wish);
};

bool Grammar::Run(string Input){
    string W(1,PPP[0].Left);
    return Run(Input,W);
}

bool Grammar::Run(string Input, string Wish){
    int IS = Input.size();
    int WS = Wish.size();
    if (IS == 0 || WS == 0) return IS==0 && WS==0;
    char CFirst = Wish[0];
    if(CFirst != 'E' && CFirst != 'T' && CFirst != 'F'){
        if(Input[0] != CFirst) return false;
        return Run(Input.substr(1),Wish.substr(1));
    }
    for(int i = 0; i < 7; i++){
        if(PPP[i].Left != CFirst) continue;
        if(Run(Input,PPP[i].Right+Wish.substr(1))) return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    cout << S << endl;

    double start = clock();
    if(ThisE(S)) cout << "yes" << endl; else cout << "no" << endl;
    cout << (clock()-start)/CLOCKS_PER_SEC << endl;

    start = clock();
    if(DasE(0,L-1)) cout << "yes" << endl; else cout << "no" << endl;
    cout << (clock()-start)/CLOCKS_PER_SEC << endl;

    start = clock();
    if(EtoE(0,L-1)) cout << "yes" << endl; else cout << "no" << endl;
    cout << (clock()-start)/CLOCKS_PER_SEC << endl;

    Grammar GGG;
    GGG.PPP[0].Init('E',"T");
    GGG.PPP[1].Init('E',"T+E");
    GGG.PPP[2].Init('T',"F");
    GGG.PPP[3].Init('T',"F*T");
    GGG.PPP[4].Init('F',"a");
    GGG.PPP[5].Init('F',"b");
    GGG.PPP[6].Init('F',"(E)");
    start = clock();
    if(GGG.Run(S)) cout << "yes" << endl; else cout << "no" << endl;
    cout << (clock()-start)/CLOCKS_PER_SEC << endl;
    return 0;
}

