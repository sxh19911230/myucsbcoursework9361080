#include <iostream>
#include "sum.h"

int main(int argc, const char *argv[]) {
	int numbers[5];
	std::cout << "Enter 5 integers:";
	for (int i = 0; i < 5; i++)
		std::cin >> numbers[i];
	int total = sum(numbers, 5);
	std::cout << "The summation = " << total << std::endl;
}
