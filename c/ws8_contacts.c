/****************************************************************************/
/*                                      WS8_contact.c                               */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/

#include <stdio.h>   /* printf, puts   */
#include <stdlib.h>  /* malloc and     */

#define SIZE ((sizeof(con_arr)/sizeof(con_arr[0])))
#define SIZEOFME(x) (((char*)(&x+1))-(char*)&x)

typedef struct DateOfBirth
{
    size_t day; 
    size_t month; 
    size_t year; 
} DateOfBirth_t;

typedef struct Contact
{
    char f_name[50]; 
    char l_name[50]; 
    DateOfBirth_t dob; 
    size_t ID; 
} Contact_t ; 
   
typedef struct X
{
    int i; 
    char c; 
    double d;
    short s; 
} x_t; 

typedef struct card
{
    unsigned int suit : 2; 
    unsigned in face_val : 4; 
} card_t; 
static const Contact_t con_arr[]=
{
    { "name1","name1", {1, 1, 1975}, 010},
    { "name2","name2", {2, 2, 1975}, 011},
    { "name3","name3", {3, 3, 1975}, 012},
    { "name4","name4", {4, 4, 1975}, 013},
    { "name5","name5", {5, 5, 1975}, 014},
    { "name6","name6", {6, 6, 1975}, 015},
    { "name7","name7", {7, 7, 1975}, 016},
    { "name8","name8", {8, 8, 1975}, 017},
    { "name9","name9", {9, 9, 1975}, 020},
    { "name10","name10", {10, 10, 1975}, 021}
};


int main (void)
{
     card_t one; 
    /*FILE *f_ptr = NULL; 
    
    Contact_t copied_arr[SIZE] = {0}; 
    
    f_ptr = fopen("mylog.dat","w");
    if (NULL == f_ptr)
    {
        return(EXIT_FAILURE);
    } 
    
    if(0 == fwrite(&con_arr,sizeof(Contact_t),SIZE,f_ptr)) 
    {
        return(EXIT_FAILURE);
    }
    fclose(f_ptr);
    f_ptr = fopen("mylog.dat","r");
    fread(copied_arr,sizeof(Contact_t),SIZE,f_ptr); 
    for(val = 0; val < SIZE; ++val)
    {
        printf("this is :%s %s \n", copied_arr[val].f_name, copied_arr[val].l_name);
        printf("Date of Birth is: %lu %lu \n", copied_arr[val].dob.day, copied_arr[val].dob.month); 
    }
    
    fclose(f_ptr);*/
    
    printf("%ld",SIZEOFME(one));
    
    return (EXIT_SUCCESS); 
}
