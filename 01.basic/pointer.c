#include <stdio.h>

int swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(void)
{
    int a, b;
    printf("Enter two numbers: ");
    scanf_s("%d %d",&a, &b);
    swap(&a, &b);
     printf("a=%d b=%d\n", a, b);
    return 0;
}
