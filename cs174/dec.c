#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "paillier.h"

int main (int arg, char ** args) {
	paillier_pubkey_t * pub;
	paillier_prvkey_t * prv;
	
	paillier_ciphertext_t *c;
    paillier_plaintext_t *p;

	char buff[100];
	int i;
	if (arg != 2) {
		printf("Usage: %s <binary file>\n", args[0]);
		exit(0);
	}

//	c = paillier_ciphertext_from_bytes(args[1],32);
	
	
	FILE *pFile;
	pFile=fopen("pubkey", "r");
	if (!pFile)  {
		perror ("Need public Key!\n");
		exit(1);
	}
	fgets (buff , 100 , pFile);
	fclose (pFile);
	
	pub = paillier_pubkey_from_hex(buff);
	
	
	pFile=fopen("prvkey", "r");
	if (!pFile)  {
		perror ("Need private Key!\n");
		exit(1);
	}
	fgets (buff , 100 , pFile);
	fclose (pFile);
	
	prv = paillier_prvkey_from_hex(buff, pub);
	
	pFile=fopen(args[1], "r");
	if (!pFile)  {
		perror ("Fail to open file\n");
		exit(1);
	}
	fread (buff , 1,16 , pFile);
	fclose (pFile);
	
	c = paillier_ciphertext_from_bytes(buff,16);
	
	p = paillier_dec(NULL, pub, prv, c);
	mpz_out_str(stdout,10, p->m);
	return 0;
}
