#include <stdio.h>
#include <math.h>

#define MAX_m 200
#define MAX_n 5

double f1(double x)
{
	return sin(x);
}

double f2(double x)
{
    return exp(x);
}

double Polynomial(int n, double c[], double x)
{
	double ans=0;
	for (int i = n-1; i >=0; i--)
    {
		ans = ans*x + c[i];
    }
	return ans;
}
double InnerProduct2(int m, double w[], double x[], double(*f1)(double x))
{
	double ans = 0;
	for (int i = 0; i < m; i++)
	{
		ans += w[i] * f1(x[i])*f1(x[i]);
	}
	return ans;
}

double InnerProduct1(int m, double w[], double c[], double x[], double(*f1)(double x), double(*f2)(int n, double c[],double x))
{
	double ans = 0;
	for (int i = 0; i < m; i++)
	{
		ans += w[i] * f1(x[i])*f2(m, c, x[i]);
	}
	return ans;
}

double InnerProduct(int m,double w[],double c1[],double c2[],double x[], double(*f1)(int n, double c[], double x), double(*f2)(int n, double c[], double x))
{
	double ans = 0;
	for (int i = 0; i < m;i++)
	{
		ans += w[i] * f1(m,c1,x[i])*f2(m,c2,x[i]);
	}
	return ans;
}

int OPA(double(*f)(double t), int m, double x[], double w[], double c[], double *eps)
{
	for (int i = 0; i < MAX_n + 1;i++)
	{
		c[i] = 0;
	}
	double phi[MAX_n+1][MAX_m] = {0};
	phi[0][0]= 1;
	double a = InnerProduct1(m, w, phi[0], x, f, Polynomial) /InnerProduct(m, w, phi[0], phi[0], x, Polynomial, Polynomial); //(phi0,y)/(phi0,phi0)
	c[0] = a;
	double err = InnerProduct2(m, w, x,f) - a*InnerProduct1(m, w, phi[0], x, f, Polynomial); //(y,y)-a0(phi0,y)
	double temp[MAX_m] = {0};
	temp[1] = 1;
	double bk = InnerProduct(m, w, temp, phi[0], x, Polynomial, Polynomial) / InnerProduct(m, w, phi[0], phi[0], x, Polynomial, Polynomial); //(xphi0,phi0)/(phi0,phi0);
	phi[1][0] = -bk; 
	phi[1][1] = 1;
	a = InnerProduct1(m, w, phi[1], x, f, Polynomial) / InnerProduct(m, w, phi[1], phi[1], x, Polynomial, Polynomial); //a=(phi1,y)/(phi1,phi1)
	for (int i = 0; i < 2; i++)
		c[i] += a*phi[1][i];	//P(x)+=a1*phi1
	err -= a*InnerProduct1(m, w, phi[1], x, f, Polynomial);//err-=a1(phi1,y)

	int k = 1;
	while (k < MAX_n && fabs(err) >= *eps)
	{
		k++;
		double temp[MAX_m] = {0};
		for (int i = 0; i < k; i++)
			temp[i + 1] = phi[k - 1][i];
		bk = InnerProduct(m, w, temp, phi[k-1], x, Polynomial, Polynomial) / InnerProduct(m, w, phi[k-1], phi[k-1], x, Polynomial, Polynomial); //(xphik-1,phik-1)/(phik-1,phik-1);
		double ck = InnerProduct(m, w, temp, phi[k - 2], x, Polynomial, Polynomial) / InnerProduct(m, w, phi[k - 2], phi[k - 2], x, Polynomial, Polynomial); //(xphik-1,phik-2)/(phik-2,phik-2);
		for (int i = 0; i < k+1; i++)
			phi[k][i] = temp[i] - bk*phi[k - 1][i] - ck*phi[k - 2][i];	//phi=
		a = InnerProduct1(m, w, phi[k], x, f, Polynomial) / InnerProduct(m, w, phi[k], phi[k], x, Polynomial,Polynomial); //a=(phik,y)/(phik,phik)
		for (int i = 0; i < k + 1; i++)
			c[i] += a*phi[k][i];
		err -= a*InnerProduct1(m, w, phi[k], x, f, Polynomial);//err-=a1(phi1,y)
	}
	*eps = err;
	return k;
}

void print_results(int n, double c[], double eps)
{
    int i;

    printf("%d\n", n);
    for (i = 0; i <= n; i++)
        printf("%12.4e ", c[i]);
    printf("\n");
    printf("error = %9.2e\n", eps);
    printf("\n");
}

int main()
{
	freopen("1.out", "w", stdout);
	int m, i, n;
	double x[MAX_m], w[MAX_m], c[MAX_n + 1], eps;

	m = 90;
	for (i = 0; i < m; i++) {
		x[i] = 3.1415926535897932 * (double)(i + 1) / 180.0;
		w[i] = 1.0;
	}
	eps = 0.001;
	n = OPA(f1, m, x, w, c, &eps);
	print_results(n, c, eps);

	m = 200;
	for (i = 0; i < m; i++) {
		x[i] = 0.01*(double)i;
		w[i] = 1.0;
	}
	eps = 0.001;
	n = OPA(f2, m, x, w, c, &eps);
	print_results(n, c, eps);

	return 0;
}