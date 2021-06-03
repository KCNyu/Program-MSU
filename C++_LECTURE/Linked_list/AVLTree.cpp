/*================================================================
* Filename:AVLTree.cpp
* Author: KCN_yu
* Createtime:Mon 30 Mar 2020 02:11:27 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

class AVLTree{
    private:
        bool Empty;
        int A;
        int depth;
        AVLTree* Left;
        AVLTree* Right;
    public:
        AVLTree(){ Empty = true; depth = -1; }
        ~AVLTree();
        AVLTree(const AVLTree& bt);
        AVLTree(AVLTree* pbt);
        void Print() { Print(0,6); }
        void Update_depth(AVLTree* node) { node->depth = max(node->Left->depth,node->Right->depth)+1; }
        bool Add_avl(int Anew, AVLTree*& node);
        bool Delete(int elem, AVLTree*& node);
        int Depth();
        AVLTree* LL();
        AVLTree* RR();
        AVLTree* LR();
        AVLTree* RL();
        AVLTree* Search_minNode_parent();
        friend ostream& operator<<(ostream& os, AVLTree& bt);
    private:
        void Print(int Space, int Spacel);
};
AVLTree:: AVLTree(const AVLTree& bt){
    Empty = true;
    if(bt.Empty) return;
    Empty = false;
    A = bt.A;
    Left = new AVLTree(*bt.Left);
    Right = new AVLTree(*bt.Right);
}
AVLTree:: AVLTree(AVLTree* pbt){
    Empty = true;
    if(pbt->Empty) return;
    Empty = false;
    Left = new AVLTree(pbt->Left);
    Right = new AVLTree(pbt->Right);
}
AVLTree:: ~AVLTree(){
    if(Empty) return;
    delete Left;
    delete Right;
}
ostream& operator<<(ostream& os, AVLTree& bt){
    if(bt.Empty){
        os << endl;
        return os;
    }
    queue<AVLTree*> Q;
    Q.push(&bt);
    AVLTree* currentNode = &bt;
    while(!Q.front()->Empty){
        AVLTree* tmp = Q.front();Q.pop();
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
void AVLTree::Print(int Space, int SpaceL){
    if(Empty) return;
    for(int i = 0; i < Space; i++) cout << " ";
    cout.width(3);
    cout << A << "(" << depth << ")";
    Right->Print(0,SpaceL+6);
    if(Right->Empty) cout << endl;
    Left->Print(SpaceL,SpaceL+6);
}
AVLTree* AVLTree::LL(){
    AVLTree* temp;

    temp = this->Left;
    this->Left = temp->Right;
    temp->Right = this;

    Update_depth(this);
    Update_depth(temp);

    return temp;
}
AVLTree* AVLTree::RR(){
    AVLTree* temp;

    temp = this->Right;
    this->Right = temp->Left;
    temp->Left = this;

    Update_depth(this);
    Update_depth(temp);

    return temp;
}
AVLTree* AVLTree::LR(){
    this->Left = Left->RR();
    return this->LL();
}
AVLTree* AVLTree::RL(){
    this->Right = Right->LL();
    return this->RR();
}
bool AVLTree::Add_avl(int Anew, AVLTree*& node){
    if(node->Empty){
        node->Empty = false;
        node->A = Anew;
        node->Left = new AVLTree;
        node->Right = new AVLTree;
        node->depth = 0;
        return true;
    }
    if(Anew == node->A) return false;
    if(Anew < node->A) Add_avl(Anew,node->Left);
    if(Anew > node->A) Add_avl(Anew,node->Right);
    Update_depth(node);

    int balanceFactor = node->Right->depth - node->Left->depth;
    if(balanceFactor == -2){
        if(Anew < node->Left->A) node = node->LL();
        else node = node->LR();
    }
    if(balanceFactor == 2){
        if(Anew > node->Right->A) node = node->RR();
        else node = node->RL();
    }
}
AVLTree* AVLTree::Search_minNode_parent(){
    if(Left->Empty || Left->Left->Empty) return this;
    else return Left->Search_minNode_parent();
}
bool AVLTree::Delete(int elem, AVLTree*& node){
    if(node->Empty) return false;
    if(elem < node->A) Delete(elem,node->Left);
    else if(elem > node->A) Delete(elem,node->Right);
    else{
        if(node->Left->Empty && node->Right->Empty){
            node->Empty = true;
            goto balance;
        }
        else if(node->Left->Empty && !node->Right->Empty){
            node->Empty = true;
            node = node->Right;
            goto balance;
        }
        else if(!node->Left->Empty && node->Right->Empty){
            node->Empty = true;
            node = node->Left;
            goto balance;
        }
        else if(!node->Left->Empty && !node->Right->Empty){
            AVLTree* minNode_parent = node->Right->Search_minNode_parent();
            AVLTree* minNode = minNode_parent->Left;
            if(minNode->Empty){
                node->A = node->Right->A;
                node->Right = minNode_parent->Right;
                minNode_parent->Empty = true;
                goto balance;
            }
            node->A = minNode->A;
            minNode_parent->Left = minNode->Right;
            minNode->Empty = true;
            goto balance;
        }
    }
balance:
    int balanceFactor = node->Right->depth - node->Left->depth;
    if(balanceFactor == -2){
        if(elem < node->Left->A) node = node->LL();
        else node = node->LR();
    }
    if(balanceFactor == 2){
        if(elem > node->Right->A) node = node->RR();
        else node = node->RL();
    }
    return true;
}
int main(int argc, char *argv[])
{
    AVLTree* BT = new AVLTree;
    BT->Add_avl(3,BT);
    BT->Add_avl(2,BT);
    BT->Add_avl(1,BT);
    BT->Add_avl(4,BT);
    BT->Add_avl(5,BT);
    BT->Add_avl(6,BT);
    BT->Add_avl(7,BT);
    BT->Add_avl(16,BT);
    BT->Add_avl(15,BT);
    BT->Add_avl(14,BT);
    BT->Add_avl(13,BT);
    BT->Add_avl(12,BT);
    BT->Add_avl(11,BT);
    BT->Add_avl(10,BT);
    BT->Add_avl(8,BT);
    BT->Add_avl(9,BT);
    BT->Print(); cout << endl << endl << endl;
    //cout << *BT << endl << endl << endl; //печатать дерево по уровням и печатать глубину каждого узла.
    BT->Delete(11,BT);
    BT->Print(); cout << endl << endl << endl;
    return 0;
}
