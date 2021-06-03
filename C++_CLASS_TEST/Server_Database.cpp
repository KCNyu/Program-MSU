/*================================================================
 *   Copyright (C) 2021 ChenXuandong Ltd. All rights reserved.
 *
 *   FileName:avltree.cpp
 *   Author:ChenXuandong
 *   Data:2021年01月05日
 *   Description：
 *
 ================================================================*/
#include <arpa/inet.h>
#include <cmath>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define TCP_PORT_NUMBER 5555
#define NUM_CONNECTIONS 2
#define MAX_SIZE 32727
using namespace std;
int connections[NUM_CONNECTIONS];
struct sockaddr_in clients[NUM_CONNECTIONS];
int num_connected = 0;
const int num_stud = 20;
int Index = 0;
int allneednom[num_stud];
int nom_del = -1;
char commands[25][20];

long int RndDouble() {
    int num;
    long int totalNum = 0;
    for (int j = 0; j < 6; j++) {
        num = rand() % 10;
        totalNum += num * pow(10, j);
    }
    return totalNum;
}

char RndCaps() { return (char)(rand() % 26 + 'A'); }

char RndLitt() { return (char)(rand() % 26 + 'a'); }

int RndDiap(int nMin, int nMax) { return rand() % (nMax - nMin) + nMin; }

bool Menshe(string s1, string s2) { return s1 < s2; }

int analyse_commands(char buf[MAX_SIZE]) {
    int num = 0, row = 0, col = 0;
    int len = strlen(buf);
    for (; row < len; row++) {
        if (buf[row] != ' ')
            commands[num][col++] = buf[row];
        else {
            if (col != 0) {
                commands[num++][col] = '\0';
                col = 0;
            }
        }
    }
    if (col != 0)
        commands[num++][col] = '\0';
    for (int i = num; i < 25; i++)
        commands[i][0] = '\0';
    return num;
}

int getindex_afterspace_untilnextword(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '\n' || str[i] == '\0')
            return i;
        if (str[i] == ' ')
            if (str[i + 1] != ' ' && str[i + 1] != '\n' && str[i + 1] != '\0')
                return i;
    }
    return len;
}

char *cutout_str_first_word(char *str) {
    int index1 = getindex_afterspace_untilnextword(str);
    if (str[index1] == '\n')
        return NULL;
    char *struse4 = (char *)malloc((strlen(str) - index1 - 1) * sizeof(char));
    strncpy(struse4, str + index1 + 1, strlen(str) - index1 - 1);
    struse4[strlen(str) - index1 - 1] = '\0';
    return struse4;
}

char *getnextword(char *str) {
    int index1 = getindex_afterspace_untilnextword(str);
    if (str[index1] == '\n')
        return str;
    int index2 = getindex_afterspace_untilnextword(str + index1 + 1);
    char *struse4 = (char *)malloc((index2) * sizeof(char));
    strncpy(struse4, str + index1 + 1, index2);
    struse4[index2] = '\0';
    return struse4;
}

class Fio {
    private:
        string sFio;

    public:
        Fio() {}
        Fio(string str) { sFio = str; }
        Fio(const Fio &fio) { this->sFio = fio.sFio; }
        void RndInit();
        string GetString() { return sFio; }
        void SetsFio(string str) { sFio = str; }
        friend ostream &operator<<(ostream &os, const Fio &fio);
        friend bool operator==(const Fio &fio1, const Fio &fio2);
        friend bool operator<(const Fio &fio1, const Fio &fio2);
        friend bool operator>(const Fio &fio1, const Fio &fio2);
};

void Fio::RndInit() {
    string fnames[6] = {"Mihailof", "Kyznecof", "Smirnof",
        "Vacilief", "Bobof",    "Bitrof"};
    string names[9] = {"Anton", "Vektoliy", "Yuli", "Lef",  "Oleg",
        "Alex",  "Sasha",    "Ivan", "Vacia"};
    sFio = fnames[rand() % 6] + names[rand() % 9] + names[rand() % 9];
}

bool operator==(const Fio &fio1, const Fio &fio2) {
    if (fio1.sFio.length() != fio2.sFio.length())
        return false;
    int len = fio1.sFio.length();
    for (int i = 0; i < len; i++) {
        if (fio1.sFio[i] == fio2.sFio[i])
            continue;
        else
            return false;
    }
    return true;
}

