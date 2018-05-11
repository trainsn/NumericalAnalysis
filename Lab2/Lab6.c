#include <stdio.h>

#define MAX_N 10

void TriLinearSystem(int n,double a[][MAX_N], double x[], double y[])
{
    double l[MAX_N][MAX_N] = { 0 }, u[MAX_N][MAX_N] = { 0 }, z[MAX_N] = { 0 };
    l[0][0] = a[0][0];
    u[0][1] = a[0][1] / l[0][0];
    z[0] = y[0] / l[0][0];
    
    for (int i = 1; i < n; i++)
    {
        l[i][i - 1] = a[i][i - 1];
        l[i][i] = a[i][i] - l[i][i - 1] * u[i - 1][i];
        u[i][i + 1] = a[i][i + 1] / l[i][i];
        z[i] = (y[i] - l[i][i - 1] * z[i - 1]) / l[i][i];
    }

    x[n - 1] = z[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        x[i] = z[i] - u[i][i + 1] * x[i + 1];
    }
}

void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[])
{
    double A[MAX_N][MAX_N] = { 0 }, h[MAX_N] = { 0 }, y[MAX_N] = { 0 };
    for (int i = 0; i <= n; i++)
    {
        a[i] = f[i];
        b[i] = c[i] = d[i] = 0;
    }
        
    for (int i = 0; i < n; i++)
    {
        h[i] = x[i + 1] - x[i]; //step
    }
    
    //配置系数
    if (Type == 1) // s'(x0)=s0
    {
        A[0][0] = 2*h[0];
        A[0][1] = h[0];
        
        A[n][n - 1] = h[n - 1];
        A[n][n] = 2 * h[n - 1];
        y[0] = 3 / h[0] * (a[1] - a[0]) - 3 * s0;
        y[n] = 3 * sn - 3 / h[n - 1] * (a[n] - a[n - 1]);

    }
    else if (Type == 2) //s''(x0)=s0
    {
        A[0][0] = 2;
        A[n][n] = 2;
        y[0] = s0; y[n] = sn;    
    }
    for (int i = 1; i < n; i++)
    {
        A[i][i-1] = h[i - 1];
        A[i][i] = 2 * (h[i - 1] + h[i]);
        A[i][i + 1] = h[i];
    }
    for (int i = 1; i < n; i++)
    {
        y[i] = 3 / h[i] * (a[i + 1] - a[i]) - 3 / h[i - 1] * (a[i] - a[i - 1]);
    }
    
    //solve tri linear system
    TriLinearSystem(n+1, A, c, y); //最后一个点就是因为这里开始打了n所以没过去
    for (int i = 0; i < n; i++)
    {
        b[i] = (a[i + 1] - a[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3;
        d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
    }

    for (int i = n; i > 0; i--)
    {
        a[i] = a[i - 1];
        b[i] = b[i - 1];
        c[i] = c[i - 1];
        d[i] = d[i - 1];
    }
}

double S(double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[])
{
    for (int i = 0; i < n; i++)
    {
        if (x[i] <= t && x[i+1] >= t)
        {
            return a[i+1] + b[i+1] * (t - x[i]) + c[i+1] * (t - x[i])*(t - x[i]) + d[i+1] * (t - x[i])*(t - x[i])*(t - x[i]);
        }
    }
    return Fmax;
}

int main()
{
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
    
    int n, Type, m, i;
    double x[MAX_N], f[MAX_N], a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
    double s0, sn, Fmax, t0, tm, h, t;

    scanf("%d", &n);
    for (i = 0; i <= n; i++)
        scanf("%lf", &x[i]);
    for (i = 0; i <= n; i++)
        scanf("%lf", &f[i]);
    scanf("%d %lf %lf %lf", &Type, &s0, &sn, &Fmax);

    Cubic_Spline(n, x, f, Type, s0, sn, a, b, c, d);
    for (i = 1; i <= n; i++)
        printf("%12.8e %12.8e %12.8e %12.8e \n", a[i], b[i], c[i], d[i]);

    scanf("%lf %lf %d", &t0, &tm, &m);
    h = (tm - t0) / (double)m;
    for (i = 0; i <= m; i++) {
        t = t0 + h*(double)i;
        printf("f(%12.8e) = %12.8e\n", t, S(t, Fmax, n, x, a, b, c, d));
    }

    return 0;
}
