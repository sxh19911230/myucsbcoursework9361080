#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//char *hash1 = "$5$aBD123cdE$ADH/D30llsWnrTJTKJBxvaztshXoNbX4J.hakVNp1p0";
//char *hash2 = "$1$aEcddE12$9NCUhiNOvSP5QOdiRDf1Z.";
//char *hash3 = "STlLGmwDFuINg";
char *hash4 = "$6$ZefEqq3q$ajIrXaQ6rlL/82W0sJ.vYhGTP1REEuMLWIlPQOTeiNDtrJeLmiU1vLM7x2zgP3qaD36nYearEvmrJ.Q4BbpCW0";


void check(char* buff) {
//  puts(buff);
//  if (strcmp (crypt(buff, hash2), hash2) == 0) {puts("2: "); puts(buff);}
//  if (strcmp (crypt(buff, hash3), hash3) == 0) {puts("3: "); puts(buff);}
  if (strcmp (crypt(buff, hash4), hash4) == 0) {puts("4: "); puts(buff);}
}

void rescusiveSubsituteCheck(char* buff, int n) {
  char *higherCase, *otherCase;
  char tmp[20];
  if (buff[n] == 0) puts(buff);//check(buff);
  else {
    rescusiveSubsituteCheck(buff, n+1);
    if (n == 0) {
      higherCase = (char*) malloc(strlen(buff) + 1);
      strcpy(higherCase, buff);
      higherCase[0] -= 32;
      rescusiveSubsituteCheck(higherCase, n+1);
      free(higherCase);
    }

    otherCase = (char*) malloc(strlen(buff) + 1);
    strcpy(otherCase,buff);
    switch (buff[n]) {
    case('e'):
      otherCase[n] = '3';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('g'):
      otherCase[n] = '9';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('l'):
      otherCase[n] = '1';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('o'):
      otherCase[n] = '0';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('s'):
      otherCase[n] = '5';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('i'):
      otherCase[n] = '1';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('t'):
      otherCase[n] = '7';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('a'):
      otherCase[n] = '4';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('z'):
      otherCase[n] = '2';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('w'):
      strncpy(tmp,otherCase+n+1,strlen(otherCase)-n);
      otherCase[n] = 'u';
      otherCase[n+1] = 'u';
      otherCase[n+2] = 0;
      strcat(otherCase,tmp);
      rescusiveSubsituteCheck(otherCase, n+2);
      break;
    }
    free(otherCase);
  }
}

int main(int argc, char *argv[]) {
  int i;
  FILE *fp;
  char buff[30];

  if (argc != 2) {
    printf("Usage: %s <dictionary file>\n", argv[0]);
    return 0;
  }

  fp = fopen(argv[1], "r");

  while (fgets(buff, 255, fp) != NULL) {
    if(strlen(buff) > 6) {
      buff[strlen(buff) - 1] = 0;
      rescusiveSubsituteCheck(buff,0);
    }
  }
  fclose(fp);
    
  return 0;
}
