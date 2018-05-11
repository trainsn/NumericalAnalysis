#include <stdio.h>
#include <math.h>

#define  MAXN 10
int main(void)
{
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	int n;
	double x[MAXN], y[MAXN];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &x[i]);
		x[i] = log(x[i]);
		printf("%lf ", x[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &y[i]);
		y[i] = log(y[i]);
		printf("%lf ", y[i]);
	}
	return 0;
}