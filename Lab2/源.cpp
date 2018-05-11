#include <stdio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define  MAXN  10

// double f(int j, double t, double y, double y1)
// {
// 	if (j == 0)
// 		return y1;
// 	else
// 		return (t*t*t*log(t) + 2 * t*y1 - 2 * y) / (t*t);
// 	// 	if (j == 0)
// 	// 		return y1;
// 	// 	else
// 	// 		return exp(2 * t)*sin(t) - 2 * y + 2 * y1;
// }

double f(int j, double t, double y, double y1, double y2)
{
	if (j == 0)
		return y1;
	else if (j == 1)
		return y2;
	else
		return (5*pow(t,3)*log(t)+9*pow(t,3)+t*t*y2-3*t*y1-4*y)/pow(t,3);
}

double exact(double t)
{
	return -t*t + t*cos(log(t)) + t*sin(log(t)) + pow(t, 3)*log(t);
}

int main()
{
	double h, a, b;
	double ini[MAXN] = { 0 };
	double w[20][3] = { 0 }, k[5][3] = { 0 };

	int m = 3;
	a = 1; b = 2;
	h = 0.1;
	w[0][0] = 0; w[0][1] = 1; w[0][2] = 3;
	int n = (int)(b - a) / h;
	printf("%10d%20lf%20lf%20lf%20lf%20lf\n", 0, a, w[0][0], w[0][1],w[0][2], exact(a));

	for (int i = 1; i <= 3; i++)
	{
		double t = a + h*(i - 1);
		for (int j = 0; j < m; j++)
			k[1][j] = h*f(j, t, w[i - 1][0], w[i - 1][1],w[i-1][2]);
		for (int j = 0; j < m; j++)
			k[2][j] = h*f(j, t + h / 2, w[i - 1][0] + k[1][0] / 2, w[i - 1][1] + k[1][1] / 2, w[i - 1][2] + k[1][2] / 2);
		for (int j = 0; j < m; j++)
			k[3][j] = h*f(j, t + h / 2, w[i - 1][0] + k[2][0] / 2, w[i - 1][1] + k[2][1] / 2, w[i - 1][2] + k[2][2] / 2);
		for (int j = 0; j < m; j++)
			k[4][j] = h*f(j, t + h, w[i - 1][0] + k[3][0], w[i - 1][1] + k[3][1], w[i - 1][2] + k[3][2]);
		for (int j = 0; j < m; j++)
			w[i][j] = w[i - 1][j] + (k[1][j] + 2 * k[2][j] + 2 * k[3][j] + k[4][j]) / 6;
		printf("%10d%20lf%20lf%20lf%20lf%20lf\n", i, t + h, w[i][0], w[i][1], w[i][2], exact(t + h));
	}

	for (int i = 4; i <= n; i++)
	{
		double t = a + i*h;
		for (int j = 0; j < m; j++)
		{
			w[i][j] = w[i - 1][j] + h*(55 * f(j, t - h, w[i - 1][0], w[i - 1][1], w[i - 1][2]) - 59 * f(j, t - 2 * h, w[i - 2][0], w[i - 2][1], w[i - 2][2]) + 37 * f(j, t - 3 * h, w[i - 3][0], w[i - 3][1], w[i - 3][2]) - 9 * f(j, t - 4 * h, w[i - 4][0], w[i - 4][1], w[i - 4][2])) / 24;
		}
		for (int j = 0; j < m; j++)
		{
			w[i][j] = w[i - 1][j] + h*(9 * f(j, t, w[i][0], w[i][1], w[i][2]) + 19 * f(j, t - h, w[i - 1][0], w[i - 1][1], w[i - 1][2]) - 5 * f(j, t - 2 * h, w[i - 2][0], w[i - 2][1], w[i - 2][2]) + f(j, t - 3 * h, w[i - 3][0], w[i - 3][1], w[i - 3][2])) / 24;
		}
		printf("%10d%20lf%20lf%20lf%20lf%20lf\n", i, t, w[i][0], w[i][1],w[i][2], exact(t));
	}
	system("pause");
}