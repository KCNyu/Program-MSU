#include <iostream>
#define MAXLENTH 20
using namespace std;

int main() {
	const int len = MAXLENTH;
	long num[len + 1] = { 1 };

	for (int i = 1; i <= len; ++i)
		for (int j = i; j <= len; ++j)
			num[j] += num[j - i];

	for (int i = 0; i <= len; i++)
		cout << i << " " << num[i] << endl;
	return 0;
}
