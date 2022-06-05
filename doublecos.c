#include <stdio.h>
#define EPS_COS 0.000001
#define PI 3.14159

double cosseno (double theta, double epsilon);
double fatorial (double d);
double potencia (double e, int pot);

int main () {
    double graus, cosx;

    printf ("Graus\n");
    scanf ("%lf", &graus);

    cosx = cosseno (graus, EPS_COS);

    printf ("%lf", cosx);
    return 0;
}

double fatorial (double d) {
    double fat = 1;
    do { fat = fat * d; d--;} while (d > 1);
    return fat;
}

double potencia (double e, int pot) {
    int i, cont = 0; double pote = 1;
    while (cont != pot) { pote = pote * e; cont ++;}
    return pote;
}

double cosseno (double theta, double epsilon) {
    double cosx = 0, fat = 0, sinal = 1, rad, n = 1, d = 1, termo = 0, parar = 0, compara;

    rad = (PI * theta) / 180;

    while (parar != 1) {
        termo = (n / d) * sinal;
        n = potencia (rad, 2); fat = fat + 2; d = fatorial (fat), rad = n;

        if (termo < 0 ) compara = -termo;
        else compara = termo;
        if (compara < epsilon) parar = 1;
        else {
            cosx = cosx + termo; sinal = -sinal;
        }
    }
    cosx = cosx + termo;
    return cosx;
}
