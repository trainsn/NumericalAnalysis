#include <stdio.h>
#include <math.h>
int main()
{
	double a,b;
	b = 3.188777;
	a = 0.372382;
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	int n;
	double x[10], y[10];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &x[i]);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &y[i]);
	}
	
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		double temp = b*exp(x[i] * a)-y[i];
		sum += temp*temp;
	}
	printf("%lf", sum);
		
}