bool operator<(const Fio &fio1, const Fio &fio2) {
    int len = min(fio1.sFio.length(), fio2.sFio.length());
    for (int i = 0; i < len; i++) {
        if (fio1.sFio[i] == fio2.sFio[i])
            continue;
        else if (fio1.sFio[i] < fio2.sFio[i])
            return true;
        else
            return false;
    }
    return fio1.sFio.length() < fio2.sFio.length();
}

bool operator>(const Fio &fio1, const Fio &fio2) {
    int len = min(fio1.sFio.length(), fio2.sFio.length());
    for (int i = 0; i < len; i++) {
        if (fio1.sFio[i] == fio2.sFio[i])
            continue;
        else if (fio1.sFio[i] > fio2.sFio[i])
            return true;
        else
            return false;
    }
    return fio1.sFio.length() > fio2.sFio.length();
}

ostream &operator<<(ostream &os, const Fio &fio) {
    os << fio.sFio;
    return os;
}

class Student {
    private:
        Fio fio;
        long int rRating;
        string country;
        int age;
        string gender;
        int group;

    public:
        Student();
        void RndInit();
        Fio &GetFio() { return fio; }
        long int GetRating() { return rRating; }
        int Getage() { return age; }
        string Getcountry() { return country; }
        string Getgender() { return gender; }
        int Getgroup() { return group; }
        void SetFio(Fio f) { fio = f; }
        void SetRating(long int r) { rRating = r; }
        void Setage(int a) { age = a; }
        void Setcountry(string c) { country = c; }
        void Setgender(string g) { gender = g; }
        void Setgroup(int g) { group = g; }
        friend ostream &operator<<(ostream &os, const Student &stud);
};

Student::Student() {
    fio.SetsFio("Null");
    rRating = 0;
    country = "Null";
    age = 0;
    gender = "Null";
    group = 0;
}

void Student::RndInit() {
    fio.RndInit();
    age = rand() % 14 + 16;
    string genders[2] = {"Male", "Female"};
    gender = genders[rand() % 2];
    group = rand() % 4 + 1;
    string countrys[8] = {"China",  "Russian", "USA",    "Japan",
        "Korean", "UK",      "France", "German"};
    country = countrys[rand() % 8];
    rRating = RndDouble();
}

ostream &operator<<(ostream &os, const Student &stud) {
    os << "Rating: " << stud.rRating;
    os << "   fio: " << stud.fio;
    os << "   country: " << stud.country;
    os << "   age: " << stud.age;
    os << "   gender: " << stud.gender;
    os << "   group: " << stud.group;
    os << endl;
    return os;
}

const int NALL = 32767;

class StudentsAll {
    private:
        int nKol;
        Student students[NALL];

    public:
        StudentsAll() { nKol = 0; }
        void RndInit(int n);
        int GetKol() { return nKol; }
        Student Getstudents(int i) { return students[i]; }
        Fio GetFio(int i) { return students[i].GetFio(); }
        long int GetRating(int i) { return students[i].GetRating(); }
        string Getcountry(int i) { return students[i].Getcountry(); }
        int Getage(int i) { return students[i].Getage(); }
        string Getgender(int i) { return students[i].Getgender(); }
        int Getgroup(int i) { return students[i].Getgroup(); }
        bool Add(Student &st);
        bool Del(int nom);
        void Print(int i);
};

void StudentsAll::RndInit(int n) {
    for (int i = 0; i < n; i++)
        students[i].RndInit();
    nKol = n;
}

bool StudentsAll::Add(Student &st) {
    students[nKol] = st;
    nKol++;
    return true;
}

bool StudentsAll::Del(int nom) {
    for (int i = nom; i < nKol - 1; i++)
        students[i] = students[i + 1];
    nKol--;
    return true;
}

void StudentsAll::Print(int i) { cout << students[i]; }

