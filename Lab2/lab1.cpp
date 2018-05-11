#include <stdio.h>
#include <stdlib.h>

void Series_Sum(double sum[])
{
    double sum_index;
    double j, k;
    int i;
    for (i = 0; i <= 302; i++)  //计算整数时的答案
    {    
        sum_index = 0;
        for (j = 1; j <= i; j++)
        {
            sum_index += 1.0 / j;
        }
        sum[i * 10] = sum_index / i;
    }
    
    double x = 0;
    int n;
    for (i = 0; i < 3001;i++)   //减两次使得精度调高
    {
        if (i==0 || i % 10 != 0)
        {   
            if (i < 2980)
                n = i / 10 + 1;
            else
                n = i / 10 - 1;
            sum_index = 0;
            for ( k = 1; k <= 500; k++)
            {
                sum_index += 1.0 / (k*(k + x)*(k + n)*(k + n + 1)*(k + n + 2));
            }
            sum[i] = (n - x)*((n + 1 - x)*(sum_index*(n + 2 - x) + (sum[n * 10] + sum[n * 10 + 20] - 2 * sum[n * 10 + 10]) / 2) + sum[n * 10] - sum[n * 10 + 10]) + sum[n * 10];
        }
        x += 0.1;
    }
}

int main()
{
    int i;
    double x, sum[3001];

    Series_Sum(sum);

    x = 0.0;
    for (i = 0; i < 101; i++)
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);
    system("pause");
    return 0;
}