#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define  MAXN  10
double f(int j,double t, double y,double y1)
{
	if (j == 0)
		return y1;
	else
		return (t*t*t*log(t) + 2 * t*y1 - 2 * y) / (t*t);
// 	if (j == 0)
// 		return y1;
// 	else
// 		return exp(2 * t)*sin(t) - 2 * y + 2 * y1;
}

double exact(double t)
{
	return 1.75*t + pow(t, 3) / 2 * log(t) - 0.75*pow(t, 3);
}

int main()
{
	double h, a, b;
	double ini[MAXN] = {0};
	double w[12][2] = { 0 }, k[5][3] = {0};

	int m = 2;
	a = 1; b = 2;
	h = 0.1;
	w[0][0] = 1; w[0][1] = 0;
	int n = (int)(b - a) / h;
	printf("%10d%10lf%10lf%10lf%10lf\n",0, a, w[0][0], w[0][1],exact(a));
	
	for (int i = 1; i <= 3; i++)
	{
		double t = a + h*(i-1);
		for (int j = 0; j < m; j++)
			k[1][j] = h*f(j, t, w[i-1][0], w[i-1][1]);
		for (int j = 0; j < m; j++)
			k[2][j] = h*f(j, t + h / 2, w[i-1][0] + k[1][0] / 2, w[i-1][1] + k[1][1] / 2);
		for (int j = 0; j < m; j++)
			k[3][j] = h*f(j, t + h / 2, w[i-1][0] + k[2][0] / 2, w[i-1][1] + k[2][1] / 2);
		for (int j = 0; j < m; j++)
			k[4][j] = h*f(j, t+h, w[i-1][0] + k[3][0], w[i-1][1] + k[3][1]);
		for (int j = 0; j < m; j++)
			w[i][j] = w[i-1][j] + (k[1][j] + 2 * k[2][j] + 2 * k[3][j] + k[4][j]) / 6;
		printf("%10d%10lf%10lf%10lf%10lf\n", i, t + h, w[i][0], w[i][1], exact(t+h));
	}
	
	for (int i = 4; i <= n; i++)
	{
		double t = a + i*h;
		for (int j = 0; j < m; j++)
		{
			w[i][j] = w[i-1][j]+h*(55 * f(j, t - h, w[i - 1][0], w[i - 1][1]) - 59 * f(j, t - 2 * h, w[i - 2][0], w[i - 2][1]) + 37 * f(j, t - 3 * h, w[i - 3][0], w[i - 3][1]) - 9 * f(j, t - 4 * h, w[i - 4][0], w[i - 4][1]))/24;
		}
		for (int j = 0; j < m; j++)
		{
			w[i][j] = w[i - 1][j] + h*(9 * f(j, t, w[i][0], w[i][1])+19 * f(j, t - h, w[i - 1][0], w[i - 1][1]) - 5 * f(j, t - 2 * h, w[i - 2][0], w[i - 2][1]) +  f(j, t - 3 * h, w[i - 3][0], w[i - 3][1]))/24;
		}
		printf("%10d%10lf%10lf%10lf%10lf\n", i, t, w[i][0], w[i][1], exact(t));
	}
	system("pause");
}