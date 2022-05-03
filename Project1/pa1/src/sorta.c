#include <stdio.h>
#include <string.h>

int main() {
   char str[3][100], temp[100];
   printf("Enter 5 words: ");

   // Getting strings input
   for (int i = 0; i < 3; ++i) {
      fgets(str[i], sizeof(str[i]), stdin);
   }

   // storing strings in the lexicographical order
   for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 3; ++j) {

         // swapping strings if they are not in the lexicographical order
         if (strcmp(str[i], str[j]) > 0) {
            strcpy(temp, str[i]);
            strcpy(str[i], str[j]);
            strcpy(str[j], temp);
         }
      }
   }

   printf("\nIn the lexicographical order: \n");
   for (int i = 0; i < 3; ++i) {
      fputs(str[i], stdout);
   }
   return 0;
}
