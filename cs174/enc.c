#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include "paillier.h"

int main (int arg, char ** args) {
	paillier_pubkey_t * pub;
	paillier_prvkey_t * prv;
	
	paillier_ciphertext_t *c;
    paillier_plaintext_t *p;

	char buff[100];
	void * tmp;
	
	if (arg != 3) {
		printf("Usage: %s <plain text> <destiny file>\n", args[0]);
		exit(0);
	}

	p = paillier_plaintext_from_ui(atoi(args[1]));
	
	
	FILE *pFile;
	pFile=fopen("pubkey", "r");
	if (!pFile)  {
		printf ("Need public Key!\n");
		exit(1);
	}
	fgets (buff , 100 , pFile);
	fclose (pFile);
	
	pub = paillier_pubkey_from_hex(buff);
	
	c = paillier_enc(NULL, pub, p, paillier_get_rand_devurandom);
	tmp = paillier_ciphertext_to_bytes(16,c);
	
	pFile = fopen(args[2], "w");
	if (!pFile)  {
		printf ("Fail to open %s\n", args[2]);
		exit(1);
	}
	
	fwrite(tmp, 1, 16, pFile);
	fclose(pFile);
	return 0;
}
