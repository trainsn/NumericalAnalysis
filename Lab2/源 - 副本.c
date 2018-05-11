#include <stdio.h>
#include <math.h>

#define MAXN 10
#define DEG 1


void swap(double *x, double* y)
{
	double temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int Solve(int n, double a[][MAXN], double x[], double y[]) //get the right y for a certain x
{
	for (int i = 0; i < n; i++)
	{
		double max = a[i][i];
		int index = i;
		for (int j = i; j < n; j++)
		{
			if (fabs(a[j][i]) > max)
			{
				max = fabs(a[j][i]);
				index = j;
			}
		}
		if (fabs(max) < 1e-8)
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
			for (int k = n - 1; k >= i; k--)
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

double fun(double c[], double x)
{
	double ans = 0;
	for (int i = DEG; i >= 0; i--)
		ans = ans*x + c[i];
	return ans;
}

int main()
{
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	int n;
	double x[10], y[10],b[(DEG+1)*2],c[(DEG+1)*2];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &x[i]);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &y[i]);
	}
	for (int i = 0; i <= DEG * 2; i++)
	{
		double sumb = 0,sumc=0;
		for (int j = 0; j < n; j++)
		{
			sumb += pow(x[j], i);
			sumc += pow(x[j], i)*y[j];
		}
		b[i] = sumb;
		c[i] = sumc;
		printf("%lf %lf\n", sumb, sumc);
	}

	double a[MAXN][MAXN];
	for (int i = 0; i <= DEG; i++)
		for (int j = 0; j <= DEG; j++)
		{
		a[i][j] = b[i + j];
		}
	double ans[DEG + 1] = { 0 };
	Solve(DEG + 1, a, c, ans);
	for (int i = 0; i <= DEG; i++)
		printf("%lf\n", ans[i]);

	double err = 0;
	for (int i = 0; i < n; i++)
	{
		double temp = fun(ans, x[i])-y[i];
		err += temp*temp;
	}
	printf("%lf", err);

	return 0;
}