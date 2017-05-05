// bigsort.cpp
// YOUR NAME(S) AND DATE

#include <iostream>
#include <string>
#include <chrono>
#include "bigint.h"
using namespace std;
int partition(BigInt *list[], int first, int last);
void swap(BigInt *list[], int first, int second);
void recQuickSort(BigInt *list[], int first, int last);
void print(BigInt *aptrs[], int n);

void sort(BigInt *aptrs[], int n) {
    // IMPLEMENT - okay to add helper functions
	recQuickSort(aptrs, 0, n - 1);
}

#define MAX 20000
int main(int argc, char *argv[]) {

	bool justtimer = false;
	chrono::steady_clock::time_point start, end;
	if (argc > 1) {
		if (argv[1][0] == '-' && argv[1][1] == 't')
			justtimer = true;
		else {
			cerr << "bad option: " << argv[1] << endl;
			return 1;
		}
	}

	BigInt *p[MAX];
	string s;
	int n = 0;
	while (getline(cin, s)) {
		try {
			p[n] = new BigInt(s);
		}
		catch (BigException e) {
			cerr << "bad data: " << s << " at line " << n << endl;
			return 1;
		}
		++n;
	}

	if (justtimer)
		start = chrono::steady_clock::now();

	sort(p, n);

	if (justtimer) {
		end = chrono::steady_clock::now();
		cout << "sort time for " << n << " BigInts: "
			<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
			<< " milliseconds" << endl;
	}
	else
		for (int i = 0; i<n; i++)
			cout << *p[i] << endl;

	return 0;
}


int partition(BigInt *list[], int first, int last)
{
	BigInt* pivot;
	int index, smallIndex;
	
	swap(list, first, (first + last) / 2);

	pivot = list[first];
	smallIndex = first;
	for (index = first + 1; index <= last; index++) {
		if (*list[index] < *pivot)
		{
			smallIndex++;
			swap(list, smallIndex, index);
		}
	}
	swap(list, first, smallIndex);
	return smallIndex;
}


void swap(BigInt *list[], int first, int second)
{
	BigInt *temp;
	if (first != second) {
		temp = list[first];
		list[first] = list[second];
		list[second] = temp;
	}
}

void recQuickSort(BigInt *list[], int first, int last)
{

	int pivotLocation;
	if (first < last)
	{
		pivotLocation = partition(list, first, last);

		recQuickSort(list, first, pivotLocation - 1);
		recQuickSort(list, pivotLocation + 1, last);
	}
}

void print(BigInt *aptrs[], int n) {
	for (int i = 0; i < n; i++)
		cout << *aptrs[i] << '\t';
}