template <class Key> class AVLTree {
    private:
        int nDepth;
        Key *pKey;
        int Nom;
        AVLTree *Parent;
        AVLTree *Left;
        AVLTree *Right;

    public:
        AVLTree();
        AVLTree(AVLTree &AT);
        AVLTree(AVLTree *pAT);
        ~AVLTree();
        bool Del(Key *AAA, AVLTree *&AT);
        bool Del_Nom(Key *AAA, AVLTree *&AT);
        int Getdepth() { return nDepth; }
        void Setdepth(int ddd) { nDepth = ddd; }
        int GetNom() { return Nom; }
        Key *GetKey() { return pKey; }
        AVLTree *GetLeft() { return Left; }
        AVLTree *GetRight() { return Right; }
        AVLTree *ProtoMin();
        AVLTree *ProtoMax();
        void LL();
        void RR();
        bool Add(Key *pk, int nom);
        void Updata_Nom();
        void Print(int Space, int SpaceR);
        void Search(Key *pk);
        bool OneCheck();
};

template <class Key> AVLTree<Key>::AVLTree() {
    nDepth = -1;
    Left = nullptr;
    Right = nullptr;
}

template <class Key> AVLTree<Key>::AVLTree(AVLTree &AT) {
    nDepth = AT.nDepth;
    if (nDepth < 0)
        return;
    pKey = AT.pKey;
    Nom = AT.Nom;
    Left = new AVLTree(*AT.Left);
    Right = new AVLTree(*AT.Right);
}

template <class Key> AVLTree<Key>::AVLTree(AVLTree *pAT) {
    nDepth = pAT->nDepth;
    if (nDepth < 0)
        return;
    pKey = pAT->pKey;
    Nom = pAT->Nom;
    Left = new AVLTree(pAT->Left);
    Right = new AVLTree(pAT->Right);
}

template <class Key> AVLTree<Key>::~AVLTree() {
    if (nDepth < 0)
        return;
    delete Left;
    delete Right;
}

template <class Key> AVLTree<Key> *AVLTree<Key>::ProtoMin() {
    if (Left->Left->nDepth < 0)
        return this;
    return Left->ProtoMin();
}

template <class Key> AVLTree<Key> *AVLTree<Key>::ProtoMax() {
    if (Right->nDepth < 0)
        return this;
    return Right->ProtoMax();
}

template <class Key> void AVLTree<Key>::Updata_Nom() {
    if (nDepth < 0)
        return;
    if (nom_del < Nom)
        Nom--;
    Left->Updata_Nom();
    Right->Updata_Nom();
}

template <class Key> bool AVLTree<Key>::Del_Nom(Key *AAA, AVLTree *&AT) {
    if (AT->nDepth < 0)
        return false;
    if (*AAA < *pKey) {
        if (AT->Left->Del_Nom(AAA, AT->Left)) {
            if (AT->Left->Getdepth() - AT->Right->Getdepth() == -2)
                if (AT->Right->Left->Getdepth() - AT->Right->Right->Getdepth() == -1)
                    AT->RR();
                else {
                    AT->Right->LL();
                    AT->RR();
                }
            AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
            return true;
        } else
            return false;
    } else if (*pKey < *AAA) {
        if (AT->Right->Del_Nom(AAA, AT->Right)) {
            if (AT->Left->Getdepth() - AT->Right->Getdepth() == 2)
                if (AT->Left->Left->Getdepth() - AT->Left->Right->Getdepth() == 1)
                    AT->LL();
                else {
                    AT->Left->RR();
                    AT->LL();
                }
            AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
            return true;
        } else
            return false;
    } else if (Nom == nom_del) {

        if (AT->Left->nDepth < 0 && AT->Right->nDepth < 0) {
            AT->nDepth--;
            delete Left;
            delete Right;
            return true;
        } else if (AT->Right->nDepth < 0) {
            AT = AT->Left;
            return true;
        } else if (AT->Left->nDepth < 0) {
            AT = AT->Right;
            return true;
        } else {
            AT->pKey = AT->Left->ProtoMax()->pKey;
            AT->Nom = AT->Left->ProtoMax()->Nom;
            AT->Left->ProtoMax()->Nom = nom_del;
            if (AT->Left->Del_Nom(AT->pKey, AT->Left)) {
                if (AT->Left->Getdepth() - AT->Right->Getdepth() == -2)
                    if (AT->Right->Left->Getdepth() - AT->Right->Right->Getdepth() == -1)
                        AT->RR();
                    else {
                        AT->Right->LL();
                        AT->RR();
                    }
                AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
                return true;
            } else
                return false;
        }
    } else {
        if (AT->Left->OneCheck()) {
            if (AT->Left->Del_Nom(AAA, AT->Left)) {
                if (AT->Left->Getdepth() - AT->Right->Getdepth() == -2)
                    if (AT->Right->Left->Getdepth() - AT->Right->Right->Getdepth() == -1)
                        AT->RR();
                    else {
                        AT->Right->LL();
                        AT->RR();
                    }
                AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
                return true;
            } else
                return false;
        } else {
            if (AT->Right->Del_Nom(AAA, AT->Right)) {
                if (AT->Left->Getdepth() - AT->Right->Getdepth() == 2)
                    if (AT->Left->Left->Getdepth() - AT->Left->Right->Getdepth() == 1)
                        AT->LL();
                    else {
                        AT->Left->RR();
                        AT->LL();
                    }
                AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
                return true;
            } else
                return false;
        }
    }
}

