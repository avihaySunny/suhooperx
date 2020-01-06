/****************************************************************************/
/*                                    BitsArrayTests.c                      */
/*                                   Avihay Asraf                           */
/*                                    May 2019                              */
/*                                  Data Structurs                          */  
/****************************************************************************/
#include <stdio.h>      /*printf, puts          */  
#include <stdlib.h>     /*Exit Succes/failure   */   

#include "./include/bits_array.h" 

#define BIT_ARR_BITS_NUM (sizeof(bits_arr_t) * 8)   

void BitsArrPrint(bits_arr_t ba);
/******************TEST FUNC DECLARATION********************************/
static void TestBitsAllOnOff(void);

static void TestSetBitOnOff(void);

static void TestSetBits(void);

static void TestFlipBits(void);

static void TestRotateBitArr(void);

static void TestMirror(void);

static void TestCountOnOff(void);

static void TestRangeOffOn(void);

static void TestIsOnOff(void); 

static void TestFastMirror(void); 

static void TestFastCountOn(void); 

/****************************MAIN**************************************/
int main (void)
{ 
    puts("Testing Set ALL on/off");
    TestBitsAllOnOff();
    puts("Testing Set bit on/off");
    TestSetBitOnOff();
    puts("Testing SetOff SetOn");
    TestSetBits();
    puts("Testing Is Bits On/Off");
    TestIsOnOff();
    puts("Testing Flip all & one by one ");
    TestFlipBits();
    puts("Testing Rotate left and right ");
    TestRotateBitArr();
    puts("Testing Mirror Bits ");
    TestMirror();
    puts("Testing Count ON/OFF bits");
    TestCountOnOff();
    puts("Testing SET RANGE ON/OFF");
    TestRangeOffOn();
    puts("Testing Fast Mirroring RANGE ON/OFF");
    TestFastMirror(); 
    puts("Testing Fast Bits On count");
    TestFastCountOn(); 
 
    return EXIT_SUCCESS; 
}
/****************TEST FUNCTIONS*****************************************/
static void TestBitsAllOnOff(void)
{
    bits_arr_t bits = 0; 
    printf("All Zeros\n"); 
    BitsArrPrint(bits); 
    printf("\nOnes\n");
    BitsArrAllOn(&bits); 
    BitsArrPrint(bits);
}

static void TestSetBitOnOff(void)
{
    unsigned int i = 0; 
    bits_arr_t bits = 0; 
    
    puts("All Zeros\n");
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        BitsArrSetBit(&bits,i, 1); 
        BitsArrPrint(bits);
        printf("\n");
    }
    
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        BitsArrSetBit(&bits,i, 0); 
        BitsArrPrint(bits);
        printf("\n");
    }
}

static void TestSetBits(void)
{   
    unsigned int i = 0;
    bits_arr_t bits = 0; 
    puts("All Zeros"); 
    BitsArrPrint(bits);  
    puts("\nPut Ones");
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        BitsArrSetOn(&bits,i); 
        BitsArrPrint(bits);
        printf("\n");
    }
    puts("Remove Ones");
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        BitsArrSetOff(&bits,i); 
        BitsArrPrint(bits);
        printf("\n");
    }
}
static void TestIsOnOff(void)
{
    unsigned int i = 0;
    bits_arr_t bits = 0xffffffff; 
    BitsArrPrint(bits); 
    
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        printf("bit number : %u is on(1)/off(0)  %d \n", i, BitsArrIsOn(&bits, i));
    }
}
static void TestFlipBits(void)
{
    unsigned int i = 0;
    bits_arr_t bits = 0xffffffff; 
    
    BitsArrPrint(bits);
    printf("Flip All: \n");
    BitsArrFlipAll(&bits);
    BitsArrPrint(bits);
    printf("\nFlip One by one: \n");
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        BitsArrFlip(&bits, i); 
        BitsArrPrint(bits);
        printf("\n");
    }
}

static void TestRotateBitArr(void)
{
    unsigned int i = 0; 
    bits_arr_t bits = 0x1; 
    printf("Original Numbers \n");
    BitsArrPrint(bits); 
    printf("\nRotate Left \n");
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        BitsArrRotateLeft(&bits, 1); 
        BitsArrPrint(bits);
        printf("\n");
    }
    
    printf("Rotate Right \n");
    for (i = 0; i < BIT_ARR_BITS_NUM; ++i)
    {
        BitsArrRotateRight(&bits, 1); 
        BitsArrPrint(bits);
        printf("\n");
    }
}

static void TestMirror(void)
{   
    bits_arr_t bits = 1; 
    unsigned int i = 0; 
    
    for (i = 50; i < 60; ++i)
    {
        puts("\nOriginal Number:");
        BitsArrPrint(bits); 
        puts("\nMirrored Number:");
        BitsArrMirror(&bits);
        BitsArrPrint(bits);
        bits = (unsigned long)i;   
    }
}

static void TestCountOnOff(void)
{
    bits_arr_t bits = 1; 
    unsigned int i = 0; 
    
    for (i = 50; i < 60; ++i)
    {
        puts("\nOriginal Number:");
        BitsArrPrint(bits); 
        printf("# bits on : %d\n", BitsArrCountOn(&bits));
        printf("# bits off : %d:", BitsArrCountOff(&bits));
        bits = (unsigned long)i;   
    }    
}

static void TestRangeOffOn(void)
{
    bits_arr_t bits = 0xff;
    int end = 42, start = 14;
    
    puts("\nOriginal Number:");
    BitsArrPrint(bits); 
    puts("\nSET ON FROM 14 TO 42:");
    BitsArrSetRangeOn(&bits, start, end);
    BitsArrPrint(bits); 
    puts("\nSET OFF FROM 14 TO 42:");
    BitsArrSetRangeOff(&bits, start, end);
    BitsArrPrint(bits);
    puts("\nSET ON FROM 56 TO 60:");
    BitsArrSetRangeOn(&bits, 56, 60);
    BitsArrPrint(bits);
}

static void TestFastMirror(void)
{   
    bits_arr_t bits = 1; 
    unsigned int i = 0; 
    
    for (i = 50; i < 60; ++i)
    {
        puts("\nOriginal Number:");
        BitsArrPrint(bits); 
        puts("\nMirrored Number:");
        BitArrFastMirror(&bits);
        BitsArrPrint(bits);
        bits = (unsigned long)i;   
    }
}

static void TestFastCountOn(void)
{
    bits_arr_t bits = 1; 
    unsigned int i = 0; 
    
    for (i = 50; i < 60; ++i)
    {
        puts("\nOriginal Number:");
        BitsArrPrint(bits); 
        printf("# bits on : %d\n", BitArrFastCountOn(&bits));
        bits = (unsigned long)i;   
    }    
}


