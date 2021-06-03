/*================================================================
* Filename:Tree.cpp
* Author: KCN_yu
* Createtime:Sat 02 May 2020 05:21:55 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

string S = "(a+b)*a";

class Tree{
    private:
        int nDepth;
        int nKol;
        int A;
        Tree** SubTrees;
    public:
        Tree() { nDepth = -1; }
        Tree(int A);
        ~Tree() { Destroy(); }
        void InitSubTrees(string Str);
        Tree* Search(char Ch, bool bl);
        void Print() { Print(0,3); }
        void PrintSym() { PrintSym(0,2); }
    private:
        void Destroy();
        void Print(int Space, int SpaceL);
        void PrintSym(int Space, int SpaceL);
};

Tree::Tree(int A){
    nDepth = 0;
    nKol = 0;
    this->A = A;
}

void Tree::Destroy(){
    if(nDepth < 0) return;
    for(int i = 0; i < nKol; i++) delete SubTrees[i];
    nDepth = -1;
}
void Tree::InitSubTrees(string Str){
    Destroy();
    nDepth = 1;
    nKol = Str.size();
    SubTrees = NULL;
    if(nKol <= 0) return;
    SubTrees = new Tree*[nKol];
    for(int i = 0; i < nKol; i++){
        char Char = Str[i];
        int AAA = Char;
        if(AAA<32 || AAA>122) exit(1);
        AAA -= 32;
        SubTrees[i] = new Tree(AAA);
    }
}
void Tree::Print(int Space, int SpaceL){
    if(nDepth < 0) return;
    for(int i = 0; i < Space; i++) cout << " ";
    cout.width(3); cout << A;
    for(int i = nKol-1; i >= 0; i--){
        SubTrees[i]->Print((i==nKol-1?0:SpaceL),SpaceL+3);
        if(i > 0) cout << endl;
    }
}
void Tree::PrintSym(int Space, int SpaceL){
    if(nDepth < 0) return;
    for(int i = 0; i < Space; i++) cout << " ";
    char Ch = A+32; cout << Ch << " ";
    for(int i = nKol-1; i >= 0; i--){
        SubTrees[i]->PrintSym((i==nKol-1?0:SpaceL),SpaceL+2);
        if(i > 0) cout << endl;
    }
}
Tree* Tree::Search(char Ch, bool bL){
    if(nDepth < 0) return NULL;
    int AAA = Ch-32; if((AAA == A) && (!bL || nDepth == 0)) return this;
    for(int i = 0; i < nKol; i++){
        Tree* tmp = SubTrees[i]->Search(Ch,bL);
        if(tmp != NULL) return tmp;
    }
    return NULL;
}

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
        bool RunTree(string Input);
        bool RunTree(string Input, string Wish, Tree* pAnswer);
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
bool Grammar::RunTree(string Input){
    char Ch = PPP[0].Left;
    string W(1,Ch);
    int AAACh = Ch-32;
    Tree* pAnswer = new Tree(AAACh);
    return RunTree(Input,W,pAnswer);
    //delete pAnswer;
}
bool Grammar::RunTree(string Input, string Wish, Tree* pAnswer){
    cout << "***begin-tree" << endl; pAnswer->PrintSym(); cout << endl << "***end-tree" << endl;
    int IS = Input.size();
    int WS = Wish.size();
    if (IS == 0 || WS == 0) return IS == 0 && WS == 0;
    char CFirst = Wish[0];
    if(CFirst != 'E' && CFirst != 'T' && CFirst != 'F'){
        cout << "symbol: " << CFirst << endl;
        if(Input[0] != CFirst) return false;
        return RunTree(Input.substr(1),Wish.substr(1),pAnswer);
    }
    Tree* pNewAnswer = pAnswer->Search(CFirst,true);
    if(pNewAnswer == NULL) return false;
    for(int i = 0; i < 7; i++){
        if(PPP[i].Left != CFirst) continue;
        pNewAnswer->InitSubTrees(PPP[i].Right);
        if(RunTree(Input,PPP[i].Right+Wish.substr(1),pAnswer)) return true;
    }
    return false;
}
int main(int argc, char *argv[])
{
    /*
    Tree TTT(7);
    TTT.Print(); cout << endl << endl;
    TTT.InitSubTrees("rtyuiop"); TTT.Print(); cout << endl << endl;
    Tree* pTTT = TTT.Search('y',true); pTTT->InitSubTrees("poiuytr"); TTT.Print(); cout << endl << endl;
    */

    Grammar GGG;
    GGG.PPP[0].Init('E',"T");
    GGG.PPP[1].Init('E',"T+E");
    GGG.PPP[2].Init('T',"F");
    GGG.PPP[3].Init('T',"F*T");
    GGG.PPP[4].Init('F',"a");
    GGG.PPP[5].Init('F',"b");
    GGG.PPP[6].Init('F',"(E)");
    double start = clock();
    if(GGG.RunTree(S)) cout << "yes" << endl; else cout << "no" << endl;
    cout << (clock()-start)/CLOCKS_PER_SEC << endl;
    return 0;
}
