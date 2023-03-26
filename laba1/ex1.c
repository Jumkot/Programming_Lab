<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>

int* init(int* arr, int n)
{
    arr = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; ++i)
    {
        arr[i] = i;
    }
    return arr;
}

int main()
{
    int n = 10;
    int* arr = NULL;
    arr = init(arr, n);
    
    for (int i = 0; i < n; ++i)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}
||||||| a64f33f
=======
#include <stdio.h>
#include <stdlib.h>

int* init(int* arr, int n)
{
    arr = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; ++i)
    {
        arr[i] = i;
    }
    return arr;
}

int main()
{
    int n = 10;
    int* arr = NULL;
    arr = init(arr, n);
    
    for (int i = 0; i < n; ++i)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}
>>>>>>> origin/main
