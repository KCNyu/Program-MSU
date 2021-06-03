
#include <iostream>
#include "list.h"
using namespace std;



List::List () :lst(NULL) {}

List::List(char c) {
    lst=new Node(c);
}

List::List(const char* s) {
    if (*s=='\0') {
        lst=NULL;
        return;
    }

    Node *p;
    lst= p= new Node(*s++);

    while (*s!='\0') {
        p= p->next= new Node(*s++);
    }
}

bool List::empty() const {return lst==NULL;}

List::List (const List& l) {
    if (l.empty()) {
        lst=NULL;
        return;
    }
    Node *p, *pl=l.lst;
    p= lst= new Node(pl->elem);
    pl=pl->next;
    while (pl!=NULL) {
        p->next= new Node(pl->elem);
        p=p->next;
        pl=pl->next;
    }
}

void List::clear() {
    Node *pl;
    while (lst!=NULL) {
        pl=lst;
        lst=lst->next;
        delete pl;
    }
}

List::~List() {
    this->clear();
}


List List::operator+ (const List& l) {
    List::Node *p,*pl;

    if(this->empty()){
            return l;
    }

    List res(*this);

    p=res.lst;
    while(p->next!=NULL){
        p=p->next;
    }

    pl=l.lst;

    while (pl!=NULL) {
        p=p->next=new Node(pl->elem);
        pl=pl->next;
    }

    return res;
}

List List::operator- (const char c) {
    List::Node *bef,*cur,*tmp = NULL;
    if(this->empty()){
        return *this;
    }
    List res(*this);
    bef = cur = res.lst;
    while(cur != NULL){
        if(cur->elem != c){
            bef = cur;
            cur = cur->next;
        }
        else{
            if(cur == res.lst){
                tmp = cur;
                res.lst = cur->next;
                bef = cur->next;
                cur = cur->next;
                delete tmp;
            }
            else{
                tmp = cur;
                bef->next = cur->next;
                cur = cur->next;
                delete tmp;
            }
        }
    }
    return res;
}
List operator+ (const char c, const List& l){
    List res1(c);
    List res2(l);
    return res1+res2;
}
List operator- (const char c, const List& l){
    List::Node *bef,*cur,*tmp = NULL;
    if(l.empty()){
        return l;
    }
    List res(l);
    bef = cur = res.lst;
    while(cur != NULL){
        if(cur->elem == c){
            bef = cur;
            cur = cur->next;
        }
        else{
            if(cur == res.lst){
                tmp = cur;
                res.lst = cur->next;
                bef = cur->next;
                cur = cur->next;
                delete tmp;
            }
            else{
                tmp = cur;
                bef->next = cur->next;
                cur = cur->next;
                delete tmp;
            }
        }
    }
    return res;
}
ostream& operator<< (ostream& s, const List& l) {
    if (l.lst==NULL) {
        s<<"";
        return s;
    }

    List::Node *pl=l.lst;
    while (pl!=NULL) {
        s<<pl->elem;
        pl=pl->next;

    }

    return s;
}


List& List::operator= (const List& l) {
    Node *p,*pl;

    if (&l==this){
            return *this;
    }

    this->clear();

    if (l.lst==NULL) {
        return *this;
    }
    p=lst= new Node(l.lst->elem);
    pl=l.lst->next;
    while (pl!=NULL) {
        p->next= new Node(pl->elem);
        p=p->next;
        pl=pl->next;

    }

    return *this;
}


