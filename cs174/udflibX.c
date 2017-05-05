#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long long ulonglong;
typedef long long longlong;

#include <mysql.h>
#include <ctype.h>
#include <gmp.h>
#include "paillier.h"
static pthread_mutex_t LOCK_hostname;


my_bool SUM_HE_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
void SUM_HE_clear(UDF_INIT *initid, char *is_null, char *error);
void SUM_HE_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
char *SUM_HE(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void SUM_HE_deinit(UDF_INIT *initid);
paillier_pubkey_t * pub;


my_bool SUM_HE_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
	initid->maybe_null = 0;
	initid->max_length = 20;
	pub = paillier_pubkey_from_hex("845febaf4fabd2db");
	

	if (args->arg_count != 1) {
		strcpy(message,"SUM_HE() requires two arguments");
		return 1;
	}
	
	if (args->arg_type[0] != STRING_RESULT)
	{
		strcpy(message,"SUM_HE() requires a string");
		return 1;
	}

	return 0;
	
}

void SUM_HE_clear(UDF_INIT *initid, char *is_null, char *error) {
	
	free((paillier_ciphertext_t *)initid->ptr);
	initid->ptr = NULL;
	
}

void SUM_HE_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error){
	paillier_ciphertext_t *t1, *t2, *res;
	
	
	t1 = paillier_ciphertext_from_bytes(args->args[0], 16);
	if (initid->ptr == NULL) {
		initid->ptr = (char *) t1;
	} else {
		res = (paillier_ciphertext_t*) malloc(sizeof(paillier_ciphertext_t));
		mpz_init(res->c);
		t2 = (paillier_ciphertext_t *)initid->ptr;
		paillier_mul(pub, res,t1,t2);
		initid->ptr = (char *) res;
		free(t1);
		free(t2);
	}
}

char *SUM_HE(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error){
	*length = 16;
	char * tmp;
	if (initid->ptr == NULL) *is_null = 1;
	else tmp = (char*)paillier_ciphertext_to_bytes(16,(paillier_ciphertext_t *)initid->ptr);
	memcpy(result, tmp, 16);
	return result;
	
}

void SUM_HE_deinit(UDF_INIT *initid) {
	
	paillier_freepubkey(pub);
	
}
