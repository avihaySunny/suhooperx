#include <stdlib.h>

void *ALignedMalloc(size_t bytes, size_t align);
void AlignedFree(void *ptr);

int main()
{
	void *ptr = NULL;
	ptr = ALignedMalloc(10, 4);
	AlignedFree(ptr);

	return 0;
}

void *ALignedMalloc(size_t bytes, size_t align)
{
	char *base = NULL;
	char *result = NULL;

	result = malloc(bytes + align + sizeof(void*));
	if (NULL == result)
	{
		return NULL;
	}
	
	base = result;
	result += sizeof(void*);
	
	result = (char*)(((size_t)(result) + ((align) - 1)) & ~((align) - 1));

	result -= sizeof(void*);
	*(void**)result = base; 

	return result + sizeof(void*);
}

void AlignedFree(void *ptr)
{
	void **tmp = (void**)ptr - 1;

	free(*(void**)tmp);
}
