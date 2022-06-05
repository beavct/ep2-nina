#include <stdio.h>

double potencia (double e, int pot);

int main (){
    int x, y;
    double pot;
    scanf ("%d %d", &x, &y);
    pot = potencia (x, y);
    printf ("%lf", pot);
    return 0;
}

double potencia (double e, int pot) {
    int i, cont = 0; double pote = 1;
    while (cont != pot) {
        pote = pote * e; cont ++;
    }
    return pote;
}