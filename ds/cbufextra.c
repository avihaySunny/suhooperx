
ssize_t CBufWrite(cbuf_t *cb, const void *src, size_t nbytes)
{
    size_t overhead = 0;
    size_t available = 0;

    assert(cb);
    assert(src);

    overhead = cb->end - cb->writer;
    available = CBufGetFreeSpace(cb);
    
    if (0 == available)
    {
        return (-1);
    }

    if (nbytes > available)
    {
        nbytes = available;
        DBG(perror("EOVERFLOW");)
    }
    
    if ((cb->reader > cb->writer) ||                            
       ((cb->writer > cb->reader) && (nbytes <= overhead)) ||
       (CBufIsEmpty(cb) && (nbytes <= overhead))) 
    {
        memcpy(cb->writer, src, nbytes);
        cb->writer = cb->writer + nbytes;   
    }
    else
    {
        memcpy(cb->writer, src, overhead);
        cb->writer = cb->data;
        
        memcpy(cb->writer, (char*)src + overhead, nbytes - overhead);
        cb->writer = cb->writer + (nbytes - overhead);
    }
    
    if ((cb->writer == cb->reader + 1) && (available == nbytes ))
    {
        cb->reader = cb->reader + 2;
    }
    
    return (nbytes);    
}



    
    /*
    if ((cb->reader > cb->writer) ||                            
       ((cb->writer > cb->reader) && (nbytes <= overhead)) ||
       (CBufIsEmpty(cb) && (nbytes <= overhead))) 
    {
        memcpy(cb->writer, src, nbytes);
        cb->writer = cb->writer + nbytes;   
    }
    else
    {
        memcpy(cb->writer, src, overhead);
        cb->writer = cb->data;
        
        memcpy(cb->writer, (char*)src + overhead, nbytes - overhead);
        cb->writer = cb->writer + (nbytes - overhead);
    }
    */
    
ssize_t CBufRead(cbuf_t *cb,void *dest, size_t nbytes)
{
    size_t overhead = 0;
    size_t available = 0;
    
    assert(cb);
    assert(dest);
    
    overhead = cb->end - cb->reader;                        
    available = CBufGetCapacity(cb) - CBufGetFreeSpace(cb); /*available to read*/
    
    if (CBufIsEmpty(cb))
    {
        DBG(perror("ENDODATA");)
        
        return (-1);
    }
    
    if(nbytes > available)
    {
        nbytes = available - 1; 
    }

    if ((cb->reader < cb->writer) || 
       ((cb->writer < cb->reader) && (overhead > nbytes)))
    {
        memcpy(dest, cb->reader, nbytes);
        cb->reader = cb->reader + nbytes;
    }
    
    else
    {
        memcpy(dest, cb->reader, overhead);
        cb->reader = cb->data;
        memcpy((char *)dest + overhead, cb->reader, nbytes - overhead);
        cb->reader = cb->reader + nbytes - overhead;
    }
    
    if (cb->reader == cb->writer)
    {
        --cb->reader;
    }
    
    return (nbytes);
}

static void DLSort(void)
{
    static int arr[20] = {0};
    int i = 0; 
    dlist_t *list = DLCreate(); 
    int max = 50;
    
    if (NULL == list)
    {
        return; 
    }
    
    for (i = 0; i < 50; ++i)
    {
        arr[i] = rand()%100; 
        DLPushFront(list, &arr[i]);
    }
    
    DLPushFront(list, &max);
    DLPrint(list); 
    puts("--------------------------"); 
    DLBubbleSort(list);
    DLPrint(list);
    DLDestroy(list);
    /*DLPushFront()*/
}

/*
static int DLCmpData(void *dataA, void* dataB)
{
    return (*(int*)dataA > *(int*)dataB);
}

void DLBubbleSort(dlist_t *list) 
{
    dlist_iter_t runner = NULL; 
    dlist_iter_t sec_runner = NULL; 
    
    assert(list);
    
    runner = DLBegin(list);
    sec_runner = DLBegin(list);
    
    while (DLEnd(list) != DLNext(sec_runner))
    {
        runner = DLBegin(list); 
        while (DLEnd(list) != DLNext(runner))
        {
            if (*(int*)DLGetData(runner) > *(int*)DLGetData(DLNext(runner)))
            {
                DLSwapData(&runner->data, &runner->next->data);
            }
            
            runner = DLNext(runner);
        }
        
        sec_runner = DLNext(sec_runner);
    }
}
*/
    
