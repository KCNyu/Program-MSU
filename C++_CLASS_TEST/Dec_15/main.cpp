#include <iostream>
#include "list.h"
using namespace std;

int main() {
	List l1,l2('a'), l3("abcabcabaa"), l4(l1), l5(l3);
	cout<<l1<<' '<<l2<<' '<<l3<<' '<<l4<<' '<<l5<<endl;
	cout<<(l1=l4)<<' '<<(l3)<<' '<<(l4=l3)<<endl;
    cout << l3 - 'a' << endl;
    cout << l3 + 'a' << endl;
    cout << 'z'+ l3 << endl;
    cout << l3 - 'a' << endl;
    cout << 'x'+ l3 << endl;
    cout << 'a'- l3 << endl;
	return 0;

}
