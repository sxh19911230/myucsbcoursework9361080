GTEST_DIR = ~cs32/gtest-1.7.0

CC = g++
CFLAGS = -c -I. -isystem $(GTEST_DIR)/include/ -std=c++0x
LDFLAGS = -pthread $(GTEST_DIR)/libgtest.a

EX1 = bigint_test
EX2 = bigsort
EX3 = bigdivint_test

.PHONY:	default sort div all clean

default: $(EX1)

sort: $(EX2)

div: $(EX3)

all: $(EX1) $(EX2) $(EX3)

$(EX1): bigint*.o test/bigint_test.o
	$(CC) bigint*.o test/bigint_test.o -o $@ $(LDFLAGS) 

$(EX2): bigsort.o bigint*.o 
	$(CC) bigsort.o bigint*.o -o $@ 

$(EX3): bigdiv*.o bigint*.o test/bigdivint_test.o
	$(CC) bigdiv*.o bigint*.o test/bigdivint_test.o -o $@ $(LDFLAGS)

bigint*.o: bigint*.cpp
	$(CC) $(CFLAGS) bigint*.cpp

bigsort.o: bigsort.cpp
	$(CC) $(CFLAGS) bigsort.cpp

bigdiv*.o: bigdiv*.cpp
	$(CC) $(CFLAGS) bigdiv*.cpp

test/bigint_test.o: test/bigint_test.cpp
	$(CC) $(CFLAGS) test/bigint_test.cpp -o $@

test/bigdivint_test.o: test/bigdivint_test.cpp
	$(CC) $(CFLAGS) test/bigdivint_test.cpp -o $@

clean:
	rm -f $(EX1) $(EX2) $(EX3) *.o test/*.o
