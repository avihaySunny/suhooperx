/****************************************************************************/
/*                                      WS6.c                               */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/

#include <stdio.h>          /* printf, puts      */
#include <stdlib.h>         /* EXIT_SUCCESS      */

static long pow2(unsigned int x, int y);          /* Calcs x*2^y                                 */

static int IsPowerOf2(unsigned int x);            /* Returns 1 if x = 2^n                        */

static int IsPowerOf2Loop(unsigned int x);        /* Returns 1 if x = 2^n using loop             */

static void pow2Test(void);                       /* Test for pow2                               */

static void IsPowerOf2Test(void);                 /* Test for IsPowerOf2/Loop                    */

static int CountOnBits(unsigned int x);           /* Return # of On bits (1's)                   */

static void NumOfBitsON(unsigned int numbers[], int n, int num_of_bits); 
                                                          /* <- Returns true for num bits on  */ 

static unsigned int AddOne(unsigned int number);         /* Adds one without arithmetic             */

static void AddOneTest(void);                            /* Test for AddOne                         */

static int Bits2n6On(unsigned char number);              /* Checks bits 2 and 6                     */

static int Bits2or6On(unsigned char number);             /* Checks bits 2 or 6                      */

static void Bit2norTest(void);                           /* Tests Bits2n6On and Bits2or6On           */

static unsigned char BitMirror(unsigned char number);    /* Mirror bits of unsigned char without loop*/

unsigned char BitMirrorLoop(unsigned char number);       /*Mirror bits of unsigned char with loop    */

static void BitMirrorTest(void);                         /*Test BitMirror and BitMirrorLoop          */

static char SwapBits3n5(unsigned char number);            /* Swaps bits 3 and 5                      */

static void FloatPrint(float x);                         /* Prints all bits of float                 */

static void FloatPrintTest(void);                        /* Test for  Float print                    */

static void Swap(unsigned char *a, unsigned char *b);    /* Swaps two ints using xor                 */

static unsigned int Divisible16(unsigned int number);    /*Checks if n Divisible by 16               */

static void Divis16Test(void);                           /* Test for divisible by 16                 */

static unsigned int OnesBit(unsigned int number);        /* number of on bits using Hamming weight   */

static void BitsOnTest(void);                            /* Test bit count                           */

static void Test3Bits(void);                             /* Test 3bitson                             */

static void TestSwap(void);                              /*Test swap bits and swap                   */
/******************************************************************************/

int main(void)
{
    pow2Test();

    IsPowerOf2Test();
    
    Test3Bits(); 
    
    BitsOnTest(); 

    AddOneTest();

    Divis16Test();
    
    FloatPrintTest(); 
   
    BitMirrorTest();
    
    Bit2norTest();

    TestSwap();
  
    return EXIT_SUCCESS;
}

/************* TEST FUNCTION SECTION **************************************/

static void pow2Test(void)
{
    unsigned int x = 1, y = 1, i = 1;

    for (; i < 7; ++i, ++x, ++y)
    {
        printf("x = %x, y = %x using func: %ld \n",x ,y ,pow2(x,y));
    }
}

static void IsPowerOf2Test(void)
{
    int unsigned i = 1;
    for (; i < 65; ++i )
    {
        puts("Without loop");
        printf(" \n x = %d is power of 2 ? : %d \n ",i ,IsPowerOf2(i));
        printf("With loop");
        printf(" \n x = %d is power of 2 ? : %d \n ",i ,IsPowerOf2Loop(i));
    }
}

static void AddOneTest(void)
{
    unsigned int i = 0;
    
    puts("");
    for (; i < 20; ++i)
    {
        printf("number is %u, plus one is : %u \n",i ,AddOne(i));
    }
}

static void FloatPrintTest(void)
{
    float number = 0;
    puts("Enter Number please"); 
    if(1 == scanf("%f", &number))
    {
        FloatPrint(number);
    }
       
    else 
    {
        fputs("Scan error", stderr); 
    }
}

static void Divis16Test(void)
{
    unsigned int i = 17;

    for(; i < 2764; i+=42)
    {
        printf("closest divisible number for %u is %u\n",i, Divisible16(i));

    }
}

static void BitMirrorTest(void)
{
    unsigned char mirror = 1; 
    for (; mirror < 20; ++mirror)
    {
        printf("Number to mirror is : %u\n", mirror);
        printf("with loop    : %u \n",BitMirror(mirror));
        printf("without loop : %u \n",BitMirrorLoop(mirror));
    }
}

static void Bit2norTest(void)
{
    unsigned char number = 0; 
    
    for (; number < 0xff; ++number)
    {
        if(Bits2n6On(number))
        {
            printf("Number %u has bit 2 and 6 on \n",number); 
        }
        
        if(Bits2or6On(number))
        {
            printf("Number %u has bit 2 or 6 on \n",number); 
        }
    }
}

