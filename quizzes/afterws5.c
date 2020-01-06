#include <stdio.h> 
#include <string.h> 
#include <assert.h> 
int IsRotated(const char* s1, const char* s2); 


int main(void)
{
    const char *s1 = "abcde"; 
    const char *s2 = "deabc";  
    
    printf("%d", IsRotated(s1,s2)); 
    return 0; 
}

int IsRotated(const char* s1, const char* s2)
{
    int n = 0; 
    int rot_cmp = 1; 
    int len = 0; 
    const char *s2_runner = s2; 
    
    assert(s1); 
    assert(s2); 
    
    if (strlen(s1) != strlen(s2))
    {
        return 0; 
    }
     
    len = strlen(s1); 
    rot_cmp = strcmp(s1,s2); 
    ++s2_runner; 
    ++n;  
    while (('\0' != *s2_runner) && (rot_cmp != 0))
    {
        rot_cmp = strncmp(s2, s1 + len - n, n) + strncmp(s2_runner, s1,len - n); 
        ++s2_runner; 
        ++n; 
    }

    return (rot_cmp == 0); 
}

