#include "stdio.h"
#include "stdlib.h"

int multiplyBy4(int v)
{
	// TODO: multiply the number by 4
	v <<= 2;
	return v;
}

int setBit7to1(int v)
{
	// TODO: set bit 7 to 1
	v = v | 0x0080;
	return v;
}

int setBit5to0(int v)
{
	// TODO: set bit 5 to 0
	v = v & 0xFFDF;
	return v;
}
	
int flipBit3(int v)
{
	// TODO: flip bit 3 (if it is 0, make it 1.  If 0, make 1)
	v = v ^ 0x0008;	
	return v;
}
	
int ifBit4is0(int v)
{
	// TODO: check to see if bit 4 is a 0 - return 1 if true, 0 if false)
	v = ((v >> 4) & 0x0001) ^ 0x0001;	
	return v;
}

int ifBit7is1(int v)
{
	// check to see if bit 7 is a 1 - return 1 if true, 0 if false
	v = (v >> 7) & 0x0001;
	return v;
}

int unsignedBits0through3(int v)
{
	// return the unsigned value in bits 0 through 3
	v = v & 0x000F;
	return v;
}

int unsignedBits4through9(int v)
{
	// return the unsigned value in bits 4 through 9
	v = (v & 0x03F0) >> 4;
	return v;
}

int signedBits0through3(int v)
{
	// return the signed value in bits 0 through 4
	int w = (v & 0x0008) >> 3;
	w = w | w << 1;
	w = w | w << 2;
	w = w | w << 4;
        w = w | w << 8;
	w = w | w << 16;
	w = w & 0xFFFFFFF0;
	v = (v & 0x0F) | w;
	return v;
}

int signedBits4through9(int v)
{
	// return the signed value in bits 4 through 9
	int w = (v & 0x0200) >> 9;
        w = w | w << 1;
        w = w | w << 2;
        w = w | w << 4;
        w = w | w << 8;
        w = w | w << 16; 
	w = w & 0xFFFFFFC0;
	v = ((v >> 4) & 0x3F) | w;
	return v;
}

int setBits2through7(int v, int setValue)
{
	// set bits 2 through 7 in v to become setValue
	v = (v & 0xFF03) | (setValue << 2);
	return v;
}




