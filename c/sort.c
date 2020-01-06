static void TestRadixSort(void)
{
    struct timeval start           = {0};
    struct timeval end             = {0};
    int radix_arr[Q_SIZE]  = {0};
    int half_sorted[Q_SIZE] = {0};    

    FillArray(radix_arr, Q_SIZE); 
    FillArray(half_sorted, Q_SIZE); 
    puts ("\nRADIX Timing: \n");
    gettimeofday(&start, NULL);
    RadixSort(radix_arr, Q_SIZE);
    gettimeofday(&end, NULL);
    printf("Randomly arr time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );
    
    RadixSort(half_sorted, Q_SIZE/2);
    gettimeofday(&start, NULL);
    RadixSort(half_sorted, Q_SIZE);
    gettimeofday(&end, NULL);
    printf("half sorted sort time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );

    gettimeofday(&start, NULL); 
    RadixSort(half_sorted, Q_SIZE);    
    gettimeofday(&end, NULL);
    printf("sorted sort time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );

}

static void TestCounting(void)
{
    struct timeval start           = {0};
    struct timeval end             = {0};
    static int select_arr[Q_SIZE] = {0};
    static int half_sorted[Q_SIZE] = {0};    

    FillArray(select_arr, Q_SIZE); 
    FillArray(half_sorted, Q_SIZE); 
    puts ("\nCounting Timing: \n");
    gettimeofday(&start, NULL); 
    CountingSort(select_arr, Q_SIZE);
    gettimeofday(&end, NULL); 
    printf("Randomly arr time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );
    
    CountingSort(half_sorted, Q_SIZE/2); 
    gettimeofday(&start, NULL); 
    CountingSort(half_sorted, Q_SIZE);
    gettimeofday(&end, NULL);
    printf("Randomly arr time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );
    gettimeofday(&start, NULL); 
    CountingSort(select_arr, Q_SIZE);    
    gettimeofday(&end, NULL);
    printf("Randomly arr time : %1.4f[sec]\n ", ((float)(end.tv_usec - start.tv_usec)/1000000) );
    
    printf("is sorted ? : %d\n", IsSorted(select_arr, Q_SIZE));
}

