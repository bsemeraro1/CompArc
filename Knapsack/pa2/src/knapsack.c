#include<stdio.h>


int maximum(int a, int b) { return (a > b)? a : b; }
int knapSack(int W, int wt[], int val[], int n)

{

   int i, w;

   int K[n+1][W+1];

   for (i = 0; i <= n; i++)

   {

       for (w = 0; w <= W; w++)

       {

           if (i==0 || w==0)

               K[i][w] = 0;

           else if (wt[i-1] <= w)

                 K[i][w] = maximum(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);

           else

                 K[i][w] = K[i-1][w];

       }
   }

   return K[n][W];

}

int main()

{

    int i, n, val[20], wt[20], W;

    

    printf("Number of items INTEGER:"); //Input the number of items for the knapsack

    scanf("%d", &n);

    

    printf("Weight Value of items INTEGER:\n"); //Input the weights and values of the items 

    for(i = 0;i < n; ++i){

     scanf("%d%d", &val[i], &wt[i]);

    }

    printf("Size of knapsack INTEGER:"); //Enter the size of the knapsack

    scanf("%d", &W);
    printf("%d", knapSack(W, wt, val, n));

    return 0;

}