#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include "HashHeap.h"

using namespace std;

//Help fuctions decration
void percolateDown(vector<int> *, int);
void percolateDown(vector<int> *);

void percolateUp(vector<int> *, int);
void percolateUp(vector<int> *);

void swap(vector<int> *, int, int);

int findNextPrime(int); //less than 15,485,863


//class implement
HashHeap::HashHeap(int hashKey) {
	if (hashKey <= 0) hashKey = 101;
	hashTable = new vector<list<int>*>(findNextPrime(hashKey));
	//Ignore the first node for heap
	heap = new vector<int>();
	heap->push_back(0);

}

bool HashHeap::insert(int num) {
	//hash insert
	int index = num % hashTable->size();
        if ((*hashTable)[index] == NULL) (*hashTable)[index] = new list<int>;
	else if (lookup(num)) return false;

	(*hashTable)[index]->push_back(num);

	//heap insert
	heap->push_back(num);
	percolateUp(heap);
	return true;
}

bool HashHeap::lookup(int num) {
	int index = num % hashTable->size();
        if ((*hashTable)[index] == NULL) return false;
	
	for (list<int>::iterator it=(*hashTable)[index]->begin();
		it != (*hashTable)[index]->end(); it++)
			if (*it == num) return true;
	
	return false;
}

int HashHeap::deleteMin() throw(EmptyHeapException) {

	//Because I don't delete element in heap when calling deleteI
	//Some element should be deleted still in heap
	//So, I check it before return the min
	
	//declare min
	int min;
	do {
		//nothing in it
		if (heap->size() == 1) throw EmptyHeapException();
	
		//find min
		min = (*heap)[1];
		//delete from heap
		swap(heap, 1, heap->size() - 1); 
		heap->pop_back();
		percolateDown(heap);
	} while (!lookup(min));
	//delete from hashTable
	int index = min % hashTable->size();

        for (list<int>::iterator it=(*hashTable)[index]->begin();
                it != (*hashTable)[index]->end(); it++)
			if (*it == min) {
				(*hashTable)[index]->erase(it);
				break;
			}

	return min;
}

bool HashHeap::deleteI(int num) {
	//return false if num doesn't exist
	if (!lookup(num)) return false;
	//delete from hash table
	int index = num % hashTable->size();

        for (list<int>::iterator it=(*hashTable)[index]->begin();
                it != (*hashTable)[index]->end(); it++)
                        if (*it == num) {
                                (*hashTable)[index]->erase(it);
                                break;
                        }
	//No deletion from heap becuase it costs linear time

	return true;
}

void HashHeap::print() {
	//Assign heap's address to another and copy back
	vector<int> * cpheap = heap;
	heap = new vector<int>();
        heap->push_back(0);

	//Because I don't delete things in heap in fuction DeleteI
	//I need check if the number won't print twice
	int lastOne;
	//If nothing is printed in the first while loop, throw exception
	bool nothing = true;
	//print Min for cpheap
	//no comma for first one
	while (cpheap->size() > 1) {
		swap(cpheap, 1, cpheap->size() - 1);
                if (lookup(cpheap->back())) {
			lastOne = cpheap->back();
                        cout << cpheap->back();
			heap->push_back(lastOne);
			//percolateUp(heap);
			cpheap->pop_back();
	                percolateDown(cpheap);
			nothing = false;
			break;
		}
                cpheap->pop_back();
                percolateDown(cpheap);
	}

	//Nothing
	if (nothing) throw EmptyHeapException();


	//comma for the rest
	while (cpheap->size() > 1) {
        	swap(cpheap, 1, cpheap->size() - 1);
		if (lookup(cpheap->back()) && lastOne != cpheap->back()) { 
			lastOne = cpheap->back();
			heap->push_back(lastOne);
			//percolateUp(heap);
			cout << ',' << cpheap->back();
		}
        	cpheap->pop_back();
		percolateDown(cpheap);
	}
	cout << endl;
	delete cpheap;
}

int HashHeap::hashSize() {
	return hashTable->size();
}

//Help Functions:
void percolateDown(vector<int> * heap, int pos) {
	while (1) {
		//no more left and right node
		if (heap->size() <= pos * 2) break;

		//has only left node, no right node
		if (heap->size() == pos * 2 + 1) {
			if ((*heap)[pos] > (*heap)[pos * 2]) 
				swap(heap,pos,pos * 2);
			break;
		}
		
		//has both left and right nodes
		//left <= right and left < self, percolate down
		if ((*heap)[pos * 2] <= (*heap)[pos * 2 + 1] 
			&& (*heap)[pos * 2] < (*heap)[pos])
		{
			swap(heap, pos, pos * 2);
			pos = pos * 2;
		}
		//right < left and right < self, percolate down
		else if ((*heap)[pos * 2 + 1] < (*heap)[pos * 2] 
                        && (*heap)[pos * 2 + 1] < (*heap)[pos])
		{
			swap(heap, pos, pos * 2 + 1);
                        pos = pos * 2 + 1;
		}
		//self is min
		else break;
	}
}

void percolateDown(vector<int> * heap) {
	percolateDown(heap, 1);
}

void percolateUp(vector<int> * heap, int pos) {
	while (pos > 1) {
		//self lager than parent
		if ((*heap)[pos] > (*heap)[pos / 2]) break;
		//self smaller than parent
		swap(heap, pos, pos / 2);
		pos = pos / 2;
	}
}

void percolateUp(vector<int> * heap) {
	percolateUp(heap, heap->size() - 1);
}

void swap(vector<int> * heap, int pos1, int pos2) {
	int tmp = (*heap)[pos1];
	(*heap)[pos1] = (*heap)[pos2];
        (*heap)[pos2] = tmp;
}

int findNextPrime(int num) {
	string fileName;
	if (num <= 49999) fileName = "primes.txt";
	else return num;

	ifstream primeFile(fileName.c_str());
	
	int nextNum;
	if (primeFile.is_open()) {
		//ignore the first line
		getline(primeFile, fileName);
		
		while (!primeFile.eof()) {
			primeFile >> nextNum;
			if (nextNum >= num) {
				primeFile.close();
				return nextNum;
			}
		}
		primeFile.close();
	}
	return num;
}


