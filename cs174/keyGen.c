#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include "paillier.h"

int main () {
	paillier_pubkey_t * pub;
	paillier_prvkey_t * prv;
	paillier_keygen(64, &pub, &prv, paillier_get_rand_devurandom);
	char * pubkey = paillier_pubkey_to_hex(pub);
	char * prvkey = paillier_prvkey_to_hex(prv);
	
	printf("pub: %s\nprv: %s\n", pubkey, prvkey);

	FILE *pFile;
	pFile=fopen("pubkey", "w");
	fwrite (pubkey , sizeof(char), strlen(pubkey), pFile);
	fclose (pFile);
	pFile=fopen("prvkey", "w");
	fwrite (prvkey , sizeof(char), strlen(prvkey), pFile);
	fclose (pFile);
	return 0;
}
