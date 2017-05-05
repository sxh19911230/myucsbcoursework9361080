#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//char const * const hash1 = "$5$aBD123cdE$ADH/D30llsWnrTJTKJBxvaztshXoNbX4J.hakVNp1p0";
//char const * const hash2 = "$1$aEcddE12$9NCUhiNOvSP5QOdiRDf1Z.";
//char const * const hash3 = "STlLGmwDFuINg";
char const * const hash4 = "$6$ZefEqq3q$ajIrXaQ6rlL/82W0sJ.vYhGTP1REEuMLWIlPQOTeiNDtrJeLmiU1vLM7x2zgP3qaD36nYearEvmrJ.Q4BbpCW0";

void check(char * buff) {
// puts(buff);
 if (strcmp (crypt(buff, hash4), hash4) == 0) {puts("4: "); puts(buff);}
}

int main(int argc, char *argv[]) {
  int i,j,k;
  FILE *fp;
  char buff[255], *result;
  char* words[109582];
  int len;

  fp = fopen("English.txt", "r");
  for (i = 0; fgets(buff, 255, fp) != NULL; i++) {
    len = strlen(buff);
    words[i] = (char*)malloc(len);
    buff[strlen(buff) - 1] = 0;
    strcpy(words[i],buff);
  }
  fclose(fp);


  for (i = atoi(argv[1]); i < atoi(argv[2]); i++) { 
    strcpy(buff,words[i]);
    len = strlen(buff);
    for (j = 0; j < 109582; j++) {
      memcpy(buff+len,words[j], strlen(words[j])+1);
      if (strlen(buff) >= 6)  check(buff);
    }
  }
  return 0;
}

