#include <stdio.h>
#include <math.h>

#define MAXN 4
double fun(double x)
{
	return pow(x,4);
}

double poly(double c[], double x)
{
	double ans = 0;
	for (int i = MAXN; i >= 0; i--)
		ans = ans*x + c[i];
	return ans;
}

int main()
{
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	double x[MAXN];
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n;i++)
	{
		scanf("%lf", &x[i]);
	}
	
	double l[MAXN][MAXN],r[MAXN];
	for (int i = 0; i < n; i++)
	{
		int top = 0;
		double c[MAXN];
		for (int j = 0; j < n; j++)
			if (j != i)
			{
			c[top++] = x[j];
			}
		l[i][0] = -c[0] * c[1] * c[2];
		l[i][1] = c[0] * c[1] + c[0] * c[2] + c[1] * c[2];
		l[i][2] = -(c[0] + c[1] + c[2]);
		l[i][3] = 1;
		r[i] = 1;
		for (int j = 0; j < MAXN - 1; j++)
			r[i] *= (x[i] - c[j]);
	}
	
	double ret[MAXN] = {0};
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			ret[i] += l[j][i] * fun(x[j]) / r[j];
		printf("%lf ", ret[i]);
	}
		

}