template <class Key> bool AVLTree<Key>::Del(Key *AAA, AVLTree *&AT) {
    if (AT->nDepth < 0)
        return false;
    else if (*pKey > *AAA) {
        if (AT->Left->Del(AAA, AT->Left)) {
            if (AT->Left->Getdepth() - AT->Right->Getdepth() == -2)
                if (AT->Right->Left->Getdepth() - AT->Right->Right->Getdepth() == -1)
                    AT->RR();
                else {
                    AT->Right->LL();
                    AT->RR();
                }
            AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
            return true;
        } else
            return false;
    } else if (*pKey < *AAA) {
        if (AT->Right->Del(AAA, AT->Right)) {
            if (AT->Left->Getdepth() - AT->Right->Getdepth() == 2)
                if (AT->Left->Left->Getdepth() - AT->Left->Right->Getdepth() == 1)
                    AT->LL();
                else {
                    AT->Left->RR();
                    AT->LL();
                }
            AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
            return true;
        } else
            return false;
    } else if (AT->Left->nDepth < 0 && AT->Right->nDepth < 0) {
        AT->nDepth--;
        if (nom_del == -1)
            nom_del = Nom;
        delete Left;
        delete Right;
        return true;
    } else if (AT->Right->nDepth < 0) {
        if (nom_del == -1)
            nom_del = Nom;
        AT = AT->Left;
        return true;
    } else if (AT->Left->nDepth < 0) {
        if (nom_del == -1)
            nom_del = Nom;
        AT = AT->Right;
        return true;
    } else {
        if (nom_del == -1)
            nom_del = Nom;
        AT->pKey = AT->Left->ProtoMax()->pKey;
        AT->Nom = AT->Left->ProtoMax()->Nom;
        if (AT->Left->Del(AT->pKey, AT->Left)) {
            if (AT->Left->Getdepth() - AT->Right->Getdepth() == -2)
                if (AT->Right->Left->Getdepth() - AT->Right->Right->Getdepth() == -1)
                    AT->RR();
                else {
                    AT->Right->LL();
                    AT->RR();
                }
            AT->nDepth = max(AT->Left->Getdepth(), AT->Right->Getdepth()) + 1;
            return true;
        } else
            return false;
    }
}

template <class Key> void AVLTree<Key>::LL() {
    AVLTree *tr = new AVLTree(*this);
    AVLTree *tl = new AVLTree(Left);
    delete tr->Left;
    tr->Left = tl->Right;
    tr->nDepth = max(tr->Left->Getdepth(), tr->Right->Getdepth()) + 1;
    pKey = Left->pKey;
    Nom = Left->Nom;
    delete Left;
    delete Right;
    Left = new AVLTree(tl->Left);
    Right = new AVLTree(tr);
    nDepth = max(Left->Getdepth(), Right->Getdepth()) + 1;
}

