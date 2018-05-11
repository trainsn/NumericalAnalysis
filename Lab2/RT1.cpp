#include<iostream>
#include<math.h>
#include<stdio.h>
using namespace std;
double fun(double x)
{
	return (100 / pow(x, 2)*sin(10 / x));  /*修改此处可以改变被积函数*/
}
double integral(double a, double b, int n)
{
	double sum, step, result;
	int i;
	sum = (fun(a) + fun(b)) / 2;
	step = (b - a) / n; /*积分步长*/
	for (i = 1; i < n; i++)
		sum = sum + fun(a + i*step);
	result = sum*step;
	return result;/*返回积分值*/
}
void main() {
	double result;
	result = integral(1.0, 3.0, 1873);/*修改此处可以改变积分上下限和步长*/
	printf("result=%f\n", result);
	system("pause");
}