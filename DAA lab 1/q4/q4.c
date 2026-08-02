#include <stdio.h>

void toh(int n, char source, char auxillary, char destination)
{
    if(n==1)
    {
        printf("Move disk 1 from %c to %c\n",source,destination);
        return;
    }

    toh(n-1,source,destination,auxillary);
    printf("Move disk %d from %c to %c\n",n,source,destination);
    toh(n-1,auxillary,source,destination);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d",&n);

    toh(n,'A','B','C');

    return 0;
}
