#include <stdio.h>
#include <stdlib.h>
int main(int args, char** argv){ 
  FILE *pFile;
  int i,j;
  char c, *str;

  str = "IUTMXGZARGZOUTYZNOYOYZNKVRGOTZKDZ";

  
  for (i = 0; i< 26; i++) {
    j = 0;
    do {
        putchar((str[j] - 'A' + i) % 26 + 'A');
    } while (str[++j] != 0);
    putchar('\n');
  }
  return 0;
  
}
