#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Use: ./mexp file.txt\n");
        return 0;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("The file cannot be opened \n");
        return 0;
    }
    int i, j, k, m, n, times; 
    fscanf(fp, "%d", &n);
    int **res = (int **)malloc(n*sizeof(int *));
    int **M = (int  **)malloc(n * sizeof(int *));
    int ** M1 = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        M1[i] = (int *)malloc(n * sizeof(int));
        res[i] = (int *)malloc(n * sizeof(int));
        M[i] = (int *)malloc(n * sizeof(int));
    }
    for (i = 0; i <n; i++)
    {
    for (j = 0; j < n; j++) 
    {
        
        fscanf(fp, "%d", &M[i][j]);
        M1[i][j] = M[i][j];
        }
    } 
        fscanf(fp, "%d", times);
        for (m = 0; m < times-1; m++)
        {
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++) 
                {
                    res[i][j] = 0;
                    for (k = 0; k < n; k++)
                    res[i][j] += M[i][k] * M1[k][i];
                }
            }
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                M1[i][j] = res[i][j];    
                }
            }
        } 
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
            {
                printf("%d ", res[i][j]);
                {
                    printf("\n");
            }
                fclose(fp);
            }
         
        }

        return 0;
   
}

