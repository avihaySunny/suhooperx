#include <stdio.h>
#include <stdlib.h>

int main (void)
{
  unsigned long w = 0; 
  int c = 0xff; 
  for (i = 0; i < (8/ sizeof(char)); ++i)
    {
        w <<= SIZEOF_BYTE;
        word += c;
    }

  printf("%ld\n", w);
  return (EXIT_SUCCESS);
}
