/*================================================================
* Filename:mystack.cpp
* Author: KCN_yu
* Createtime:Mon 30 Nov 2020 06:16:40 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX 256

class node{
public:
    int elem;
    node* next;
    node(){ next = nullptr; }
    node(int e){ elem = e; next = nullptr; }
};
class mystack{
private:
    int dim;
    int cnts;
    node* head;
public:
    mystack(int n = MAX){ dim = n; cnts = 0; head = nullptr;}
    void push(int e);
    void pop();
    int top();
    bool full() { return cnts == dim; }
    bool empty() { return cnts == 0; }
    void print();
};
void mystack::push(int e){
    if(cnts >= dim){
        cout << "error! full!" << endl;
        return;
    }
    if(head == nullptr){
        head = new node(e);
    }
    else{
        node* tmp = new node(e);
        tmp->next = head;
        head = tmp;
    }
    cnts++;
}
void mystack::pop(){
    if(head != nullptr){
        node* tmp = head;
        head = head->next;
        delete tmp;
        cnts--;
    }
}
int mystack::top(){
    if(head != nullptr)
        return head->elem;
}
void mystack::print(){
    if(head != nullptr && head->next == nullptr){
        cout << head->elem << endl;
        return;
    }
    node* tmp = head;
    while(tmp != nullptr){
        cout << tmp->elem << endl;
        tmp = tmp->next;
    }
}
int main(int argc, char *argv[])
{
    mystack st;
    cout << st.empty() << endl;
    cout << st.full() << endl;
    st.push(100);
    cout << st.top() << endl;
    st.push(10);
    cout << st.top() << endl;
    st.push(1);
    cout << st.top() << endl;
    st.print();
    cout << endl;
    st.pop();
    cout << st.top() << endl;
    st.print();
    st.pop();
    st.pop();
    st.pop();
    cout << st.empty() << endl;
    return 0;
}

