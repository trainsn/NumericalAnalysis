#include <stdio.h>

#define Max_size 10 /* max number of dishes */

void Price(int n, double p[])
{   
    //思路：手动分解原系数矩阵为准上三角阵和准下三角阵（需要手动解方程组），然后通过初等矩阵变换转为上三角和下三角阵，即可利用追赶法获得最后的答案
    //程序中的注意点：初等矩阵变换的时候增广矩阵的最后端也需要变换，由于犯了这个低级错误导致调了两节逻辑课。
    double l[2][2];
    const double sm = 0.2679491924;
    l[0][0] = 1.866025404;
    l[0][1] = 0;
    l[1][0] = 0.5; //li,i-1
    l[1][1] = 1.866025404;//li,i   (2+sqrt(3))/2
    double root =1;
    for (int i = n-1; i >= 1; i--)
    {
        root *= -sm;      //1/(2+sqrt(3))
        p[0] += root*p[i];
    }
        
    l[0][0] += 0.5*root;    

    double z[Max_size + 10] = { 0 };
    z[0] = p[0] / l[0][0];
    for (int i = 1; i < n; i++)
        z[i] = (p[i] - l[1][0] * z[i - 1]) / l[1][1];

    double u[2][2];
    u[0][0] = 1;    //ui,i
    u[0][1] = sm; //ui,i+1
    u[1][0] = 0;
    u[1][1] = 1;
    root = 1;
    for (int i = 0; i < n - 1; i++)
    {
        root *= -sm;  //2-sqrt(3)
        z[n - 1] += z[i] * root;
    }

    u[1][1] += root*sm;

    p[n - 1] = z[n - 1] / u[1][1];
    for (int i = n - 2; i >= 0; i--)
    {
        p[i] = z[i] - p[i + 1] * u[0][1];
    }    
}

int main()
{
    int n, i;
    double p[Max_size];

    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%lf", &p[i]);
    Price(n, p);
    for (i = 0; i < n; i++)
        printf("%.2lf ", p[i]);
    printf("\n");

    return 0;
}
