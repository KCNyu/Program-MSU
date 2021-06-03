/*================================================================
 * Filename:temp.cpp
 * Author: KCN_yu
 * Createtime:Thu 24 Dec 2020 02:17:40 AM CST
 ================================================================*/

#include <iostream>
#include <string>
using namespace std;

class Man {
    int age;
    string name;
    protected:
    void print_info()const{
        cout << "Меня зовут " << name << ". Мне " << age <<". ";
    }
    public:
    Man (int age, string name){
        this->age=age;
        this->name=name;
    }
    virtual ~Man(){} // объявляем деструктор виртуальным, так что деструкторы производных
    // классов будут тоже виртуальными, и при уничтожении объекта производного класса
    // через указатель на базовый класс (Man) будет вызван "правильный" деструктор,
    // соответствующий динамическому типу объекта.
    virtual void print()const =0; // объявляем метод print() чистым виртуальным, тем самым класс
    // Man становится абстрактным классом (нельзя создать объект типа Man)
};
class Male : Man {
    public:
        Male(int age=29, string name = "Коля"): Man(age,name){};
        ~Male(){} // Определяем деструктор, он виртуальный ,
        // т.к. в базовом классе деструктор объявлен как виртуальный.
        // Можно было не определять деструктор с пустым телом --
        // он и так сгенерируется автоматически (и будет виртуальным).
        // Деструкторы (как и конструкторы) не наследуются, и , если явно не
        // определяются пользователем, то генерируются автоматически.

        void print()const { // Определяем виртуальный метод print() для класса Male:
            print_info(); // Имя и возраст
            cout<<"Я мужчина. "; // Пол
            // Поскольку базовый класс Man был сделан абстрактным за счет
            // чистого виртуального метода print(),
            // то этот метод необходимо переопределить в Male,
            // иначе Male тоже будет абстрактным классом (т.е. объект типа Male
            // невозможно будет создать).
        }
};
class Female : Man {
    public:
        Female(int age=29, string name = "Оля"): Man(age,name){}
        // (виртульный) деструктор ~Female(){} сгенерируется автоматически
        virtual void print()const { // Определяем виртуальный метод print() для класса Female
            print_info(); // Имя и возраст
            cout<<"Я женщина. "; // Пол
        }
};
class Playboy: Male {
    public:
        Playboy (int age=19, string name = "Саша"): Male(age,name){}
        //(виртуальный) деструктор ~Playboy(){} сгенерируется автоматически
        virtual void print()const { // Определяем print() для мужчин "особого" сорта:
            Male::print(); // сначала вызываем print() из базового класса -- она печатает
            // общие сведения о мужчине;
            cout<<"Я люблю пиво. "; // сообщаем дополнительную информацию о себе.
        }
};
class Cover_girl: Female {
    public:
        Cover_girl (int age=19, string name = "Даша"): Female(age,name){}
        //~Cover_girl(){};
        virtual void print()const { Female::print(); cout<<"Я люблю украшения. ";}
};
class Sportsman: Male {
    public:
        Sportsman (int age=19, string name = "Дима"): Male(age,name){}
        //~Sportsmam(){};
        virtual void print()const {Male::print(); cout<<"Я люблю спорт. ";}
};
class Clever_girl: Female {
    public:
        Clever_girl (int age=19, string name = "Нина"): Female(age,name){}
        //~Clever_girl(){};
        virtual void print()const {Female::print(); cout<<"Я люблю читать научные труды. ";}
};
void People(Man *p[], int n){
    for (int i=0; i<n;i++){
        cout<<"Person #" <<i+1<<":"<<endl;
        p[i]->print(); cout<<endl;
    }
}
int main (){
    Clever_girl c(18); Female f;
    Sportsman s = Sportsman(25); Playboy p;
    Male m(45,"Миша"); Cover_girl cg(25,"Кристина");
    Man * arr[] = {(Man *)&c,(Man *) &f, (Man *)&s,(Man *)&p, (Man *)&m, (Man *)&cg};
    People(arr,sizeof(arr)/sizeof(Man*));
}
