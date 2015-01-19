#include<stdio.h>
#include<string.h>
#include<malloc.h>


void *lsearch(void *key,
              void *base,
	      int n,
	      int elemSize,
	      int (*cmpfn)(void *, void *))
{
	int i = 0;
	for (i = 0; i < n; i++) {
		void *elem = (char*)base + i * elemSize;
		if (cmpfn(key, elem) == 0) return elem;
	}
	return NULL;
}

int IntCmp(void *p1, void *p2) 
{
	int *ip1 = p1, *ip2 = p2;
	return *ip1 - *ip2;
}

int main()
{
	int arr[] = { 4, 3, 1, 5, 7, 8, 9, 2 };	
	int n = 8;
	int key = 8;
	int res = *(int*)lsearch(&key, arr, n, sizeof(int), &IntCmp);
	printf("%d\n", res);		
	key = 6;
	void *res2 = lsearch(&key, arr, n, sizeof(int), &IntCmp);
	if (NULL == res2) 
		printf("True!");	
	return 0;
}
