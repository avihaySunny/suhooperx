#include <stdio.h>
#include <string.h>

void SwapChar(char *a, char *b);
void PermutaionsRec(char *string, size_t len, size_t indx);


void PermutaionsRec(char *string, size_t len, size_t indx)
{
    size_t j = 0; 
    if (indx == len)
    {
        printf("%s\n", string); 
    }

    else
    {
        for (j = indx; j <= len; ++j)
        {
            SwapChar(&string[indx], &string[j]); 
            PermutaionsRec(string, len, j + 1); 
            SwapChar(&string[indx], &string[j]);
        }
    }
    
}

void SwapChar(char *a, char *b)
{
    char tmp = *a; 
    *a = *b; 
    *b = tmp; 
}

int main (void)
{
    char msg[] = "Abc"; 
    PermutaionsRec(msg, 3, 0); 

    return 0; 
}