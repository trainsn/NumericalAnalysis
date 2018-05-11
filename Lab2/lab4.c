#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
#define bound pow(2.0, 127)
#define ZERO 1e-9 /* X is considered to be 0 if |X|<ZERO */

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

int JudgeMatrix(int n,double a[][MAX_SIZE])
{
    double b[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i][j] = a[i][j];
    
    for (int i = 0; i < n; i++)
    {
        int flag = -1;
        for (int j = i; j < n; j++)
        {
            if (fabs(b[j][i]) > ZERO)
            {
                flag = j;
                break;                 
            }
        }
        if (flag == -1)
            return 0;
        else
        {
            for (int j = 0; j < n; j++)
                swap(&b[i][j], &b[flag][j]);
        }

        for (int j = i + 1; j < n; j++)
            for (int k = n - 1; k >= 0; k--)
            {
            b[j][k] -= b[i][k] * b[j][i] / b[i][i];
            }                
    }
    return 1;
}

void TransMatrix(int n, double a[][MAX_SIZE], double b[])
{
    for (int i = 0; i < n; i++)
    {
        double maxRow = fabs(a[i][i]);
        int flag = i;
        for (int j = i; j < n; j++)
        {
            if (fabs(a[j][i]) > maxRow)
            {
                maxRow = fabs(a[j][i]);
                flag = j;
            }
        }
        if (maxRow>ZERO&&flag > i)
        {
            for (int j = 0; j < n; j++)
            {
                swap(&a[i][j], &a[flag][j]);
            }
            swap(&b[i], &b[flag]);
        }
        else if (maxRow < ZERO)
        {
            maxRow = fabs(a[0][i]);
            flag = 0;
            for (int j = 0; j < i; j++)
            {
                if (fabs(a[j][i]) > maxRow)
                {
                    maxRow = fabs(a[j][i]);
                    flag = j;
                }
            }
            if (maxRow>ZERO)
            {
                for (int j = 0; j < n; j++)
                {
                    a[i][j] += a[flag][j];
                }
                b[i] += b[flag];
            }
        }
    }
}

int Jacobi(int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN)
{
    if (JudgeMatrix(n, a) == 0)
        return -1;
    TransMatrix(n, a, b); 

    double y[MAX_SIZE] = { 0 };
    int k = 1;
    while (k <= MAXN)
    {
        for (int i = 0; i < n; i++)
        {
            y[i] = b[i]/a[i][i];
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    y[i] -= x[j] * a[i][j]/a[i][i];
                }
            }
            if (fabs(y[i]) > bound)
                return -2;
        }

        //judge if this method has succeed
        double max = 0;
        for (int i = 0; i < n; i++)
        {
            if (fabs(y[i] - x[i])>max)
                max = fabs(y[i] - x[i]);
        }
        if (max < TOL)
        {
            return k;
        }
            
        
        for (int i = 0; i < n; i++)
            x[i] = y[i];
        k++;        
    }
    return 0;
}

int Gauss_Seidel(int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN)
{
    if (JudgeMatrix(n, a) == 0)
        return -1;
    TransMatrix(n, a, b);

    int k = 1;
    while (k <= MAXN)
    {
        double max = 0;
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    sum += a[i][j] * x[j];
                }
            }
            double temp = (b[i] - sum) / a[i][i];
            if (fabs(temp - x[i])>max)
                max = fabs(temp - x[i]);
            x[i] = temp;
            if (fabs(x[i]) > bound)
                return -2;
        }
        if (max < TOL)
            return k;

        k++;
    }
    return 0;
}

int main()
{
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
    int n, MAXN, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE];
    double TOL;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &b[i]);
    }
    scanf("%lf %d", &TOL, &MAXN);

    printf("Result of Jacobi method:\n");
    for (i = 0; i < n; i++)
        x[i] = 0.0;
    k = Jacobi(n, a, b, x, TOL, MAXN);
    switch (k) {
    case -2:
        printf("No convergence.\n");
        break;
    case -1:
        printf("Matrix has a zero column.  No unique solution exists.\n");
        break;
    case 0:
        printf("Maximum number of iterations exceeded.\n");
        break;
    default:
        printf("no_iteration = %d\n", k);
        for (j = 0; j < n; j++)
            printf("%.8f\n", x[j]);
        break;
    }
    printf("Result of Gauss-Seidel method:\n");
    for (i = 0; i < n; i++)
        x[i] = 0.0;
    k = Gauss_Seidel(n, a, b, x, TOL, MAXN);
    switch (k) {
    case -2:
        printf("No convergence.\n");
        break;
    case -1:
        printf("Matrix has a zero column.  No unique solution exists.\n");
        break;
    case 0:
        printf("Maximum number of iterations exceeded.\n");
        break;
    default:
        printf("no_iteration = %d\n", k);
        for (j = 0; j < n; j++)
            printf("%.8f\n", x[j]);
        break;
    }

    return 0;
}