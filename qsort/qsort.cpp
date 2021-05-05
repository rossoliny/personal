#include <cstdlib>


#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int partition (int* arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    int t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;

    return (i + 1);
}

void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char** argv) {

    int sz = -1;
    printf("Enter size of array:\n");
    scanf("%d", &sz);
    int arr[sz];

    srand(time(NULL));
    for (int i = 0; i < sz; ++i)
    {
    	arr[i] = rand() % (sz * 20);
    }

    clock_t begin = clock();
    quickSort(arr, 0, sz - 1);
    clock_t end = clock();

    printf("Time taken: %f seconds\n", ((double) (end - begin)) / CLOCKS_PER_SEC);

    return 0;
}
