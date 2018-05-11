#include <stdio.h>
#include <math.h>

#define ZERO 1e-13 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11    /* Max Polynomial Degree + 1 */
double findFunc(int n, double c[], double x)
{
    double temp=c[n];
    for (int i = n - 1; i >= 0; i--)
    {
        temp = temp*x + c[i];
    }
    return temp;
}

double findFirst(int n, double c[], double x)
{
    double temp = 0;
    for (int i = n; i >= 1; i--)
        temp = temp*x + i*c[i];
    return temp;
}

double findSecond(int n, double c[], double x)
{
    double temp = 0;

    for (int i = n; i >= 2; i--)
        temp = temp*x + i*(i - 1)*c[i];
    return temp;
}

int FindRoot(int n, double c[], double a, double b, double EPS, double p0, double *p)
{
    double fp0, dfp0, ddfp0;
    double err;
    int flag = 0;
   
    for (int i = 0; i < 1000;i++)
    {       
        fp0 = findFunc(n, c, p0);
        if (fabs(fp0) < ZERO)
        {
            //*root = p0;
            flag = 1;   //此时不能直接返回，否则有一个点会过不去
            break;
        }

        dfp0 = findFirst(n, c, p0);
        ddfp0 = findSecond(n, c, p0);
        double dino = dfp0 * dfp0 - fp0 * ddfp0;
        if (fabs(dino) < ZERO)
            return 0;
         
        //p = p - fp0 / dfp0;
        *p = p0 - fp0 * dfp0 / dino;
        if (*p<a || *p>b)
            return 0;
        err = fabs(*p - p0);
        if (err < EPS)
        {
            flag = 1;
            break;
        }
        p0 = *p;            
    }
    return flag;
}

double Polynomial_Root(int n, double c[], double a, double b, double EPS)
{
    if (a > b)
    {
        double temp;
        temp = a;
        a = b;
        b = temp;
    }
    
    int step = 5;
    double interval = (b - a) / step;
    double p0,p;
    double min = 9999;
    double ans=0;
    for (int i = 0; i <= step;i++)
    {
        p0 = a + interval*i;
        double flag=FindRoot(n, c, a, b, EPS, p0,&p);
        if (flag==1&&fabs(findFunc(n,c,p)) < min)
        {
            min = fabs(findFunc(n,c,p));
            ans = p;
        }
    }
    return ans;
    
}

int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
    scanf("%d", &n);
    for (i = n; i >= 0; i--)
        scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_Root(n, c, a, b, EPS));
    //system("pause");

    return 0;
    
}
