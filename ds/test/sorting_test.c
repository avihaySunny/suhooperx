/*******************************************************************************
* Programmer: Avihay Asraf
* sorting_test.c
* File: sorting testing
* Date: ב' יונ 10 11:47:17 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <time.h>           /* time                                     */
#include <sys/time.h>       /* timeval                                  */  

#include "sorting.h" 

/*-----------------------------------------------------------*/
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define Q_SIZE (1550)
#define RANGE (2500)
typedef struct student
{
    char name[50]; 
    size_t age; 
    int id; 

} stu_t; 

static stu_t students[] =   {{"frank"  , 20, 1000   }, 
                            {"frankosh", 25, 1001   }, 
                            {"frakish", 21, 1002    },
                            {"frankolo", 27, 1003   },
                            {"frakeyla", 26, 1004   },
                            {"frakoshov", 22, 1005  },
                            {"frankoski", 20, 1006  },
                            {"mistyfranks", 29, 1007},
                            {"walkmyway", 21, 1008  },
                            {"andbegintoplay", 24, 1009},
                            {"andbegintoplay", 24, 1010}, 
                            {"andbegintoplay", 24, 1011}, 
                            {"andbegintoplay", 24, 1012}, 
                            {"frakoshish", 26, 1013}};
                            
/*-----------------------------------------------------------*/
static void FillArray(int *arr, size_t size);   /*fills an array with random numbers */
static void TestSort(void(sort_func(int*, size_t)), char *name);
static void TestQSort(void); 
static int IsSmaller(const void *a, const void *b); /*cmp func for qsort */
static int IsBigger(const void *a, const void *b); /*cmp func for qsort*/
static int CmpData(const void *dataA, const void *dataB);
static int CmpDataInt(const int *dataA, const int *dataB);
static float RealTimeDiff(struct timeval *a, struct timeval *b); /*Calcs differencs of two times */ 
static int IsSorted(int *arr, size_t size);
static void TestMyQsort(void);
static void TestBinarySearchTrivial(void);
static void TestBinarySearch(void);
static int CmpStudentId(const void *stuA, const void *stuB);
static int CmpStudentIdWrapped(const stu_t *stuA, const int *stuB);
static void TestMyQsortRandom(void);
/*-----------------------------------------------------------*/

int main(void)
{
    TestSort(InsertionSort, "Insertion"); 
    TestSort(BubbleSort, "Bubble"); 
    TestSort(SelectionSort, "Selection"); 
    TestSort(RadixSort, "Radix");
    TestQSort(); 
    TestMyQsort();
    TestMyQsortRandom();
    TestBinarySearchTrivial();  
    TestBinarySearch();

    return (EXIT_SUCCESS);
}

