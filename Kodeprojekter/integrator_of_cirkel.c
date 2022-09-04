#include <stdio.h>
#include <math.h>

double integrator (double (*function)(double x), double a, double b, double n);
double g (double x);
double h (double x);

int main(void) {
    double a = 0, b = 3.14159;

    for (int n = 2; n <=128; n = n*2){
        printf("%f\n", integrator(&g, a, b, n));
    }
    a = -2;
    b = 2;
    printf("\n");

    for (int n = 2; n <=128; n = n*2){
        printf("%f\n", integrator(&h, a, b, n));
    }
}

double g (double x){
    return x*x * sin(x);
}

double h (double x){
    return sqrt(4-x*x);
}

double integrator (double (*function)(double x), double a, double b, double n){
    double h = (b-a)/n, c = 0;


    for (double d = 1; d <= n - 1; d++)
        c += function(a + h * d);

    return h/2 * (function(a) + function(b) + 2 * c);
}