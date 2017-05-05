#include <iostream>



class test {
public:
	test() {}
	test(test& tmp){
		std::cout << "copy ctor" << std::endl;
	}

	test func() {
		std::cout << "In func(): ";
		test tmp;
		return tmp;
	}

	test func2() {
		std::cout << "In func2(): ";
		return *this;
	}

};


int main() {
	test a;
	a = a.func();
	a = a.func2();
	return 0;
}
