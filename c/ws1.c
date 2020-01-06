
/*this will be the first of many */
#include <stdio.h>

void Hello() /* HELLO WORLD! IN ASCII */
{
printf("%c%c%c%c%c%c%c%c%c%c%c%c"
        ,0x48,0x65,0x6C,0x6C,0x6F,0x20
        ,0x57,0x6F,0x72,0x6C,0x64,0x21);
}

float Power(int x, float y) /* computes y^x, also if neg*/
    {
      float result =1;
      if (y==0)
        {
            printf("Jeez why");
            return 0;
        }
      if (x<0) /* in case it's a negetive power */
        {
        y=1/y;
        x*=-1;
        }

      for (int i=0; i<x; i++)
        {
         result*=y;
        }
       return result;
}

int TenPower(int x)
    {
     return (int)Power(x, 10.0);
    }

int flip(int num) /*flips the number*/
    {
    int count=0; /*keep track of digit 10's*/
    int mirror_num=num;

    while(mirror_num!=0)
        {
         count++;
         mirror_num/=10;
        }

   for(count=count-1; count>=0 ;count--)
        {
        mirror_num+=((num%10)*TenPower(count));
        num/=10;
        }

        return mirror_num;

    }

void swap(int *a,int *b)
{
int *c=*a;
*a=*b;
*b=*c;

}
void main()
{
int num;



}

double sqrt(double number) /* ignore */
{
double x_n = number/2;
double x_nplus = 0; 
double delta = 1;
    
    while (delta < 0.01)
        {
         x_nplus = x_n - ( ( ( x_n * x_n ) - number ) / (2 * x_n)) ; 
         delta = ( x_nplus * x_nplus ) - number ;
         if ( delta < 0 ) 
             delta *= -1 ;                           
        }
return x_nplus; 
} 
    

