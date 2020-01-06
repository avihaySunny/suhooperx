 /*           Testing of the String.h libary for several fucntions         */ 
/*                      Written by : Avihay Asraf                         */ 
/*                       April 2019                                       */ 
#include <stdio.h>      /* printf       */
#include <stdlib.h>     /* malloc, free */
#include "ws2.h"        

    void TestStrlen(void);
    void TestStrcmp(void); 
    void TestStrcpy(void);
    void TestStrncpy(void);
    void TestStrcasecmp(void);
    void TestStrchr(void);
    void TestStrdup(void);
    void TestStrcat(void);
    void TestStrncat(void);
    void TestStrstr(void); 
    void TestStrspn(void);
    void TestStrtok(void);  
    void TestStrSum(void);

int main (void) 
{       
  /*  TestStrlen();
    TestStrcmp(); 
    TestStrcpy();
    TestStrncpy();
    TestStrcasecmp();
    TestStrchr();
    TestStrdup();
    TestStrcat();
    TestStrncat();
    TestStrstr(); 
    TestStrspn();
    TestStrtok();  
    TestStrSum(); */
    
    char str[]= "HELLO WORLD1245!";
    StrToLow(str);
    printf("%s",str);
    
    return 0;
}

void TestStrlen(void)
{
    const char str1[] = "Hello World!";
    const char str2[] = ""; 
    const char *ptr_s1 = str1;
    const char *ptr_s2 = str2; 
    
    printf("%s character length is : %ld", str1, Strlen(ptr_s1));
    printf("%s character length is : %ld", str2, Strlen(ptr_s2));
}

void TestStrcmp(void)
{
    const char str1[] = "Hello World!";
    const char str2[] = "Hello World!"; 
    const char str3[] = "Hello Horld";  
    const char *ptr_s1 = str1;
    const char *ptr_s2 = str2; 
    const char *ptr_s3 = str3; 
    
    printf("\nstr 1 is %s, str2 is %s, differnce is %d \n",
                         str1, str2, Strcmp(ptr_s1, ptr_s2));
    printf("\nstr 1 is %s, str2 is %s, differnce is %d \n",
                        str1, str3, Strcmp(ptr_s1, ptr_s3));
}

void TestStrcasecmp(void)
{
    const char str1[] = "Hello World!";
    const char str2[] = "Hello World!"; 
    const char str3[] = "hello world!";  
    const char *ptr_s1 = str1;
    const char *ptr_s2 = str2; 
    const char *ptr_s3 = str3; 
    
    printf("str 1 is %s, str2 is %s, differnce is %d \n",
                         str1 ,str2 ,Strcmp(ptr_s1, ptr_s2));
    printf("str 1 is %s, str2 is %s, differnce is %d \n",
                        str1, str3, Strcasecmp(ptr_s1, ptr_s3));
}

void TestStrcpy(void)
{
    char str1[] = "The cake is a lie! ";
    const char str2[] = "please don't tell me that"; 
    char *ptr_s1 = str1;
    const char *ptr_s2 = str2; 
    
    printf(" \n str1 is : %s, str2 is : %s\n ", str1, str2);
    printf("\n after copy str1 is : %s ", Strcpy(ptr_s1, ptr_s2));
}

void TestStrncpy(void)
{
    char str1[] = "The cake is a lie!";
    const char str2[] = "please don't"; 
    char *ptr_s1 = str1;
    const char *ptr_s2 = str2;
    
    printf("str1 is : %s, str2 is : %s\n ", str1, str2);
    printf("\n after copy with n=3 str1 is : %s \n",Strncpy(ptr_s1, ptr_s2, 3));
}

void TestStrchr(void)
{
    const char str2[] = "maybe maybe";
    const char *ptr_s2 = str2;
    int c1 = 'y';
    int c2 = 'r';
    
    printf ("\n the rest of %s is character 's' is :%s \n",
                                    str2,Strchr(ptr_s2, c1));
    printf ("\n the rest of %s is character 'r' is :%s \n",
                                    str2,Strchr(ptr_s2, c2));
}

void TestStrdup(void)
{
    char str1[] = "The cake is a lie!";
    char *dup_string = Strdup(str1); 
    
    printf("\n original string is : %s \n", str1);
    printf("\n duplicated string is : %s\n ", dup_string);
    
    free(dup_string); 
}

void TestStrcat(void)
{
    char str1[100] = "The cake is a lie!";
    const char str2[] = "please don't tell me that!"; 
    
    printf("Original string is : %s, 2nd string is %s :\n", str1, str2);
    printf("Truncated string is : %s \n", Strcat(str1, str2));
}

void TestStrncat(void)
{
    char str1[100] = "The cake is a lie!";
    const char str2[] = "please don't tell me that!"; 
    
    printf("Original string is : %s, 2nd string is %s :\n", str1, str2);
    printf("Truncated string is with n=0 : %s \n", Strncat(str1, str2, 0));
}
void TestStrstr(void)
{
    const char str1[100] = "The cake is a lie! is it?  ";
    const char str2[] = "lie!"; 
    const char str3[]="don't";
    
    printf("Original string is : %s ,we look for %s :\n", str1, str2);
    printf("found it : %s \n", Strstr(str1, str2));
    printf("did i find it? : %s \n", Strstr(str1, str3));
}

void TestStrspn(void)
{
     const char dest[] = "abcdefghijk";
     const char src1[] = "ablie!"; 
     const char src2[] = "abcd!"; 
     
     printf("span1 is :%ld \n span is %ld \n",
            Strspn(dest, src1),Strspn(dest, src2));
}

void TestStrtok(void)
{
    char dest[] = "Ceterum-censeo-Carthaginem-esse-delendam?";
    const char delim[] = "-";
    char *ptr_s1 = dest;
    const char *ptr_s2 = delim; 
    char *next = Strtok(ptr_s1, ptr_s2);
    
    printf ("%s \n", dest); 
    
    while(next != NULL)
    {
        next=Strtok(NULL, ptr_s2);
        printf("%s \n", next);
    }
}

void TestStrSum(void)
{
    const char num1[] = "99111";
    const char num2[] = "111999";
    char *str = NULL;
    
    str = StrSum(num1, num2); 
    printf("\n%s + %s = %s \n", num1, num2, str);
    
    free(str);
    str = NULL;
    
}


