#include <stdio.h>

int partitionPoint(int arr[], int n)
{
    int low = 0;
    int high = n - 1;

    while(low <= high)
    {
        int mid = (low + high) / 2;

        if(arr[mid] == 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}

int main()
{
    int arr[] = {0,0,0,0,0,1,1,1,1};
    int n = sizeof(arr)/sizeof(arr[0]);

    int index = partitionPoint(arr,n);

    printf("Partition Point = %d\n", index);

    return 0;
}