#include <iostream>

using namespace std;

int main() {
	cout << 19 * 19 % 41 % 9 << endl;
	cout << (32 * 32 *32 % 13) * (32 * 32 * 32 % 13) % 11 << endl;
	cout << (7 * 7 * 7 % 23) * (7 * 7 * 7 % 23) % 31 << endl;
	cout << (21 * 21 % 15) *(21 * 21 % 15) * (21 * 21 % 15) % 22 << endl;


	return 0;
}
