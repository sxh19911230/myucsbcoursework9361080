#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *hash2 = "$1$aEcddE12$9NCUhiNOvSP5QOdiRDf1Z.";

void check(char* buff) {
  if (strcmp (crypt(buff, hash2), hash2) == 0) {puts("2: "); puts(buff);}
}

void rescusiveSubsituteCheck(char* buff, int n) {
  char *higherCase, *otherCase;
  if (buff[n] == 0) check(buff);
  else {
    rescusiveSubsituteCheck(buff, n+1);

    if (buff[n] <='z' && buff[n] >='a') {
      higherCase = (char*) malloc(strlen(buff) + 1);
      strcpy(higherCase,buff);
      higherCase[n] -= 32;
      rescusiveSubsituteCheck(higherCase,n+1);
      free(higherCase);
    }

    otherCase = (char*) malloc(strlen(buff) + 1);
    strcpy(otherCase,buff);
    switch (otherCase[n]) {
    case('a'):
      otherCase[n] = '@';
      rescusiveSubsituteCheck(otherCase, n+1);
      otherCase[n] = '4';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('e'):
      otherCase[n] = '3';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('g'):
      otherCase[n] = '9';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('l'):
      otherCase[n] = 'I';
      rescusiveSubsituteCheck(otherCase, n+1);
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
      otherCase[n] = '$';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('x'):
      otherCase[n] = '%';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('y'):
      otherCase[n] = '?';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('i'):
      otherCase[n] = '1';
      rescusiveSubsituteCheck(otherCase, n+1);
      otherCase[n] = 'l';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    case('t'):
      otherCase[n] = '7';
      rescusiveSubsituteCheck(otherCase, n+1);
      break;
    
    case('w'):
      memcpy(otherCase+n+2, otherCase+n+1, strlen(otherCase)-n);
      otherCase[n] = 'u';
      otherCase[n+1] = 'u';
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
    if (buff[strlen(buff) - 2] == '\r') buff[strlen(buff) - 2] = 0;
    else buff[strlen(buff) - 1] = 0;
    if(strlen(buff) >= 6) rescusiveSubsituteCheck(buff,0);
    
  }
  fclose(fp);
    
  return 0;
}
