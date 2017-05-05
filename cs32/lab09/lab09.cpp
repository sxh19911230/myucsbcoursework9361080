// lab09.cpp - variation of C program, p. 169 of CS 32 Reader

#include<iostream>
using namespace std;

int a[10] = {0,1,2,3,4,5,6,7,8,9};
int b[10];
const int M = 0;

int main() {
    static int k = 3;
    
    for (int i = 0; i < 10; i++) {
	cout << "element " << a[i];
	b[i] = k * a[i];
	cout << " is " << b[i] << endl;
    }
    return M;
}
