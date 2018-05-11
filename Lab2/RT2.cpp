#include "stdio.h" 
#include "math.h" 
#include <stdlib.h>
int count = 1;
double f(double x)
{

	return (100 / pow(x, 2)*sin(10 / x));

}
double inte1(double a, double b, double h)
{
	return 0.5*h*(f(a) + f(b));//ÌÝÐÎ¹«Ê½  
}
double inte(double a, double b, double h, double acc, double S)
{
	double L, R;
	count++;
	L = inte1(a, b - h / 2, h / 2);
	R = inte1(b - h / 2, b, h / 2);

	if (abs(L + R - S) <= acc)
		return L + R;
	else{

		return inte(a, a + h / 2, h / 2, acc / 2, L) + inte(a + h / 2, b, h / 2, acc / 2, R);
	}

}

void main()
{
	double d = inte(1.0, 3.0, 2, 0.002, inte1(1.0, 3.0, 2));
	printf("%lf\n", d);
	printf("%d", count);
	system("pause");
}