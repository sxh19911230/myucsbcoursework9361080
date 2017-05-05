#include <stdio.h>
#include <stdlib.h>
int main(int args, char** argv){ 
  FILE *pFile;
  int i, total;
  char exch[] ="mapzmdtvwcxc";
  char key[13]={0};
  char c;

  pFile = fopen(argv[1], "rb");

  if (!pFile) {
    fputs("File error", stderr);
    exit(1);
  }
  total = 0;
  do {
    
    c = fgetc(pFile);
    if (exch[total%12]-32 == c) key[total%12] = (c - 'E' + 26) % 26 + 97;
    total++;
  } while (c != EOF);
  fclose(pFile);
  key[12] = 0;
  printf("%s\n",key);
  return 0;
  
}
