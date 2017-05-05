#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i;
  char *hash1 = "$5$aBD123cdE$ADH/D30llsWnrTJTKJBxvaztshXoNbX4J.hakVNp1p0";
  FILE *fp;
  char buff[255], *result;

  if (argc != 3) {
    printf("Usage: %s <dictionary file> <pass hash>\n", argv[0]);
    printf("Example: %s wordsEn.txt \"\\$5\\$aBD123cdE\\$ADH/D30llsWnrTJTKJBxvaztshXoNbX4J.hakVNp1p0\"\n",argv[0]);
    return 0;
  }

  fp = fopen(argv[1], "r");
  while (fgets(buff, 255, fp) != NULL) {
    
    if (buff[strlen(buff) - 2] == '\r') buff[strlen(buff) - 2] = 0;
    else buff[strlen(buff) - 1] = 0;

    if (strcmp (crypt(buff, hash1), hash1) == 0) {
       puts("Password Found:");
       puts(buff);
       break;
    }
  }
  fclose(fp);
    
  return 0;
}
