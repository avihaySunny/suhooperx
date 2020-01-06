/*           Declaration of the String.h libary for several fucntions     */ 
/*                      Written by : Avihay Asraf                         */ 
/*                       April 2019                                       */ 

#ifndef __WS2_H__ 
#define __WS2_H__

 
size_t Strlen(const char *str);                             /* return size of string                         */
 
size_t Strspn(const char *s, const char *accept);           /* returns the max span of instances             */    
 
int Strcmp(const char *str1, const char *str2);             /* compares str2 to str1                         */ 
 
int Strncmp(const char *str1, const char *str2,int n);      /* compares n bytes of str1                      */
 
char* Strcpy(char *dest, const char *src);                  /*  copies src to des                            */  
 
char *Strncpy(char *dest, const char *src, size_t n) ;      /* copies up to n char from src to dest          */ 
 
int Strcasecmp(const char *s1, const char *s2);             /* strcmp without caring for upper/lower         */  
 
char *Strchr(const char *str, int c);                       /* return first instance of 'c', null otherwise  */ 
  
char *Strdup(const char *s);                                /* return a duplicate of s                       */

char *Strcat(char *dest, const char *src);                  /* truncates src on dest                         */ 

char *Strncat(char *dest, const char *src, size_t n);       /* truncates n bytes from src onto dest          */

char *Strstr(const char *haystack, const char *needle);     /* returns first instance of needle in haystack  */

char *Strtok(char *str, const char *delim);                 /* return first instace of token                 */

int IsPalindrome(const char *str);                          /* checks if is a palindrom                      */                                   

void Boom(int from, int upto);                  

static int IsSeven(int number);                             /* take a int number and turns into a string     */

void RmSpaces(char *str);                                   /* Remove spaces                                 */                         

void Swap(int **a,int **b);        

char *StrSum(const char *num1, const char *num2);
 #endif 
 
