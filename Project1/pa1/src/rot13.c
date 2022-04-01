#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
  printf("Please enter string here: "); //inputs string to encode MAKE SURE TO PUT SPACE BETWEEN!!!!

  size_t sbuff_len = 256;
  char* sbuff = (char*)calloc(sbuff_len, sizeof(char));

  char c;
  size_t len = 0;
  while((c = getchar()) != '\n') {
    sbuff[len++] = isalpha(c) ? ((c - (islower(c) ? 'a' : 'A') + 13) % 26 + (islower(c) ? 'a' : 'A')) : c;

    if(len == sbuff_len) {
      size_t new_len = sbuff_len + 256;
      char* new_buff = (char*)realloc(sbuff, new_len * sizeof(char));

      if(new_buff != NULL) {
        sbuff_len = new_len;
        sbuff = new_buff;
      }
      else {
        printf("There is an input error .\n");
        return 1;
      }
    }
  }
  sbuff[len] = '\0';

  printf("Please Enter the encoded string here: %s\n", sbuff);

  free(sbuff);
  return 0;
}