template <class Key> void AVLTree<Key>::RR() {
    AVLTree *tr = new AVLTree(Right);
    AVLTree *tl = new AVLTree(*this);
    delete tl->Right;
    tl->Right = tr->Left;
    tl->nDepth = max(tl->Left->Getdepth(), tl->Right->Getdepth()) + 1;
    pKey = Right->pKey;
    Nom = Right->Nom;
    delete Left;
    delete Right;
    Left = new AVLTree(tl);
    Right = new AVLTree(tr->Right);
    nDepth = max(Left->Getdepth(), Right->Getdepth()) + 1;
}

template <class Key> bool AVLTree<Key>::Add(Key *pk, int nom) {
    if (nDepth < 0) {
        nDepth++;
        pKey = pk;
        Nom = nom;
        Left = new AVLTree;
        Right = new AVLTree;
        return true;
    }
    if (*pk < *pKey) {
        if (!Left->Add(pk, nom))
            return false;
        else if (Left->Getdepth() - Right->Getdepth() == 2)
            if (Left->Left->Getdepth() - Left->Right->Getdepth() == 1)
                LL();
            else {
                Left->RR();
                LL();
            }
    } else {
        if (!Right->Add(pk, nom))
            return false;
        else if (Left->Getdepth() - Right->Getdepth() == -2)
            if (Right->Left->Getdepth() - Right->Right->Getdepth() == -1)
                RR();
            else {
                Right->LL();
                RR();
            }
    }
    nDepth = max(Left->Getdepth(), Right->Getdepth()) + 1;
    return true;
}

template <class Key> void AVLTree<Key>::Print(int Space, int SpaceR) {
    if (nDepth < 0)
        return;
    for (int i = 0; i < Space; i++)
        cout << " ";
    cout.width(3);
    cout << *pKey;
    //	cout <<"("<< Getdepth() <<")";
    //  cout << "("<< GetNom() <<")";
    Left->Print(0, SpaceR + 6);
    if (Left->nDepth < 0)
        cout << endl;
    Right->Print(SpaceR, SpaceR + 6);
}

template <class Key> bool AVLTree<Key>::OneCheck() {
    if (nDepth < 0)
        return false;
    if (nom_del == Nom)
        return true;
    else
        return Right->OneCheck() || Left->OneCheck();
}

template <class Key> void AVLTree<Key>::Search(Key *pk) {
    if (nDepth < 0)
        return;
    if (*pKey == *pk) {
        allneednom[Index] = this->Nom;
        Index++;
        Left->Search(pk);
        Right->Search(pk);
    } else if (*pk < *pKey)
        Left->Search(pk);
    else
        Right->Search(pk);
}

