#ifndef HASHHEAP_H
#define HASHHEAP_H 
#include <string>
#include <vector>
#include <list>
/**
  * @author Xianghong Sun
  *
  */

class EmptyHeapException {};

class HashHeap {
public:
	HashHeap(int=11);
	bool insert(int);
	bool lookup(int);
	int deleteMin() throw(EmptyHeapException);
	bool deleteI(int);
	int hashSize();
	void print();
private:
	std::vector<int> * heap;
	std::vector<std::list<int> *> * hashTable;
	
};

#endif
