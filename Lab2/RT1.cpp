#include<iostream>
#include<math.h>
#include<stdio.h>
using namespace std;
double fun(double x)
{
	return (100 / pow(x, 2)*sin(10 / x));  /*�޸Ĵ˴����Ըı䱻������*/
}
double integral(double a, double b, int n)
{
	double sum, step, result;
	int i;
	sum = (fun(a) + fun(b)) / 2;
	step = (b - a) / n; /*���ֲ���*/
	for (i = 1; i < n; i++)
		sum = sum + fun(a + i*step);
	result = sum*step;
	return result;/*���ػ���ֵ*/
}
void main() {
	double result;
	result = integral(1.0, 3.0, 1873);/*�޸Ĵ˴����Ըı���������޺Ͳ���*/
	printf("result=%f\n", result);
	system("pause");
}