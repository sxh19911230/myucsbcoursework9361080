#include <iostream>
using namespace std;

int main() {

	int a, b, c;
	int tmp;
	
	cout << "3 number";

	cin >> a >> b >> c;
	

	if (b < c) goto bltc;

	if (a < c) goto finish;
	
	tmp = a;
	a = c;
	c = tmp;

	goto finish;

bltc:
	if (a < b) goto finish;
	
	tmp = a;
	a = b;
	b = tmp;
	
finish:

	if (b < c) goto result;

	tmp = b;
	b = c;
	c = tmp;

result:
	cout << a << b << c;
	return 0;
}