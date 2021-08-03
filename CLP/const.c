#include <stdio.h>

int main(void) {
	
    //case 1
    //assign directly
    const int n1 = 2;
	n1++; //compiler error
	
    //case 2
    //modify througth a pointer
    const int n2 = 2;
	int *p = &n2; //compiler warning
	(*p)++;

    //case 3
    //all element of const array are const
    const int t[2] = {1,2};
	t[0] = 1; //compiler error
    *(t + 0) = 1; //compiler error

    //case 4
    //const structure, all fields are const
    const struct { int x,y; } as = {1.2}, bs = {3, 4};
	as.x++; //compiler error
    as.y--; //compiler error
    bs = a; //compiler error

    //case 5
    //pointer to a const qualified variable
    //both equivalent
    //int const *p = &a;
    //const int *p = &a;
    int a = 1, b = 2;
	int const *p = &a;
	a++;
	(*p)++; //compiler error
	p = &b;

    //case 6
    //const pointer to variable
    int a = 1, b = 2;
	int *const p = &a;
	a++;
	(*p)++;//compiler error
	p = &b;

    //case 7
    //const pointer to const variable
    int a = 1, b = 2;
	int const *const p = &a;
	a++;
	(*p)++; //compiler error
    p = &b; //compiler error

    //more 5,6 and 7
    char str[] = "string";
	char const *s1 = str; //pointer to const
	char * const s2 =str; //const pointer to variable
	char const * const s3 = str; //const pointer to const variable
	s1[1] = 'S';
	s2[2] = 'S';
	s3[3] = 'S';
	printf("%s %s %s\n", s1, s2, s3);
	s1 = "1";
	s2 = "2"; s3 = "3";
	printf("%s %s %s\n", s1, s2, s3);

    //case 8
    //non const pointers should not be assigned with pointers to const variables.
    int const v = 1;
	const *p = &v; //compiler warning

    //case 9
    //pointer to a non const variable may be assigned to const pointers
    int v = 1;
	const int *p = &v; //ok

	return 0;
}