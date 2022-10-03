#include <stdio.h>
#include <string.h>

int main()
{
   char c[100];
   int length;

   printf("Enter a string = ");
   gets(c);

   length = strlen(c); // strlen to find string lenth

   printf("\nlength of string is = %d\n", length);

   return 0;
}
