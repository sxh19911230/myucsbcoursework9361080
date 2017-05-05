#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char buff[255];

int myWrite(FILE* fp, FILE* fpw) {
  if (fgets(buff, 255, fp) != NULL) {
    fputs(buff,fpw);
    return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  FILE *fp,*fp1,*fp2,*fp3,*fp4,*fp5;;
  int i = 0;
  fp = fopen("words10k.txt", "r");

  while (fgets(buff, 255, fp) != NULL) {
    buff[strlen(buff)-1] = 0;
    if (strcmp(buff, argv[1]) == 0) i = 50;
    if (i-- > 0) puts(buff);
  }
  fclose(fp);
  return 0;
}

