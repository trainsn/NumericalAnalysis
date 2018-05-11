#include <stdio.h>

#define MAX_SIZE 10

double abs(double x)
{
    return x > 0 ? x : -x;
}
void swap(double *x, double* y)
{
    double temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int GetMax(int n, double x[])
{
    int index = 0;
    double max = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(x[i])>max)
        {
            max = abs(x[i]);
            index = i;
        }
    }
    return index;
}

int Solve(int n, double a[][MAX_SIZE], double x[],double y[]) //get the right y for a certain x
{
    for (int i = 0; i < n; i++)
    {
        double max = a[i][i];
        int index = i;
        for (int j = i; j < n; j++)
        {
            if (abs(a[j][i]) > max)
            {
                max = abs(a[j][i]);
                index = j;
            }
        }
        if (abs(max) < 1e-8)
            return -1;
        if (index != i)
        {
            for (int j = 0; j < n; j++)
                swap(&a[index][j], &a[i][j]);
            swap(&x[index], &x[i]);
        }

        for (int j = i + 1; j < n; j++)
        {
            x[j] -= x[i] * a[j][i] / a[i][i];
            for (int k = n-1; k >= i; k--)
            {
                a[j][k] -= a[i][k] * a[j][i] / a[i][i];
            }   
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        y[i] = x[i];
        for (int j = i + 1; j < n; j++)
            y[i] -= a[i][j] * y[j];
        y[i] /= a[i][i];
    }
    return 0;
}

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN)
{
    double err;
    double tVec[MAX_SIZE];

    int p = GetMax(n, v);
    double vp = v[p];
    for (int i = 0; i < n; i++)
        v[i] = v[i] / vp;
    for (int num = 0; num < MAXN; num++)
    {                 
        double temp[MAX_SIZE][MAX_SIZE];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
            if (i == j)
                temp[i][j] = a[i][j] - *lambda;
            else
                temp[i][j] = a[i][j];
            }
        
        double y[MAX_SIZE],x[MAX_SIZE];
        for (int i = 0; i < n; i++)
            x[i] = v[i];
        int ret=Solve(n, temp, x, y);
        if (ret == -1)
            return -1;
        double u = y[p];
        p = GetMax(n, y);

        double yp = y[p];
        for (int i = 0; i < n; i++)
            tVec[i] = v[i] - y[i] / yp;
        int errIndex=GetMax(n, tVec);
        err = abs(tVec[errIndex]);
        for (int i = 0; i < n; i++)
            v[i] = y[i] / yp;
        if (err < TOL)
        {
            u = 1 / u + *lambda;
            *lambda = u;
            return 1;
        }          
    }
    return 0;
}

int main()
{
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
    int n, MAXN, m, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], v[MAX_SIZE];
    double lambda, TOL;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &a[i][j]);
    scanf("%lf %d", &TOL, &MAXN);
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%lf", &lambda);
        for (j = 0; j < n; j++)
            scanf("%lf", &v[j]);
        switch (EigenV(n, a, &lambda, v, TOL, MAXN)) {
        case -1:
            printf("%12.8f is an eigenvalue.\n", lambda);
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        case 1:
            printf("%12.8f\n", lambda);
            for (k = 0; k < n; k++)
                printf("%12.8f ", v[k]);
            printf("\n");
            break;
        }
    }

    return 0;
}