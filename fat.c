#include <stdio.h>
double fatorial (double d);;

int main (){
    int x; 
    double fat;
    scanf ("%d", &x);

    fat = fatorial (x);
    printf ("%lf", fat);
    return 0;
}

double fatorial (double d) {
    double fat = 1;

    do {
        fat = fat * d;
        d--;
    } while (d > 1);
    return fat;
}