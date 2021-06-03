/*================================================================
* Filename:BTree.cpp
* Author: KCN_yu
* Createtime:Mon 30 Mar 2020 02:11:27 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

class BTree{
    private:
        bool Empty;
        int A;
        int depth;
        BTree* Left;
        BTree* Right;
    public:
        BTree(){ Empty = true; };
        ~BTree();
        BTree(const BTree& bt);
        BTree(BTree* pbt);
        void Print() { Print(0,6); }
        void Print_KLP();
        void Print_LKP();
        void Print_LPK();
        void Minus_depth(int elem);
        void Delete(int elem);
        bool Add(int Anew);
        int Depth();
        BTree* Search_node(int elem);
        BTree* Search_parent(BTree* node);
        BTree* Search_min_node();
        friend ostream& operator<<(ostream& os, BTree& bt);
    private:
        void Print(int Space, int Spacel);
};
BTree:: BTree(const BTree& bt){
    Empty = true;
    if(bt.Empty) return;
    Empty = false;
    A = bt.A;
    Left = new BTree(*bt.Left);
    Right = new BTree(*bt.Right);
}
BTree:: BTree(BTree* pbt){
    Empty = true;
    if(pbt->Empty) return;
    Empty = false;
    Left = new BTree(pbt->Left);
    Right = new BTree(pbt->Right);
}
BTree:: ~BTree(){
    if(Empty) return;
    delete Left;
    delete Right;
}
ostream& operator<<(ostream& os, BTree& bt){
    if(bt.Empty){
        os << endl;
        return os;
    }
    queue<BTree*> Q;
    Q.push(&bt);
    BTree* currentNode = &bt;
    while(!Q.front()->Empty){
        BTree* tmp = Q.front();Q.pop();
        os << tmp->A << "~" << tmp->depth << " ";
        if(!tmp->Left->Empty) Q.push(tmp->Left);
        if(!tmp->Right->Empty) Q.push(tmp->Right);
        if(!Q.size()) break;
        if(tmp == currentNode){
            os << endl;
            currentNode = Q.back();
        }
    }
    return os;
}
void BTree::Print(int Space, int SpaceL){
    if(Empty) return;
    for(int i = 0; i < Space; i++) cout << " ";
    cout.width(3);
    cout << A << "(" << depth << ")";
    Right->Print(0,SpaceL+6);
    if(Right->Empty) cout << endl;
    Left->Print(SpaceL,SpaceL+6);
}
void BTree::Print_KLP(){
    if(Empty) return;
    else{
        cout << A << " ";
        Left->Print_KLP();
        Right->Print_KLP();
    }
}
void BTree::Print_LKP(){
    if(Empty) return;
    else{
        Left->Print_LKP();
        cout << A << " ";
        Right->Print_LKP();
    }
}
void BTree::Print_LPK(){
    if(Empty) return;
    else{
        Left->Print_LPK();
        Right->Print_LPK();
        cout << A << " ";
    }
}
bool BTree::Add(int Anew){
    if(Empty){
        Empty = false;
        A = Anew;
        Left = new BTree;
        Right = new BTree;
        depth = 0;
        return true;
    }
    if(Anew == A) return false;
    if(Anew < A) Left->Add(Anew);
    if(Anew > A) Right->Add(Anew);
    depth = 1+max(Left->depth,Right->depth);
}// Добавить глубину при добавлении узлов.
int BTree::Depth(){
    if(Empty) return -1;
    return 1+max(Left->Depth(),Right->Depth());
}
BTree* BTree::Search_node(int elem){
    if(Empty) return NULL;
    if(elem == A) return this;
    else if(elem > A) Right->Search_node(elem);
    else Left->Search_node(elem);
}
BTree* BTree::Search_parent(BTree* node){
    if(Empty || this == node) return NULL;
    if(Left == node || Right == node) return this;
    else if(node->A < A) return Left->Search_parent(node);
    else return Right->Search_parent(node);
}
BTree* BTree::Search_min_node(){
    if(Empty) return NULL;
    if(Left->Empty) return this;
    return Left->Search_min_node();
}
void BTree::Minus_depth(int elem){
    if(Empty) return;
    if(elem == A) return;
    depth = Depth();
    if(elem > A) Right->Minus_depth(elem);
    if(elem < A) Left->Minus_depth(elem);
}
void BTree::Delete(int elem){
    if(Empty) return;
    BTree* del = Search_node(elem);
    if(del == NULL) return;
    BTree* parent = Search_parent(del);
    if(del->Left->Empty && del->Right->Empty){
        del->Empty = true;
        Minus_depth(elem);
        //delete del;
        return;
    }
    else if(!del->Left->Empty && del->Right->Empty){
        if(this == del){
            this->A = this->Left->A;
            Left->Delete(this->Left->A);
            return;
        }
        if(parent->Left == del) parent->Left = del->Left;
        else parent->Right = del->Left;
        del->Empty = true;
        delete del;
        Minus_depth(elem);
        return;
    }
    else if(del->Left->Empty && !del->Right->Empty){
        if(this == del){
            this->A = this->Right->A;
            Right->Delete(this->Right->A);
            return;
        }
        if(parent->Left == del) parent->Left = del->Right;
        else parent->Right = del->Right;
        del->Empty = true;
        delete del;
        Minus_depth(elem);
        return;
    }
    else{
        BTree* minRight = del->Right->Search_min_node();
        del->A = minRight->A;
        BTree* parent = Search_parent(minRight);
        if(minRight == del->Right) parent->Right = minRight->Right;
        else parent->Left = minRight->Right;
        minRight->Empty = true;
        delete minRight;
        Minus_depth(elem);
        return;
    }
}
int main(int argc, char *argv[])
{
    BTree BT;
    /*
        8(3)
        /  \
       3(2) 10(2)
      /  \    \
    1(0) 6(1) 14(1)
        / \     /
       4(0)7(0)13(0)
    */
    BT.Add(8);
    BT.Add(3);
    BT.Add(10);
    BT.Add(1);
    BT.Add(6);
    BT.Add(14);
    BT.Add(4);
    BT.Add(7);
    BT.Add(13);
    BT.Print(); cout << endl << endl << endl;
    /*
    BT.Print_KLP(); cout << endl << endl << endl;
    BT.Print_LKP(); cout << endl << endl << endl;
    BT.Print_LPK(); cout << endl << endl << endl;
    */
    cout << BT << endl << endl << endl; //печатать дерево по уровням и печатать глубину каждого узла.
    //cout << BT.Depth() << endl;
    BT.Delete(10);
    BT.Print(); cout << endl << endl << endl;
    cout << BT << endl << endl << endl;
    return 0;
}
