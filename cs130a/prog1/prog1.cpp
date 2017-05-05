#include <iostream>
#include "HashHeap.h"

using namespace std;

int main() {
	HashHeap *a;
	int in;
	cin >> in;
	a = new HashHeap(in);
	cout << "read hash size " << a->hashSize() << endl;
	do {
		cin >> in;
		switch (in) {
		case 0:
			cin.get();
			cin >> in;
			if (a->insert(in)) cout << "insert " << in << endl;
			else cout << "error_already_present " << in << endl;
			
			break;
		case 1:
			cin.get();
			cin >> in;
			if (a->lookup(in)) cout << "find " << in << endl;
			else cout << "not_find " << in << endl;
			break;
		case 2:
			try{
				int i = a->deleteMin();
				cout << "deleteMin " << i << endl;
			} catch (EmptyHeapException e) {
				cout << "error_structure_is_empty" << endl;
			}
			break;
		case 3:
			cin.get();
			cin >> in;
			if (a->deleteI(in)) cout << "delete " << in << endl;
			else cout << "error_not_find " << in << endl;
			break;
		case 4:
			try{
				cout <<"print ";
				a->print();
                        } catch (EmptyHeapException e) {
                                cout << "error_structure_is_empty" << endl;
                        }

			break;
		default:
			cout << "error_no_operation" << endl;
			cin.clear();
			cin.ignore(256,'\n');
		}
	} while (!cin.eof());
	



	return 0;
}


