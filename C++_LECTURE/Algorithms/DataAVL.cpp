/*================================================================
* Filename:BasicData.cpp
* Author: KCN_yu
* Createtime:Wed 10 Jun 2020 05:26:46 PM CST
================================================================*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <iomanip>
using namespace std;

long int RndDouble()
{
    return rand() * 32768.0 + rand();
}

char RndCaps()
{
    return 'A' + (rand() % 26);
}

char RndLitt()
{
    return 'a' + (rand() % 26);
}
int RndDiap(int nMin, int nMax)
{
    return nMin + rand() % (nMax - nMin + 1);
}
bool Menshe(string s1, string s2)
{
    if (s2.size() == 0)
        return false;
    if (s1.size() == 0)
        return true;
    char c1 = s1[0], c2 = s2[0];
    if (c1 == c2)
        return Menshe(s1.substr(1), s2.substr(1));
    if (c2 == ' ')
        return false;
    if (c1 == ' ')
        return true;
    return c1 < c2;
}
class Fio
{
private:
    string sFio;

public:
    Fio() {}
    Fio(const Fio &fio) { this->sFio = fio.sFio; }
    void RndInit();
    string GetString() { return sFio; }
    friend ostream &operator<<(ostream &os, const Fio &f);
    friend bool operator==(const Fio &f1, const Fio &f2);
    friend bool operator<(const Fio &f1, const Fio &f2);
    friend bool operator>(const Fio &f1, const Fio &f2) { return !(f1 < f2); }
};

void Fio::RndInit()
{
    sFio = "";
    int L = RndDiap(1, 8);
    sFio += RndCaps();
    for (int i = 0; i < L; i++)
        sFio += RndLitt();
    L = RndDiap(1, 8);
    sFio += ' ';
    sFio += RndCaps();
    for (int i = 0; i < L; i++)
        sFio += RndLitt();
    L = RndDiap(1, 8);
    sFio += ' ';
    sFio += RndCaps();
    for (int i = 0; i < L; i++)
        sFio += RndLitt();
}

ostream &operator<<(ostream &os, const Fio &f)
{
    os << f.sFio;
    int T = 30 - f.sFio.size();
    if (T <= 0)
        return os;
    for (int i = 0; i < T; i++)
        os << " ";
    return os;
}

bool operator==(const Fio &f1, const Fio &f2)
{
    return f1.sFio == f2.sFio;
}

bool operator<(const Fio &f1, const Fio &f2)
{
    return Menshe(f1.sFio, f2.sFio);
}

enum Country
{
    Rossia,
    Germania,
    Kitay,
    Pindostan,
    Antarktida,
    Gvatemala,
    Gonduras
};

class Student
{
private:
    Fio fio;
    long int rRating;
    Country cCountry;
    int nGruppe;
    int DD, MM, GG;

public:
    void RndInit();
    Fio &GetFio() { return fio; }
    long int GetRating() { return rRating; }
    Country GetCountry() { return cCountry; }
    friend ostream &operator<<(ostream &os, const Student &s);
};

void Student::RndInit()
{
    fio.RndInit();
    rRating = RndDouble();
    int T = RndDiap(0, 6);
    switch (T)
    {
    case 0:
        cCountry = Rossia;
        break;
    case 1:
        cCountry = Germania;
        break;
    case 2:
        cCountry = Kitay;
        break;
    case 3:
        cCountry = Antarktida;
        break;
    case 4:
        cCountry = Gvatemala;
        break;
    case 5:
        cCountry = Gonduras;
        break;
    }
    nGruppe = RndDiap(101, 499);
    DD = RndDiap(1, 28);
    MM = RndDiap(1, 12);
    GG = RndDiap(1990, 2012);
}
ostream &operator<<(ostream &os, const Student &s)
{
    os << "FIO: " << s.fio << " ";
    os.width(13);
    os << "Rating: " << setw(15) << s.rRating << " ";
    os << "Country: ";
    switch (s.cCountry)
    {
    case Rossia:
        os << "Rossia      ";
        break;
    case Germania:
        os << "Germania    ";
        break;
    case Kitay:
        os << "Kitay       ";
        break;
    case Antarktida:
        os << "Antarktida  ";
        break;
    case Gvatemala:
        os << "Gvatemala   ";
        break;
    case Gonduras:
        os << "Gonduras    ";
        break;
    }
    os << "Gruppa: " << s.nGruppe << " ";
    if (s.DD < 10)
        os << 0;
    os << s.DD << ".";
    if (s.MM < 10)
        os << 0;
    os << s.MM << ".";
    os.width(4);
    os << s.GG;
    os << endl;
    return os;
}

const int NALL = 32767;

class StudentsAll
{
private:
    int nKol;
    Student students[NALL];

public:
    StudentsAll() { nKol = 0; }
    int GetKol() { return nKol; }
    Fio GetFio(int i) { return students[i].GetFio(); }
    long int GetRating(int i) { return students[i].GetRating(); }
    Country GetCountry(int i) { return students[i].GetCountry(); }
    bool Add(Student &st);
    friend ostream &operator<<(ostream &os, const StudentsAll &stall);
} stall;

bool StudentsAll::Add(Student &st)
{
    if (nKol >= NALL)
        return false;
    students[nKol++] = st;
    return true;
}

ostream &operator<<(ostream &os, const StudentsAll &stall)
{
    for (int i = 0; i < stall.nKol; i++)
    {
        os.width(4);
        os << i << ".  ";
        os << stall.students[i];
    }
    return os;
}
template <class Key>
class AVLTree
{
private:
    bool Empty;
    int depth;
    int nNom;
    Key *pKey;
    AVLTree *Left;
    AVLTree *Right;

public:
    AVLTree<Key>()
    {
        Empty = true;
        depth = -1;
    }
    ~AVLTree();
    void Update_depth(AVLTree *node) { node->depth = max(node->Left->depth, node->Right->depth) + 1; }
    bool Add(Key *pKey, AVLTree *&node, int nNom);
    bool Delete(Key *elem, AVLTree *&node);
    int Depth();
    AVLTree *LL();
    AVLTree *RR();
    AVLTree *LR();
    AVLTree *RL();
    AVLTree *Search_minNode_parent();
    int Search(Key *pKey);
};
template <class Key>
AVLTree<Key>::~AVLTree()
{
    if (Empty)
        return;
    delete Left;
    delete Right;
}
template <class Key>
AVLTree<Key> *AVLTree<Key>::LL()
{
    AVLTree<Key> *temp;

    temp = this->Left;
    this->Left = temp->Right;
    temp->Right = this;

    Update_depth(this);
    Update_depth(temp);

    return temp;
}
template <class Key>
AVLTree<Key> *AVLTree<Key>::RR()
{
    AVLTree<Key> *temp;

    temp = this->Right;
    this->Right = temp->Left;
    temp->Left = this;

    Update_depth(this);
    Update_depth(temp);

    return temp;
}
template <class Key>
AVLTree<Key> *AVLTree<Key>::LR()
{
    this->Left = Left->RR();
    return this->LL();
}
template <class Key>
AVLTree<Key> *AVLTree<Key>::RL()
{
    this->Right = Right->LL();
    return this->RR();
}
template <class Key>
bool AVLTree<Key>::Add(Key *pKey, AVLTree *&node, int nNom)
{
    if (node->Empty)
    {
        node->Empty = false;
        node->pKey = pKey;
        node->Left = new AVLTree<Key>;
        node->Right = new AVLTree<Key>;
        node->depth = 0;
        node->nNom = nNom;
        return true;
    }
    if (*pKey == *(node->pKey))
        return false;
    if (*pKey < *(node->pKey))
        Add(pKey, node->Left, nNom);
    if (*pKey > *(node->pKey))
        Add(pKey, node->Right, nNom);
    Update_depth(node);

    int balanceFactor = node->Right->depth - node->Left->depth;
    if (balanceFactor == -2)
    {
        if (*pKey < *(node->Left->pKey))
            node = node->LL();
        else
            node = node->LR();
    }
    if (balanceFactor == 2)
    {
        if (*pKey > *(node->Right->pKey))
            node = node->RR();
        else
            node = node->RL();
    }
    return true;
}
template <class Key>
AVLTree<Key> *AVLTree<Key>::Search_minNode_parent()
{
    if (Left->Empty || Left->Left->Empty)
        return this;
    else
        return Left->Search_minNode_parent();
}
template <class Key>
bool AVLTree<Key>::Delete(Key *elem, AVLTree *&node)
{
    if (node->Empty)
        return false;
    if (*elem < *(node->pKey))
        Delete(elem, node->Left);
    else if (*elem > *(node->pKey))
        Delete(elem, node->Right);
    else
    {
        if (node->Left->Empty && node->Right->Empty)
        {
            node->Empty = true;
            goto balance;
        }
        else if (node->Left->Empty && !node->Right->Empty)
        {
            node->Empty = true;
            node = node->Right;
            goto balance;
        }
        else if (!node->Left->Empty && node->Right->Empty)
        {
            node->Empty = true;
            node = node->Left;
            goto balance;
        }
        else if (!node->Left->Empty && !node->Right->Empty)
        {
            AVLTree *minNode_parent = node->Right->Search_minNode_parent();
            AVLTree *minNode = minNode_parent->Left;
            if (minNode->Empty)
            {
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
    if (balanceFactor == -2)
    {
        if (elem < node->Left->A)
            node = node->LL();
        else
            node = node->LR();
    }
    if (balanceFactor == 2)
    {
        if (elem > node->Right->A)
            node = node->RR();
        else
            node = node->RL();
    }
    return true;
}
template <class Key>
int AVLTree<Key>::Search(Key *pKey)
{
    if (depth < 0)
        return -1;
    if (*(this->pKey) == *pKey)
        return this->nNom;
    return (*(this->pKey) < *pKey) ? Right->Search(pKey) : Left->Search(pKey);
}
template <class Key>
class DataAVL
{
private:
    AVLTree<Key> *root;

public:
    DataAVL() { root = new AVLTree<Key>; }
    bool Add(Key *pKey, int nNom) { return root->Add(pKey, root, nNom); }
    bool Delete(Key *elem) { return root->Delete(elem, root); }
    int Search(Key *pKey) { return root->Search(pKey); }
    ~DataAVL() { delete root; }
};
int main(int argc, char *argv[])
{
    StudentsAll stall;
    DataAVL<Fio> avlFIO; 
    DataAVL<long> avlRating;
    int nStud = 100;
    for (int i = 0; i < nStud; i++)
    {
        Student st;
        st.RndInit();
        stall.Add(st);

        Fio *fio = new Fio(stall.GetFio(i));
        if (avlFIO.Search(fio) >= 0)
        {
            continue;
        }

        long *T = new long(st.GetRating());
        if (avlRating.Search(T) >= 0)
        {
            continue;
        }
        avlFIO.Add(fio,  stall.GetKol() - 1);
        avlRating.Add(T,  stall.GetKol() - 1);
    }
    cout << stall << endl
         << endl;
    Fio fio = stall.GetFio(95);
    cout << fio << endl;

    cout << avlFIO.Search(&fio) << endl
         << endl;

    long int rating = stall.GetRating(80);
    cout << rating << endl;

    cout << avlRating.Search(&rating) << endl
         << endl;
    cout << "***** KONEC" << endl;
    return 0;
}
