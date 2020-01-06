static void VSAMerge(block_t *block, ssize_t needed_size, block_t *end);

static void VSAMerge(block_t *block, ssize_t needed_size, block_t *end)
{
    block_t *next = NULL; 
     
    needed_size -= block->free_mem; 
    next = NextBlock(block);
    
    while ((next <= end) && (next->free_mem > 0) && (needed_size >= 0))
    {
        needed_size -= next->free_mem; 
        block->free_mem = block->free_mem + next->free_mem + sizeof(block_t);     
        next = NextBlock(next);
    }
    
}

void PrintAllocs(vsa_t *vsa)
{
    block_t *runner = (block_t*)vsa;
    size_t i = 0;  
    
    while (VSAEnd(vsa) >= runner)
    {
        puts("--------------");
        printf("block number : %ld\n", i);
        printf("address :%ld\n", (size_t)runner);
        printf("free_mem:%ld\n", runner->free_mem); 
        runner = NextBlock(runner);
        ++i;
    }
}

size_t VSAAvailableSpace(vsa_t *vsa)
{
   block_t *runner = (block_t*)vsa; 
   size_t avail = ((vsa_t*)((size_t)vsa - sizeof(vsa_t)))->overall_size; 
   while (VSAEnd(vsa) >= runner)
   {
        avail = avail + (runner->free_mem) * (runner->free_mem < 0); 
        runner = NextBlock(runner);
   }
   
   return avail;
}

static int TestVSAFree(void)
{
    size_t buf_size = 2000; 
    size_t i = 0; 
    void *space = malloc(buf_size); 
    void *vec[50] = {NULL}; 
    void *tmp = NULL; 
    vsa_t *vsa = NULL; 
    size_t *mem = NULL; 
    memset(space, 0, buf_size);
    vsa = VSAInit(space, buf_size);

    for (i = 0; i < 50; ++i)
    {
        vec[i] = VSAAlloc(vsa, rand() % 35);
    }
    
    for (i = 0; i < 25; ++i)
    {
        VSAFree(vec[rand() % 50]);
   
    }
    
    tmp = VSAAlloc(vsa, 100);
    
    for (i = 0; i < 50; ++i)
    {
        mem = (size_t*)((size_t)vec[i] - sizeof(size_t));   
    }
    
    free(space);
}
