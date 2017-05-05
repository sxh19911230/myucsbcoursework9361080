/* padding.cpp
   Shows an effect of data in a struct being padded to word boundaries
   cmc, updated to class from struct 5/24/2013 */

#include <iostream>
using namespace std;

class CIC {
    char c1;
    int i;
    char c2;
} cic;

class CCI {
    char c1;
    char c2;
    int i;
} cci;

int main() {
    cout << "sizeof cic: " << sizeof cic << endl;
    cout << "sizeof cci: " << sizeof cci << endl;
    return 0;
}