static void BitsOnTest(void)
{
    unsigned int number = 0; 
    
    for(; number < 0xff; ++number)
    {
        puts("Using count"); 
        printf("Number is %u, # bits on is : %d ",number ,CountOnBits(number));
        puts("Using Hamming Weight "); 
        printf("Number is %u, # bits on is : %d ",number ,OnesBit(number));
    }
}

void Test3Bits(void)
{
    unsigned int numbers[] = {2, 5, 7, 9, 11, 12, 27, 14};
    NumOfBitsON(numbers, 8, 3);    
}

void TestSwap(void)
{
    unsigned char a = 47, b = 10; 
    printf("a = %u, b = %u \n",a ,b);
    puts("Now Swap"); 
    Swap(&a, &b);
    printf("a = %u, b = %u \n",a ,b); 
    puts("Now Swap bit 3 and 5 on b (47)");
    printf("b = %u", SwapBits3n5(b)); 
}

/***************************FUNCTION SECTION*****************************/

static long pow2(unsigned int x, int y)
{
   return((y < 0) ? ( x >> y) : (x << -y));
}

static int IsPowerOf2(unsigned int x)
{
    return (0 == (x & (x - 1 )));
}

static int IsPowerOf2Loop(unsigned int x)
{
    return (CountOnBits(x) == 1 );  
}

static int CountOnBits(unsigned int x)
{
    int count = 0;

    while(0 != x )
    {
        count +=  x & 1;
        x >>= 1;
    }

    return count;
}

static void NumOfBitsON(unsigned int numbers[], int n,int num_of_bits)
{
    int i = 0;
    
    printf("\n Number with %d bits are:", num_of_bits);
    for (; i < n; ++i)
    {
        if(num_of_bits == CountOnBits(numbers[i]))
        {
            printf(" %u \n ", numbers[i]);
        }
    }
}

static unsigned int AddOne(unsigned int number) /* can also be (-(~number))*/
{
    unsigned int carry = 1;
    unsigned int num_copy = number;

    while (num_copy & 1)
    {
        carry <<= 1;
        carry |= 1;
        num_copy >>= 1;
    }

    return (number ^ carry); 
}

static unsigned char BitMirror(unsigned char number)
{
    unsigned char p1 = 0, p2 = 0, p3 = 0, p4 = 0, p_all = 0; /*p for pair */
 
    p1 = (number & 1) ^ ((number >> 7) & 1);
    p2 = ((number >> 1) & 1) ^ ((number >> 6) & 1);
    p3 = ((number >> 2) & 1) ^ ((number >> 5) & 1);
    p4 = ((number >> 3) & 1) ^ ((number >> 5) & 1);

    p_all = (((p1 << 7) | (   p1  ))  |
             ((p2 << 6) | (p2 << 1))  |
             ((p3 << 5) | (p3 << 2))  |
             ((p4 << 4) | (p4 << 3)))   ; 
    
    return (number ^ p_all);
}

static int Bits2n6On(unsigned char number)
{
    return (0 == ((number & 0x22) ^ 0x22 ));
}

static int Bits2or6On(unsigned char number)
{
    return (0 != ((number & 0x20) | (number & 0x2)));
}

static char SwapBits3n5(unsigned char number)
{
    unsigned char diff_bit = ((number >> 2) & 1) ^ ((number >> 4) & 1); /*Check difference between bits 3 and 5 */

    diff_bit = ((diff_bit << 2) | (diff_bit << 4)) ; /*mask creation */
    return (number ^ diff_bit);
}

static void Swap(unsigned char *a, unsigned char *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

static void FloatPrint(float x)
{
    int i = 31;
    void *ptr = NULL;
    ptr = &x;  
    
    for(; i >= 0; --i)
    {
         ((*((int *)ptr) & (1 << i)) == 0) ? (printf("0")) : (printf("1")) ;
        
    }
    puts("");
}
    
unsigned char BitMirrorLoop(unsigned char number)
{
    unsigned char mirrored = 0;
    size_t i = 0;
    
    for (; i < sizeof(number); ++i)
    {
        if (number & 1 )
        {
            mirrored <<= 1;
            mirrored += 1;
        }

        else
        {
            mirrored <<= 1;
        }

        number >>= 1 ;
    }

    return mirrored;
}

static unsigned int Divisible16(unsigned int number)
{
     return (number & 0xfffffff0);      /*clears the reminder */
}

static unsigned int OnesBit(unsigned int number) /*Uses Hamming weight algo for 32bit int */
{
    number = number - ((number >> 1) & (0x55555555)); /*how many bits in every 2 bits set */ 
    number = (number & 0x33333333) + ((number >> 2) & 0x33333333); /* how many bits in every 4 bits */
    number = (number + (number >> 4)) & (0x0f0f0f0f); /*so on */
    number = number + (number >> 8);
    number = number + (number >> 16);
    
    return number & 0x3f;
}


