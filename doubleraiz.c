#include <stdio.h>
#define EPS 0.01
double raiz (double x, double epsilon);

 int main () {
     int n;
     double raizx, epsilon = 0.01;

     printf ("valor de n\n");
     scanf ("%d", &n);
     /*se x é diferente de 0*/

     raizx = raiz (n, EPS);
     printf ("%lf", raizx);
     return 0;
 }

 double raiz (double x, double epsilon) {
    int i;
    double rant = x;

    if (x < EPS) return 0;
    else {
    for (i = 0; i < 10; ++i)
          rant = rant/2 + x/(2*rant);
    }      
    return rant;  
 }