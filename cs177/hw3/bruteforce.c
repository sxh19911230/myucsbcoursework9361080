#define _XOPEN_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i,j,k;
  char buff[9];
  int digit[8];
  char *cs[5];
  cs[0] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}\\|;\':\",./<>\?`";
  cs[1] =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  cs[2] =  "abcdefghijklmnopqrstuvwxyz1234567890";
  cs[3] =  "abcdefghijklmnopqrstuvwxyz";
  cs[4] =  "1234567890"; 

  char *charset;
  int charsize;

  if (argc != 3 || argv[1][0] < '0' || argv[1][0] > '4') {
    printf("Usage: %s <charset> <password hash>\n", argv[0]);
    for (i = 0; i < 5; ++i) printf("charset %i: %s\n",i,cs[i]);
    printf("Example: %s 2 STlLGmwDFuINg\n", argv[0]);
    return 0;
  }
  charset = cs[argv[1][0]-'0'];
  charsize = strlen(charset);
  //start with 6 chars
  printf("Password hash: %s\n", argv[2]);
  for (i = 6; i < 15; i++) {
    for (j = 0; j < i; ++j) {
      buff[j] = 'a';
      digit[j] = 0;
    }
    buff[j] = 0;
    k = 0;
    while ((digit[i-k-1] % charsize) || (i-k-1)) {
      if (!strcmp(crypt(buff, argv[2]), argv[2])) {
        puts("\nPassword Found: ");
        puts(buff);
        return 0;
      }
      for (k = 0; k < i; ++k) {
        digit[i-k-1] += 1;
        if (!(digit[i-k-1] % charsize) && !(i-k-1)) break;
        else if (!(digit[i-k-1] % charsize)) {
          digit[i-k-1] = 0;
          buff[i-k-1] = 'a';
        }
        else {
          buff[i-k-1] = charset[digit[i-k-1]];
          break;
        }
      }
      //puts(buff); 
    }
      
  }
  return 0;
}
