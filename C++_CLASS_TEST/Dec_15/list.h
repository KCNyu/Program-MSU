# include<iostream>
using namespace std;
class List {
  struct Node {
      char elem;
      Node* next;
      Node (char elem='_', Node* next=NULL) {
			this->elem=elem;
			this->next=next;
      }
  };
  Node* lst;
  void clear();
public:

    List ();

    List (char c);

    List (const char* s);


    bool empty() const ;

    List (const List& l);

    ~List();


    List operator+ (const List& l);
    List operator- (const char c);


    friend List operator+ (const char c, const List& l);
    friend List operator- (const char c, const List& l);

    friend ostream& operator<< (ostream& s, const List& l);


    List& operator= (const List& l);
};
