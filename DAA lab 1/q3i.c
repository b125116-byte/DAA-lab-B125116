#include <stdio.h>

void bubbleSort(int arr[], int n)
{
    int temp, swapped;
    long comparisons = 0;

    for(int i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    printf("Comparisons = %ld\n", comparisons);
}

int main()
{
    int arr[] = {5,2,9,1,6,3};
    int n = sizeof(arr)/sizeof(arr[0]);

    bubbleSort(arr,n);

    printf("Sorted Array:\n");

    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}