#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i;
    int fairHeads = 0, biasedHeads = 0;

    printf("Enter number of tosses: ");
    scanf("%d", &n);

    srand(time(NULL));

    // Fair coin
    for(i = 0; i < n; i++)
    {
        if(rand() % 2 == 1)
            fairHeads++;
    }

    // Biased coin (70% Heads)
    for(i = 0; i < n; i++)
    {
        if(rand() % 100 < 70)
            biasedHeads++;
    }

    printf("\nFair Coin\n");
    printf("Heads = %d\n", fairHeads);
    printf("Probability = %.3f\n", (float)fairHeads/n);

    printf("\nBiased Coin\n");
    printf("Heads = %d\n", biasedHeads);
    printf("Probability = %.3f\n", (float)biasedHeads/n);

    return 0;
}