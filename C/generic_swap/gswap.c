#include<stdio.h>
#include<string.h>
#include<malloc.h>

void swap(void *p1, void *p2, int size)
{
	int i = 0;
	char *t1 = p1, *t2=p2;
	while(i < size) {
		t1[i] = t1[i] ^ t2[i]; 
		t2[i] = t1[i] ^ t2[i]; 
		t1[i] = t1[i] ^ t2[i]; 
		i++;
	}
}

int main()
{
	int x1 = 5;
	int x2 = 7;
	double y1 = 1.0;
	double y2 = 42.0;
	char *s1 = strdup("John");
	char *s2 = strdup("Marry");
	printf("x1=%d, x2=%d\n", x1, x2);
	printf("y1=%f, y2=%f\n", y1, y2);
	printf("s1=%s, s2=%s\n", s1, s2);
	swap(&x1, &x2, sizeof(int));
	swap(&y1, &y2, sizeof(double));
	swap(&s1, &s2, sizeof(char*));
	printf("x1=%d, x2=%d\n", x1, x2);
	printf("y1=%f, y2=%f\n", y1, y2);
	printf("s1=%s, s2=%s\n", s1, s2);
	free(s1);
	free(s2);
	return 0;
}
