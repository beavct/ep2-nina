#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 /*zona de alerta*/
#define DELTA_ALARME 60
#define EPS_COS 0.000001 /*precisão para o cálculo de cosseno*/
#define EPS 0.01 /*precisão para os valores contendo metro*/

double velocidade (double x0, double y0, double x1, double y1, double deltaT);
int iguais (double x, double y);
double cosseno (double theta, double epsilon);
double fatorial (double d);
double potencia (double e, int pot);
double distancia (double H, double cos);
double raiz (double x, double epsilon);
int localiza (double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv);

int main () {
    double x0, y0, x1, y1, tempo, Vmedia;

    printf ("coordenadas iniciais, finais e tempo\n");
    scanf ("%lf %lf %lf %lf %lf", &x0, &y0, &x1, &y1, &tempo);

    Vmedia = velocidade (x0, y0, x1, y1, tempo);
    printf ("%lf", Vmedia);

    return 0;
}

double velocidade (double x0, double y0, double x1, double y1, double deltaT) {
    double velocidade, deltaS2, deltaS;

    deltaS2 = potencia ((x1 - x0), 2) + potencia ((y1 - y0), 2);
    deltaS = raiz (deltaS2, EPS);

    velocidade = deltaS / deltaT;

    if (velocidade < 0) velocidade = -velocidade;

    return velocidade;
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