static void TestSort(void(sort_func(int*, size_t)), char *name)
{
    struct timeval start           = {0};
    struct timeval end             = {0};
    static int arr[Q_SIZE]  = {0};
    static int half_sorted[Q_SIZE] = {0};    

    FillArray(arr, Q_SIZE); 
    FillArray(half_sorted, Q_SIZE); 
    printf(CYAN"\n%s timing\n"RESET, name);
    gettimeofday(&start, NULL);
    sort_func(arr, Q_SIZE);
    gettimeofday(&end, NULL);
    printf("Randomly arr time : %1.4f[sec]\n ", RealTimeDiff(&start, &end));
    
    sort_func(half_sorted, Q_SIZE/2);
    gettimeofday(&start, NULL);
    sort_func(half_sorted, Q_SIZE);
    gettimeofday(&end, NULL);
    printf("half sorted sort time : %1.4f[sec]\n ", RealTimeDiff(&start, &end));

    gettimeofday(&start, NULL); 
    sort_func(half_sorted, Q_SIZE);    
    gettimeofday(&end, NULL);
    printf("sorted sort time : %1.4f[sec]\n ", RealTimeDiff(&start, &end));

    qsort(arr, Q_SIZE, sizeof(int), IsSmaller);
    gettimeofday(&start, NULL); 
    sort_func(arr, Q_SIZE);
    gettimeofday(&end, NULL);
    printf("sorted sort time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );
    printf("Is Sorted? %d\n", IsSorted(half_sorted, Q_SIZE));
}

static void TestQSort(void)
{
    struct timeval start    = {0};
    struct timeval end      = {0};
    int select_arr[Q_SIZE]  = {0};
    int half_sorted[Q_SIZE] = {0};    

    FillArray(select_arr, Q_SIZE); 
    FillArray(half_sorted, Q_SIZE); 
    puts ("\nQuicksort Timing: \n");
    gettimeofday(&start, NULL);
    qsort(select_arr, Q_SIZE, sizeof(int), IsBigger);
    gettimeofday(&end, NULL);
    printf("Randomly arr time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );
    
    qsort(half_sorted, Q_SIZE/2, sizeof(int), IsBigger);
    gettimeofday(&start, NULL);
    qsort(half_sorted, Q_SIZE, sizeof(int), IsBigger);
    gettimeofday(&end, NULL);
    printf("half sorted sort time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );

    gettimeofday(&start, NULL); 
    qsort(half_sorted, Q_SIZE, sizeof(int), IsBigger);    
    gettimeofday(&end, NULL);
    printf("reverse sorted sort time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );
    printf("Is Sorted %d\n", IsSorted(half_sorted, Q_SIZE));
}

static void FillArray(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);
    
    for (i = 0; i < size; ++i)
    {
        arr[i] = rand() % RANGE; 
    }
}

static int IsBigger(const void *a, const void *b)
{   
    assert(a && b); 
    return  (*(int*)a > *(int*)b);
}

static int IsSmaller(const void *a, const void *b)
{
    assert(a && b);
    return (*(int*)a < *(int*)b);
}

static float RealTimeDiff(struct timeval *a, struct timeval *b) /*returns seconds*/
{
    assert(a && b);
    return (((b->tv_sec*1e6 + b->tv_usec) - (a->tv_sec *1e6 + a->tv_usec)) / 1000000);
}

static int IsSorted(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);

    for (i = size - 1; i > 0 ; --i)
    {
        if (arr[i] < arr[i - 1])
        {
            return 0; 
        }
    }

    return 1; 
}

static void TestMyQsort(void)
{   
    int arr[] = { 41 , 1, 21, 34,  41, 39,22, 17,  25, 42, 56, 8, 34, 37, 64, 22, 81, 442, 54, 23};
    size_t size =  sizeof(arr)/sizeof(arr[0]);
    FillArray(arr, size); 
    QSort(&arr, size, sizeof(int), IsBigger);
    if(!IsSorted(arr, size))
    {
        puts ("QSort failed");
    } 
}   

static void TestBinarySearchTrivial(void)
{
    int arr[] = {1, 4, 7, 9, 17, 19, 26, 21, 29, 31};
    size_t size =  sizeof(arr)/sizeof(arr[0]);
    int found = 1; 
    int not_found = 12; 
    int *found_data_ptr = NULL; 
    void *not_found_ptr = NULL; 
    
    found_data_ptr = BinarySearch(&arr, size, sizeof(int), &found, CmpData); 
    not_found_ptr = BinarySearch(&arr, size, sizeof(int), &not_found, CmpData);
    
    if (*found_data_ptr != found)
    {
        puts ("BSearch Error"); 
    }
    if (not_found_ptr != NULL)
    {
        puts ("BSearch Error");
    } 
}

static void TestBinarySearch(void)
{
    stu_t *found_stu = NULL; 
    size_t stu_size = sizeof(students) / sizeof(students[0]);

    int id_to_be_found = 1009;
    int id_not_in_list = 1100;  

    found_stu = BinarySearch(&students, stu_size, sizeof(stu_t), &id_to_be_found, CmpStudentId); 
    if (found_stu == NULL)
    {
        puts ("error BSearch Recursive");
    }
    
    found_stu = BinarySearchIter(&students, stu_size, sizeof(stu_size), &id_not_in_list, CmpStudentId);
    if (NULL != found_stu)
    {
        puts ("Bsearch iterative failed ");
    }
}

static int CmpData(const void *dataA, const void *dataB)
{
    return CmpDataInt(dataA, dataB); 
}

static int CmpDataInt(const int *dataA, const int *dataB)
{
    int res = *dataA - *dataB; 
    if (res > 0)
    {
        return 1;
    }
    else if (res < 0)
    {
        return -1;
    } 
    else
    {
        return 0;
    } 
}

static int CmpStudentId(const void *stuA, const void *stuB)
{
    return CmpStudentIdWrapped(stuA, stuB);
}

static int CmpStudentIdWrapped(const stu_t *stuA, const int *stuB)
{
    return stuA->id - *stuB;
}

#if 0
void PrintStudent(stu_t *student)
{
    printf("name : %s \n", student->name); 
    printf("age : %ld \n", student->age); 
    printf("id %d\n", student->id); 
}
#endif

static void TestMyQsortRandom(void)
{   
    int arr[Q_SIZE] = {0};
    size_t size =  sizeof(arr)/sizeof(arr[0]);
    FillArray(arr, Q_SIZE);
    QSort(&arr, size, sizeof(int), IsBigger);
    if (!IsSorted(arr, size ))
    {
        puts ("Qsort failed");
    }
}   
