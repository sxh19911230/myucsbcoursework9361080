#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char buff[255];

int main(int argc, char *argv[]) {
  FILE *fp;
  int all = 0, sixmore = 0;

  fp = fopen("words10k.txt", "r");

  while (fgets(buff, 255, fp) != NULL) {
    if (strlen(buff) > 6) ++sixmore;
    ++all;
  }
  fclose(fp);
  printf("all:%i sixmore:%i\n", all, sixmore);
  return 0;
}

