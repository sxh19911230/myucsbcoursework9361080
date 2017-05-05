#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *hash2;

char *orichar = "aegllostii";
char *subchar = "@39I10571l";
int len;

void check(char* buff) {
  if (strcmp (crypt(buff, hash2), hash2) == 0) {
    puts("Password Found:");
    puts(buff);
    exit(0);
  }  
}

void rescusiveSubsituteCheck(char* buff, int n) {
  char *higherCase, *otherCase;
  int i;
  int dirty = 0;
  if (n == len) {
     check(buff);
     higherCase = (char*) malloc(strlen(buff) + 1);
     strcpy(higherCase,buff);
     if (higherCase[0] >= 'a' && higherCase[0] <= 'z') {
       higherCase[0] -= 32;
       check(higherCase);
     }
     for (i = 1; higherCase[i]; ++i)
       if (higherCase[i] >= 'a' && higherCase[i] <= 'z') {
         higherCase[i] -= 32;
         dirty = 1;
       }
     if (dirty) check(higherCase);
     free(higherCase);
  }
  else {

    rescusiveSubsituteCheck(buff,n+1);

    otherCase = (char*) malloc(strlen(buff) + 1);
    strcpy(otherCase,buff);
    for (i = 0; otherCase[i] != 0; ++i)
      if (otherCase[i] == orichar[n]) {
        otherCase[i] = subchar[n];
        dirty = 1;
      }
    
    if (dirty) rescusiveSubsituteCheck(otherCase,n+1);
    free(otherCase);
  }
}

int main(int argc, char *argv[]) {
  int i;
  FILE *fp;
  char buff[30];
  len = strlen(orichar);

  if (argc != 3) {
    printf("Usage: %s <dictionary file> <hash>\n", argv[0]);
    printf("Example: %s wordsEn.txt \"\\$1\\$aEcddE12\\$9NCUhiNOvSP5QOdiRDf1Z.\"\n", argv[0]);
    return 0;
  }

  hash2 = argv[2];
  fp = fopen(argv[1], "r");

  while (fgets(buff, 255, fp) != NULL) {
    if (buff[strlen(buff) - 2] == '\r') buff[strlen(buff) - 2] = 0;
    else buff[strlen(buff) - 1] = 0;
    if(strlen(buff) >= 6) rescusiveSubsituteCheck(buff,0);
  }
  fclose(fp);
  return 0;
}