int main(int argc, char **argv) {
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "socket() error!" << endl;
        exit(-1);
    }
    struct sockaddr_in server_addr;
    int on = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_port = htons(TCP_PORT_NUMBER);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, (struct sockaddr *)&server_addr,
                sizeof server_addr)) {
        cerr << "bind() error!" << endl;
        exit(-1);
    }
    if (listen(server_socket, 5)) {
        cerr << "listen() error!" << endl;
        exit(-1);
    }
    int client_socket;
    while (1) {
        if ((client_socket = accept(server_socket, NULL, NULL)) < 0) {
            cerr << "accept() error!" << endl;
            exit(1);
        }
        cout << "A new client is connected, and his socket is " << client_socket
            << endl;
        int itmp = 0;
        AVLTree<string> *ATcountrys = new AVLTree<string>;
        AVLTree<long int> *ATratings = new AVLTree<long int>;
        AVLTree<Fio> *ATfios = new AVLTree<Fio>;
        AVLTree<string> *ATgenders = new AVLTree<string>;
        AVLTree<int> *ATages = new AVLTree<int>;
        AVLTree<int> *ATgroups = new AVLTree<int>;
        StudentsAll stall;
        Student tmpstud;
        string tmpcountrys[100];
        long int tmpratings[100];
        Fio tmpfios[100];
        string tmpgenders[100];
        int tmpages[100];
        int tmpgroups[100];
        for (itmp = 0; itmp < num_stud; itmp++) {
            tmpstud.RndInit();
            stall.Add(tmpstud);
            tmpcountrys[itmp] = stall.Getcountry(itmp);
            tmpratings[itmp] = stall.GetRating(itmp);
            tmpfios[itmp] = stall.GetFio(itmp);
            tmpgenders[itmp] = stall.Getgender(itmp);
            tmpages[itmp] = stall.Getage(itmp);
            tmpgroups[itmp] = stall.Getgroup(itmp);
            ATcountrys->Add(&tmpcountrys[itmp], itmp + 1);
            ATratings->Add(&tmpratings[itmp], itmp + 1);
            ATfios->Add(&tmpfios[itmp], itmp + 1);
            ATgenders->Add(&tmpgenders[itmp], itmp + 1);
            ATages->Add(&tmpages[itmp], itmp + 1);
            ATgroups->Add(&tmpgroups[itmp], itmp + 1);
        }
        char message[MAX_SIZE];
        char str[300] = {0};
        char mes[MAX_SIZE];
        int numcom = 0;
        while (1) {
            read(client_socket, str, sizeof(str));
            numcom = analyse_commands(str);
            if (!strncmp(commands[0], "SHOW", 4) ||
                    !strncmp(commands[0], "FIND", 4)) {
                int save_fd = dup(STDOUT_FILENO);
                int fd1 = open("out.txt", (O_RDWR | O_CREAT), 0644);
                dup2(fd1, STDOUT_FILENO);
                if (!strncmp(commands[0], "SHOW", 4))
                    for (int i = 0; i < stall.GetKol(); i++)
                        stall.Print(i);
                else {
                    if (!strncmp(commands[1], "\n", 1)) {
                        strncpy(mes, "FIND ()\n", 9);
                    } else {
                        string nextword = getnextword(str);
                        for (int i = 0; i < stall.GetKol(); i++)
                            allneednom[i] = -1;
                        Index = 0;
                        if (!strncmp(commands[1], "China", 5) ||
                                !strncmp(commands[1], "Russian", 7) ||
                                !strncmp(commands[1], "German", 6) ||
                                !strncmp(commands[1], "Japan", 5) ||
                                !strncmp(commands[1], "Korean", 6) ||
                                !strncmp(commands[1], "France", 6) ||
                                !strncmp(commands[1], "USA", 3) ||
                                !strncmp(commands[1], "UK", 2)) {
                            ATcountrys->Search(&nextword);
                        } else if (!strncmp(commands[1], "Male", 4) ||
                                !strncmp(commands[1], "Female", 6)) {
                            ATgenders->Search(&nextword);
                        } else if (!strncmp(commands[1], "Group", 5)) {
                            char *stmp = commands[2];
                            int n = atoi(stmp);
                            ATgroups->Search(&n);
                        } else if (!strncmp(commands[1], "Age", 3)) {
                            char *stmp = commands[2];
                            int n = atoi(stmp);
                            ATages->Search(&n);
                        } else if (!strncmp(commands[1], "Rating", 6)) {
                            long int n = atoi(commands[2]);
                            ATratings->Search(&n);
                        } else {
                            strncpy(mes, "FIND (wrong)\n", 14);
                        }
                        for (int i = 0; i < num_stud; i++) {
                            if (allneednom[i] == -1)
                                break;
                            stall.Print(allneednom[i] - 1);
                            allneednom[i] = -1;
                        }
                        Index = 0;
                    }
                }
                close(fd1);
                dup2(save_fd, STDOUT_FILENO);
                FILE *fp1 = fopen("out.txt", "r");
                char tmp;
                int m = 0;
                for (m = 0;; m++) {
                    tmp = fgetc(fp1);
                    if (tmp == EOF)
                        break;
                    mes[m] = tmp;
                }
                mes[m] = '\0';
                fclose(fp1);
                remove("out.txt");
            } else if (!strncmp(commands[0], "QUIT", 4))
                strncpy(mes, "  quiting...\n", 13);
            else if (!strncmp(commands[0], "ADD", 3)) {
                allneednom[0] = -1;
                Index = 0;
                if (commands[2][0] != '\0') {
                    long int serrating = atoi(commands[2]);
                    ATratings->Search(&serrating);
                }
                if (allneednom[0] != -1) {
                    strncpy(mes, "have same rating can't add", 26);
                    for (int i = 0; allneednom[i] != -1; i++)
                        allneednom[i] = -1;
                    Index = 0;
                } else {
                    int flag = 0;
                    if (strncmp(commands[1], "Rating", 6))
                        flag = 1;
                    if (strncmp(commands[3], "Fio", 3))
                        flag = 1;
                    if (strncmp(commands[5], "Country", 7))
                        flag = 1;
                    if (strncmp(commands[7], "Age", 3))
                        flag = 1;
                    if (strncmp(commands[9], "Gender", 6))
                        flag = 1;
                    if (strncmp(commands[11], "Group", 5))
                        flag = 1;
                    if (flag == 1)
                        strncpy(mes, "not correct add", 15);
                    else {
                        Student addstud;
                        addstud.SetRating(atoi(commands[2]));
                        Fio afio(commands[4]);
                        addstud.SetFio(afio);
                        addstud.Setcountry(commands[6]);
                        addstud.Setage(atoi(commands[8]));
                        addstud.Setgender(commands[10]);
                        addstud.Setgroup(atoi(commands[12]));
                        stall.Add(addstud);
                        int nowkol = stall.GetKol();
                        tmpcountrys[itmp] = stall.Getcountry(nowkol - 1);
                        tmpratings[itmp] = stall.GetRating(nowkol - 1);
                        tmpfios[itmp] = stall.GetFio(nowkol - 1);
                        tmpgenders[itmp] = stall.Getgender(nowkol - 1);
                        tmpages[itmp] = stall.Getage(nowkol - 1);
                        tmpgroups[itmp] = stall.Getgroup(nowkol - 1);
                        ATcountrys->Add(&tmpcountrys[itmp], nowkol);
                        ATratings->Add(&tmpratings[itmp], nowkol);
                        ATfios->Add(&tmpfios[itmp], nowkol);
                        ATgenders->Add(&tmpgenders[itmp], nowkol);
                        ATages->Add(&tmpages[itmp], nowkol);
                        ATgroups->Add(&tmpgroups[itmp], nowkol);
                        itmp++;
                        strncpy(mes, "success add", 11);
                    }
                }
            } else if (!strncmp(commands[0], "DEL", 3)) {
                if (!strncmp(commands[1], "Rating", 6)) {
                    allneednom[0] = -1;
                    Index = 0;
                    if (commands[2][0] != '\0') {
                        long int serrating = atoi(commands[2]);
                        ATratings->Search(&serrating);
                    }
                    if (allneednom[0] == -1 || commands[2][0] == '\0') {
                        if (allneednom[0] == -1)
                            strncpy(mes, "don't have this rating, can't del", 33);
                        else
                            strncpy(mes, "no rating", 9);
                        for (int i = 0; allneednom[i] != -1; i++)
                            allneednom[i] = -1;
                        Index = 0;
                    } else {

                        long int num_rating = 0;
                        long int flag = 1;
                        num_rating = atoi(commands[2]);
                        ATratings->Del(&num_rating, ATratings);
                        ATratings->Updata_Nom();
                        string c = stall.Getcountry(nom_del - 1);
                        Fio f = stall.GetFio(nom_del - 1);
                        string gen = stall.Getgender(nom_del - 1);
                        int a = stall.Getage(nom_del - 1);
                        int gr = stall.Getgroup(nom_del - 1);
                        ATages->Del_Nom(&a, ATages);
                        ATfios->Del_Nom(&f, ATfios);
                        ATgenders->Del_Nom(&gen, ATgenders);
                        ATgroups->Del_Nom(&gr, ATgroups);
                        ATcountrys->Del_Nom(&c, ATcountrys);
                        ATages->Updata_Nom();
                        ATfios->Updata_Nom();
                        ATgenders->Updata_Nom();
                        ATgroups->Updata_Nom();
                        ATcountrys->Updata_Nom();
                        stall.Del(nom_del - 1);
                        nom_del = -1;
                        strncpy(mes, "success del", 11);
                    }
                } else
                    strncpy(mes, "not correct del", 15);
            } else {
                strncpy(mes, "not command", 11);
            }
            write(client_socket, mes, sizeof(mes));
            memset(str, 0, sizeof(str));
            memset(mes, 0, sizeof(mes));
        }
    }
    close(client_socket);
    close(server_socket);
    return 0;
}
