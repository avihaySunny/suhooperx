#include <stdio.h>


#define MAX(a,b) ((a > b) ? (a): (b))
#define MAX3(a,b,c) MAX(MAX(a,b), MAX(b,c))
#define TO_LOWER(c) ((c >= 'A' && c <= 'Z') ? (c +('a'- 'A')) : (c))
#define OFFSET(s,f) (&(s->f) - &s)
int main (void)
{

    printf("%c",TO_LOWER('l'));
    return 0;

}
