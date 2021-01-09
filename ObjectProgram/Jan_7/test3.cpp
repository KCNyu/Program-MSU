/*================================================================
 * Filename:test3.cpp
 * Author: KCN_yu
 * Createtime:Tue 05 Jan 2021 12:42:20 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

using namespace std;
class Fly {
    string text;

    public:
    Fly() { text = "Лукоморье все же есть!"; }
    Fly(string t) : text(t) {}
    void said() { cout << text << endl; }
};
class Baba_Yaga : public Fly {
    public:
        Baba_Yaga() {}
        Baba_Yaga(string t) : Fly(t) {}
};
class Covernyi_Samolet : public Fly {
    public:
        Covernyi_Samolet(string t) : Fly(t) {}
        ~Covernyi_Samolet() { cout << "Вот!" << endl; }
};
struct Propp;
void fairy_tail(Propp &x, int n);
struct Propp {
    Propp() {
        Baba_Yaga("Избушка, избушка! ").said();
        fairy_tail(*this, -1);
        Fly("на курьих ножках").said();
    }

    void magic() {
        cout << "В заповедных и дремучих, \n"
            "Страшных Муромских лесах"
            << endl;
        if (sizeof(*this) > 5)
            throw Fly("Там ступа с Бабою-Ягой");
        throw Baba_Yaga("Идет, бредет сама собой...");
    }

    Propp(int i) {
        cout << "-Колобок, колобок! Я тебя съем!" << endl;
        cout << "-А я не простой колобок, "
            " а тот, который рот лисе платком завяжет,"
            " прежде чем песенку петь."
            << endl;
        throw Fly("колобок" + (i >= 0 ? i : -i) % 7);
        magic();
    }

    Propp(Propp &x) {
        Fly("Ловко пользуется, тать ").said();
        Baba_Yaga("Тем, что может он летать... ").said();
    }
};
struct Morph : Propp {
    Morph() {
        try {
            Baba_Yaga("Пой частушки, бабка-ежка...").said();
            fairy_tail(*this, 1);
            Covernyi_Samolet(" В далеком созвездии Тау Кита \n"
                    " Все стало для нас непонятно, - \n"
                    " Сигнал посылаем: \"Вы что это там?\" - \n"
                    " А нас посылают обратно.")
                .said();
            if (sizeof(*this) > 10)
                throw Fly();
            Baba_Yaga("И послала к лешему...").said();
        } catch (Fly &f) {
            f.said();
            throw;
            faible();
        }
    }
    Morph(Morph &) { Baba_Yaga("Против!!!").said(); }
    void faible() {
        cout << "... Он прогнал министров с кресел," << endl;
        cout << "Оппозицию повесил -" << endl;
        cout << "И скучал от тоски по делам." << endl;
    }
};
void fairy_tail(Propp &x, int n) {
    try {
        Baba_Yaga("повернись к лесу задом...").said();
        if (n < 0)
            throw Baba_Yaga("Фу-фу, русским духом пахнет... ");
        Baba_Yaga("костяная нога...").said();
        if (n > 0)
            throw Fly("А коверный самолет...");
        Baba_Yaga("Я печку истоплю, \n Ведь мальчиков и девочек ...").said();
    } catch (Baba_Yaga &a) {
        a.said();
        fairy_tail(x, 1);
        Covernyi_Samolet(" Слал им кажную субботу \n"
                " Обскорбительную ноту, - \n"
                " Шел на международный скандал.")
            .said();
        throw;
    } catch (Fly &f) {
        f.said();
        throw;
    }
}
int main() {
    Baba_Yaga("Я фольклорный элемент, у мене есть документ...").said();
    try {
        Morph a;
        throw Baba_Yaga("Я вобче могу отседа улететь в любой момент...");
    } catch (...) {
        Covernyi_Samolet("Сдан в музей в запрошлый год.").said();
        Baba_Yaga().said();
        return 0;
    }
    return 0;
}
