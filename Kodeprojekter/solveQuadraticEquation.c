#include <stdio.h>
#include <math.h>

void solveQuadraticEquation(double a, double b, double c);
double Discriminant (double a, double b, double c);
double Root1 (double a, double b, double discriminant);
double Root2 (double a, double b, double discriminant);

int main(void) {
  double a = 1.0, b = -8.0, c = 15.0,
         d = 2.0, e =  8.0, f =  2.0,
         g, h, i;

  /* First call - coefficents are values of variables */
  solveQuadraticEquation(a, b, c);  

  /* Second call - coefficents are values of expressions */
  solveQuadraticEquation(d - 1, -e, 7 * f + 1); 

  while(g != 0 && h != 0 && i != 0)
  {
    /* Third call - coefficents are entered by user outside solveQuadraticEquation */
    printf("Enter coeficients a, b, and c: ");
    scanf("%lf %lf %lf", &g, &h, &i);
    solveQuadraticEquation(g, h, i);  
  }
  return 0;
}

/* Prints roots of the quadratic equation a * x*x + b * x + c = 0 */
void solveQuadraticEquation(double a, double b, double c){
  double discriminant, root1, root2;

  discriminant = Discriminant(a, b, c);
  printf("%d", discriminant);

  if (discriminant < 0)
    printf("No roots\n");
  else if (discriminant == 0){
    root1 = -b/(2*a);
    printf("One root: %f\n", root1);
  }
  else {
    root1 = Root1(a, b, discriminant);
    root2 = Root1(a, b, discriminant);
    printf("Two roots: %f and %f\n", root1, root2);
  }

}

//calculates the discriminant
double Discriminant (double a, double b, double c){
    return b * b - 4 * a * c;
}

//calculates root1
double Root1 (double a, double b, double discriminant){
    return (-b + sqrt(discriminant))/(2*a);
}

//calculates root1
double Root2 (double a, double b, double discriminant){
    return (-b - sqrt(discriminant))/(2*a);
}