#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

int
main(void)
{
  /* Hashed form of "GNU libc manual". */
  char *hash1 = "$5$aBD123cdE$ADH/D30llsWnrTJTKJBxvaztshXoNbX4J.hakVNp1p0";
  char *hash2 = "$1$aEcddE12$9NCUhiNOvSP5QOdiRDf1Z."; 
  char *hash3 = "STlLGmwDFuINg"; 
  char *hash4 = "$6$ZefEqq3q$ajIrXaQ6rlL/82W0sJ.vYhGTP1REEuMLWIlPQOTeiNDtrJeLmiU1vLM7x2zgP3qaD36nYearEvmrJ.Q4BbpCW0"; 

  char *result, pass[255];

  /* Read in the user’s password and encrypt it,
 *      passing the expected password in as the salt. */
while(1) {
    gets(pass);
    result = crypt(pass, hash1);
    if (strcmp (result, hash1) == 0) printf("1:%s\n",pass);
    result = crypt(pass, hash2);
    if (strcmp (result, hash2) == 0) printf("2:%s\n",pass);
    result = crypt(pass, hash3);
    if (strcmp (result, hash3) == 0) printf("3:%s\n",pass);
    result = crypt(pass, hash4);
    if (strcmp (result, hash4) == 0) printf("4:%s\n",pass);
  }
  return 0;
}

