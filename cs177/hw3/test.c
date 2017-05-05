#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i,j;
//  char *hash1 = "$5$aBD123cdE$ADH/D30llsWnrTJTKJBxvaztshXoNbX4J.hakVNp1p0";
//  char *hash2 = "$1$aEcddE12$9NCUhiNOvSP5QOdiRDf1Z."; 
//  char *hash3 = "STlLGmwDFuINg"; 
  char *hash4 = "$6$ZefEqq3q$ajIrXaQ6rlL/82W0sJ.vYhGTP1REEuMLWIlPQOTeiNDtrJeLmiU1vLM7x2zgP3qaD36nYearEvmrJ.Q4BbpCW0"; 
  FILE *fp;
  char buff[255], *result;

  if (argc != 2) {
    printf("Usage: %s <dictionary file>\n", argv[0]);
    return 0;
  }

  fp = fopen(argv[1], "r");
  while (fgets(buff, 255, fp) != NULL) {
    buff[strlen(buff) - 1] = 0;
    for (j = 0; j < 26; ++j) {
      for (i = 0; buff[i] != 0; ++i) buff[i] = (buff[i] -'a' + 1) % 26 +'a';  
      if (strcmp (crypt(buff, hash4), hash4) == 0) {puts("4: "); puts(buff);}
    }
  }
  fclose(fp);
    
  return 0;
}
