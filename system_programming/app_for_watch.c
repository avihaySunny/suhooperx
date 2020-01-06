#include <stdlib.h>
#include <stdio.h>

int main (void)
{
    int i = 0;
    FILE *f_ptr = fopen ("mylog.txt", "a");

    while (i < 500000000)
    {
        ++i;
    }

    fprintf(f_ptr, "x\n");
    
    fclose(f_ptr);

    return EXIT_SUCCESS; 
}