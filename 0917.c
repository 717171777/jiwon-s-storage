#include <stdio.h>

int main(void)
{
    int i;
    int ecnt=0;
    int a[10]={3,7,8,9,2,3,4,6,1,7};

    for (i=0; i<10; i=i+1) {
        if (a[i] % 2 == 0){
            ecnt = ecnt +1;
        }
    }
    printf("There are %d even numbers in a[10]/n", ecnt);

    return 0;
}