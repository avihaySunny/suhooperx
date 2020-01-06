
#include <stdio.h>
#include <dlfcn.h> 

#define SHARED_LIB1 ("/home/student/git/ds/obj/libso1.so")
#define SHARED_LIB2 ("/home/student/git/ds/obj/libso2.so")

void foo(void); 

int main (void)
{
	
	void (*test_bar)(void) = NULL;
	void *hand1 = dlopen(SHARED_LIB1, RTLD_LAZY); 
	if (NULL == hand1)
	{
		printf("NO");
	}
	
	test_bar = dlsym(hand1, "Bar1");
	 
	if (test_bar == NULL)
	{
		printf("HELL\n");
	}  
	
	test_bar(); 
	foo();
	printf("foo 	: %p\n", foo);
	printf("handler : %p\n", test_bar); 
	puts("");
	
	hand1 = dlopen(SHARED_LIB2, RTLD_LAZY); 
	if (NULL == hand1)
	{
		printf("NO2");
	}
	
	test_bar = dlsym(hand1, "Bar2");
	test_bar();
	if (test_bar == NULL)
	{
		printf("HELL2\n");
	}  
	
	printf("dynamic lib : %p\n", test_bar); 
	
	dlclose(hand1); 
	return (0);
}






