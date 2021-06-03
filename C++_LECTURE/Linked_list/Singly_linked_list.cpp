/*************************************************************************
	> File Name: Singly_linked_list.cpp
	> Author:
	> Mail:
	> Created Time: Wed 20 Nov 2019 01:13:18 PM CST
 ************************************************************************/

#include<iostream>
#include <stdlib.h>
using namespace std;

class Node {
public:
	int data;
	Node *pNext;
};
class Linked_list {
public:
	Linked_list() {
		head = new Node;
		head->data = 0;
		head->pNext = NULL;
	}
	void Create_linked_list(int n);
	void Insert_node(int position, int d);
	void Traverse_linked_list();
	void Delete_node(int position);
	void Delete_linked_list();
private:
	Node *head;
};

void Linked_list::Create_linked_list(int n) {
    Node *pnew, *ptemp;
    ptemp = head;
    int i = 0;
    while(++i <= n) {
        pnew = new Node;
        cout << "Input the node_" << i << ": ";
        cin >> pnew->data;
        pnew->pNext = NULL;
        ptemp->pNext = pnew;
        ptemp = pnew;
    }
}

void Linked_list::Insert_node(int position, int d) {
    Node *pnew, *ptemp;
    ptemp = head;
    pnew = new Node;
    pnew->data = d;
    pnew->pNext = NULL;

    while(position-- > 1)
        ptemp = ptemp->pNext;
    pnew->pNext = ptemp->pNext;
    ptemp->pNext = pnew;
}

void Linked_list::Traverse_linked_list() {
    cout << "The numberical value of node is: ";
    Node *p = head->pNext;
	while(p != NULL) {
	    cout << p->data << " ";
	    p = p->pNext;
	}
	cout << endl;
}

void Linked_list::Delete_node(int position) {
    Node *ptemp = head, *pdelete;
    while(position-- > 1)
        ptemp = ptemp->pNext;
    pdelete = ptemp->pNext;
    ptemp->pNext = pdelete->pNext;
    delete pdelete;
    pdelete = NULL;
}

void Linked_list::Delete_linked_list() {
	Node *pdelete = head->pNext, *ptemp;
	while(pdelete != NULL) {
	    ptemp = pdelete->pNext;
	    head->pNext = ptemp;
	    delete pdelete;
	    pdelete = ptemp;
	}
}

int main() {
	Linked_list l;
	int position = 0, value = 0, n = 0;

	cout << "Input the number of node：";
	cin >> n;
	l.Create_linked_list(n);
	l.Traverse_linked_list();

    cout << "Input the position of Delete_node: ";
	cin >> position;
	l.Delete_node(position);
	l.Traverse_linked_list();

    cout << "Input the position of Insert_node and numberical value: ";
	cin >> position >> value;
	l.Insert_node(position, value);
	l.Traverse_linked_list();

	l.Delete_linked_list();
    cout << "Delete linked list successfully!" << endl;
 	return 0;
}
