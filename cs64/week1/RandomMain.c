#include "stdio.h"
#include "stdlib.h"
#include "RandomCode.h"
int main(int argc, char *argv[])
{
	char buf[256];
	int value;
	int result1;
	unsigned int result2;
	FILE *file;
	if (argc != 2)
	{
		printf("Proper usage: a.out filename.txt");
		printf("You need to create a file, and that file contains\n");
		printf("a list of numbers, with each number on a different line.\n");
		printf("This program will run all of the tests on each number.\n");
		exit(1);
	}

	file = fopen(argv[1],"r");
	if (file == NULL)
	{
		printf("Could not open file %s\n",argv[1]);
		exit(2);
	}

	// read in each line, convert to number, then do bitwise stuff
	fgets(buf,256,file);
	while (!feof(file))
	{
		// convert the number from a character string to integer
		value = atoi(buf);

		// print the number out as an integer and hex number
		printf("The original number: int: %d, hex: %x\n",value,value);
		printf("Every operation is independent\n");

		// TODO: multiply the number by 8
		result1 = multiplyBy4(value);
		printf("%d*4 = %d\n",value,result1);

		// TODO: set bit 7 to 1
		result1 = setBit7to1(value);
		printf("set bit 7 to 1: %d\n",result1);

		// TODO: set bit 5 to 0
		result1 = setBit5to0(value);
		printf("set bit 5 to 0: %d\n",result1);
		
		// TODO: flip bit 3 (if it is 0, make it 1.  If 0, make 1)
		result1 = flipBit3(value);
		printf("flip bit 3: %d\n",result1);
		
		// check to see if bit 4 is a 0
		result1 = ifBit4is0(value);
		if (result1) // TODO: if bit 3 is a 0
			printf("bit 4 is 0\n");
		else
			printf("bit 4 is 1\n");

		// check to see if bit 7 is a 1
		result1 = ifBit7is1(value);
		if (result1) // TODO: if bit 7 is a 1
			printf("bit 7 is 1\n");
		else
			printf("bit 7 is 0\n");

		// Now imagine that the number actually contains several
		// smaller unsigned integers smashed together into 32 bits.
		// The format is:  The lowest 4 bits are one number, and 
		// the next 6 bits are another number.

		// TODO: extract the number contained in only the lowest 4 bits
		result1 = unsignedBits0through3(value);
		printf("lowest 4 bits: %d\n",result1);

		// TODO: extract the number contained in only the next 6 bits
		result1 = unsignedBits4through9(value);
		printf("next 4 bits: %d\n",result1);

		// Now imagine that the number actually contains several
		// smaller *signed* integers smashed together into 32 bits.
		// The format is:  The lowest 4 bits are one number, and 
		// the next 6 bits are another number.

		// TODO: extract the signed number in the lowest 4 bits
		result1 = signedBits0through3(value);
		printf("lowest 4 bits: %d\n",result1);

		// TODO: extract the signed number in the next 6 bits
		result1 = signedBits4through9(value);
		printf("next 6 bits: %d\n",result1);

		// TODO: set bits 2-7 (inclusive) to contain the number 7.
		result1 = setBits2through7(value,7);
		printf("next 5 bits: %d\n",result1);

		fgets(buf,256,file);
	}

		
}

