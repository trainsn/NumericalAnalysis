#include <stdio.h>
#include <math.h>

double f0(double x, double l, double t)
{
	return sqrt(1.0 + l*l*t*t*cos(t*x)*cos(t*x));
	//return sin(x);
}

double Integral(double a, double b, double(*f)(double x, double y, double z),
	double eps, double l, double t)
{
	double r[25][25] = {0};
	double h = b - a;
	r[0][0] = (f0(a,l,t) + f0(b,l,t))*h / 2;
	int pow2 = 1;
	int i;
	for (i = 1;i<=20; i++)
	{
		
		r[i][0] = r[i - 1][0];
		for (int j = 1; j <= pow2; j++)
		{
			double x = a + (j - 0.5)*h;
			r[i][0] += h*f0(x, l, t);
		}
		pow2 *= 2;
			
		r[i][0] /= 2;
		
		double pow4 = 1;
		for (int j = 1; j <= i; j++)
		{
			pow4 *= 4;
			r[i][j] = r[i][j - 1] + (r[i][j - 1] - r[i - 1][j - 1]) / (pow4 - 1);
		}	
		h /= 2;
// 		if (fabs(r[i - 1][i - 1] - r[i][i]) < eps && fabs(r[i - 1][i - 1] - r[i - 2][i - 2]) < eps)
// 			break;
	}
	return r[i-1][i-1]/100;
}

int main()
{
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	double a = 0.0, b, eps = 0.005, l, t;

	scanf("%lf %lf %lf", &l, &b, &t);
	printf("%.2f\n", Integral(a, b, f0, eps, l, t));

	return 0;
}