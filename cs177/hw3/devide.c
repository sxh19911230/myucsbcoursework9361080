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


  if (argc != 2) return 0;
  fp = fopen(argv[1], "r");
  fp1 = fopen("words1.txt","w+");
  fp2 = fopen("words2.txt","w+");
  fp3 = fopen("words3.txt","w+");
  fp4 = fopen("words4.txt","w+");
  fp5 = fopen("words5.txt","w+");

  while (1) {
    if (myWrite(fp,fp1)) break;
    if (myWrite(fp,fp2)) break;
    if (myWrite(fp,fp3)) break;
    if (myWrite(fp,fp4)) break;
    if (myWrite(fp,fp5)) break;
  }
  fclose(fp);
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
  fclose(fp5);
  return 0;
}

