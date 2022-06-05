#include <stdio.h>
#define EPS_COS 0.000001
#define EPS 0.01
#define PI 3.14159

int iguais (double x, double y);
double cosseno (double theta, double epsilon);
double fatorial (double d);
double potencia (double e, int pot);
double distancia (double H, double cos);
int localiza (double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv);

int main () {
    double xi, yi, xj, yj, xk, yk;
    double Hi, Hj, Hk;
    double thetai, thetaj, thetak;
    double div, djv, dkv;
    double xv, yv;

    printf ("(x,y), comprimento H e angulo theta (i, j, k)\n");
    scanf ("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &xi, &yi, &Hi, &thetai, &xj, &yj, &Hj, &thetaj, &xk, &yk, &Hk, &thetak);

    div = distancia (Hi, thetai); 
    djv = distancia (Hj, thetaj);
    dkv = distancia (Hk, thetak);

    localiza (xi, yi, div, xj, yj, djv, xk, yk, dkv, &xv, &yv);

    printf ("(%.2f, %.2f)", xv, yv);
    return 0;
}

double distancia (double H, double theta){
    double dist;
    dist = H * cosseno (theta, EPS);
    return dist;
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
        n = potencia (rad, 2); fat = fat + 2; d = fatorial (fat);

        if (termo < 0 ) compara = -termo;
        else compara = termo;
        if (compara < epsilon) parar = 1;
        else {
            cosx = cosx + termo; sinal = -sinal;
        }
    }
    return cosx;
}

double fatorial (double d) {
    double fat = 1;
    do { fat = fat * d; d--;} while (d > 1);
    return fat;
}

int iguais (double x, double y) {
    if (x - y < EPS && y - x < EPS ) return 1;
    else return 0;
}

int localiza (double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv) {
    double P1, P2, Q1, Q2; 

    if (iguais(xi, xj) == 0 && iguais(xi, xk) == 0) { /*usa ij e ik*/
        P1 = ((xi *xi) - (xj * xj) + (yi * yi) - (yj * yj) - (div *div) + (djv * djv)) / (2 * (xi - xj)); 
        Q1 = (yj - yi) / (xi - xj);

        P2 = ((xi *xi) - (xk * xk) + (yi * yi) - (yk * yk) - (div *div) + (dkv * dkv)) / (2 * (xi - xk)); 
        Q2 = (yk - yi) / (xi - xk);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    else if (iguais(xj, xi) == 0 && iguais(xj, xk)) { /*usa ji e jk*/
        P1 = ((xj *xj) - (xi * xi) + (yj * yj) - (yi * yi) - (djv *djv) + (div * div)) / (2 * (xj - xi)); 
        Q1 = (yi - yj) / (xj - xi);

        P2 = ((xj *xj) - (xk * xk) + (yj * yj) - (yk * yk) - (djv *djv) + (dkv * dkv)) / (2 * (xj - xk)); 
        Q2 = (yk - yj) / (xj - xk);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    else if (iguais(xk, xi) == 0 && iguais(xk, xj) == 0) { /*usa ki, kj*/
        P1 = ((xk *xk) - (xi * xi) + (yk * yk) - (yi * yi) - (dkv *dkv) + (div * div)) / (2 * (xk - xi)); 
        Q1 = (yi - yk) / (xk - xi);

        P2 = ((xk *xk) - (xj * xj) + (yk * yk) - (yj * yj) - (dkv *dkv) + (djv * djv)) / (2 * (xk - xj)); 
        Q2 = (yj - yk) / (xk - xj);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    else if (iguais (xi, xj) && (xi, xk)) { /*impossível calcular a posição*/
        return 0;
    }
    else { 
        P1 = ((xi *xi) - (xj * xj) + (yi * yi) - (yj * yj) - (div *div) + (djv * djv)) / (2 * (xi - xj)); 
        Q1 = (yj - yi) / (xi - xj);

        P2 = ((xi *xi) - (xk * xk) + (yi * yi) - (yk * yk) - (div *div) + (dkv * dkv)) / (2 * (xi - xk)); 
        Q2 = (yk - yi) / (xi - xk);

        *yv = (P2 - P1) / (Q1 - Q2);
        *xv = P1 + (Q1 * *yv);
    }
    return 1;
}