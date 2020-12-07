/*================================================================
* Filename:K.1.14.b.cpp
* Author: KCN_yu
* Createtime:Sun 06 Dec 2020 06:40:05 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class tiger
{
private:
    string name;
    string color;
    int weight;
public:
    static int count;
    tiger(string s = "null"){ name = s; color = "null"; weight = 0; count++;}
    ~tiger() { count--; }
    tiger& setname(string s){ name = s; return *this; }
    tiger& setcolor(string c){ color = c; return *this; }
    tiger& setweight(int w){ weight = w; return *this; }
    void print(){
        cout << "name: " << name << endl
        << "color: " << color << endl
        << "weight: " << weight << endl << endl;
    }
    int getweight(){ return weight; }
};
int tiger:: count = 0;

bool myless(tiger& t1, tiger& t2){ return t1.getweight() <= t2.getweight(); }
int main(int argc, char *argv[])
{
    tiger T1,T2("Kuzya");
    T1.setname("Murzik").setcolor("light").setweight(200);
    //задаем параметры тигра
    T1.print(); //печать информации о тиграх
    T2.print();
    T2.setname("Tigr");
    if (myless(T2,T1)) T2.print();
    //печать информации о том тигре, который по размеру меньше
    else T1.print();
    //печатаем количество объектов-тигров
    cout<<tiger::count<<endl;
    return 0;
}

