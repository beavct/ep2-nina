#include <stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 /*zona de alerta*/
#define DELTA_ALARME 60
#define EPS_COS 0.000001 /*precisão para o cálculo de cosseno*/
#define EPS 0.01 /*precisão para os valores contendo metro*/

double dist_percorrida (double xv1, double yv1, double xv2, double yv2);
double dist_origem (double x, double y);
int equaçao_reta (double x0, double y0, double x1, double y1, double *a, double *b, double *c);
double velocidade (double x0, double y0, double x1, double y1, double deltaT);
int iguais (double x, double y);
double cosseno (double theta, double epsilon);
double fatorial (double d);
double potencia (double e, int pot);
double distancia (double H, double cos);
double raiz (double x, double epsilon);
int localiza (double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv);
int intercepta (double x0, double y0, double x1, double y1, double *x, double *y);

int main (){
    int casos, IDv;
    /* Dados para o cálcula da posição prévia*/
    double IDi1, Xi1, Yi1, Hi1, thetaI1; 
    double IDj1, Xj1, Yj1, Hj1, thetaJ1;
    double IDk1, Xk1, Yk1, Hk1, thetaK1; 
    /* Dados para o cálcula da posição atual*/ 
    double deltaT;  
    double IDi2, Xi2, Yi2, Hi2, thetaI2; 
    double IDj2, Xj2, Yj2, Hj2, thetaJ2;
    double IDk2, Xk2, Yk2, Hk2, thetaK2;
    /*Localização e distância em relação as antenas prévias*/
    double xLP, yLP, diP, djP, dkP; 
    /*Localização e distância em relação as antenas atuais*/
    double xLA, yLA, diA, djA, dkA; 
    /*Outras infos*/
    double dist_per, dist_origem, vel_med;
    /**/ 

    FILE *arq;
    char filename [256];

    printf ("Programa-demo para o Sistema de Monitoramento\n\n"
    "Digite o nome do arquivo com os dados a serem processados:\n");
    scanf ("%s", filename);

    arq = fopen(filename, "r");

    if (arq == NULL) {
        printf ("Nao consegui abrir o arquivo %s.\n", filename);
        return 0;
    }

    scanf ("%d", &casos); 
    printf ("Casos a serem analisados: %d", casos);

    while (casos > 0) {
        scanf ("%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", 
        &IDv, &IDi1, &Xi1, &Yi2, &Hi1, &thetaI1, &IDj1, &Xj1, &Yj1, Hj1, &thetaJ1, &IDk1, &Xk1, &Yk1, &Hk1, thetaK1, &deltaT, &IDi2, &Xi2, &Yi2, &Hi2, &thetaI2, &IDj2, &Xj2, &Yj2, Hj2, &thetaJ2, &IDk2, &Xk2, &Yk2, &Hk2, thetaK2);

        diP = distancia (Hi1, thetaI1); djP = distancia (Hj1, thetaJ1); dkP = distancia (Hk1, thetaK1);

        diA = distancia (Hi2, thetaI2); djA = distancia (Hj2, thetaJ2); dkA = distancia (Hk2, thetaK2);

        printf ("IDENTIFICACAO: veiculo %d\n\n", IDv);
        printf ("Antenas na posicao previa:\n");
        printf ("id | posicao | H (m) | theta (graus) | distancia (m)\n");
        printf ("%lf | (%lf, %lf) | %lf | %lf | %lf\n", IDi1, Xi1, Yi1, thetaI1, diP);
        printf ("%lf | (%lf, %lf) | %lf | %lf | %lf\n", IDj1, Xj1, Yj1, thetaJ1, djP);
        printf ("%lf | (%lf, %lf) | %lf | %lf | %lf\n\n", IDk1, Xk1, Yk1, thetaK1, dkP);

        printf ("Antenas a posicao atual\n");
        printf ("id | posicao | H (m) | theta (graus) | distancia (m)\n");
        printf ("%lf | (%lf, %lf) | %lf | %lf | %lf\n", IDi2, Xi2, Yi2, thetaI2, diA);
        printf ("%lf | (%lf, %lf) | %lf | %lf | %lf\n", IDj2, Xj2, Yj2, thetaJ2, djA);
        printf ("%lf | (%lf, %lf) | %lf | %lf | %lf\n\n", IDk2, Xk2, Yk2, thetaK2, dkA);
    }
    fclose (arq);
    return 0;
}

int intercepta (double x0, double y0, double x1, double y1, double *x, double *y) {
    double a, b, c, r, m;
    double A, B, C, D; 
    double deltaY;
    double xL0, yL0, xL1, yL1; 

    if ( dist_origem (x0, x0) > dist_origem (x1, y1)) {
        if (iguais (x0, x1)) {
            equaçao_reta (x0, y0, x1, y1, &a, &b, &c);

            *x = 0;
            deltaY = ((200 * 200) - (x1 * x1));

            if (deltaY < 0) return 0; /*se Δ < 0 a reta não intercepta a AP*/
            else *y = raiz (deltaY, EPS);

            if ( y1 > y0) *y = - raiz (deltaY, EPS);
        }
        return 1; 


        if (dist_origem (x0, x0) < dist_origem (x1, x1)) {
            equaçao_reta (x0, y0, x1, y1, &a, &b, &c);
            A = 1 + (a *a) / (b * b); B = (2 * a * c) / (b * b); C = (c * c) / (b * b) - (200 * 200);
            D = (B * B) - (4 * A * C);

            if (D < 0) return 0; 

            xL0 = (-B + raiz (D, EPS)) / (2 * A);
            XL1 (-B - raiz (D, EPS)) / (2 * A);
            yL0 = ((-a * xL0) - c) / b;
            yL1 = ((-a * xL1) - c) / b;

            if (iguais (xL0, xL1)) {
                *x = xL0; *y = yL0; return 1;
            }

            else if (dist_percorrida (x1, y1, xL0, yL0) < dist_percorrida (x1, y1, xL1, yL1)) {
                *x = xL0; *y = yL0;

                if (dist_percorrida (x0, y0, *x, *y) > dist_percorrida (x1, y1, *x, *y)) return 0;

                else return 1;
            }

                else {
                    *x = xL1; *y = yL1;

                    if (dist_percorrida (x0, y0, *x, *y) > dist_percorrida (x1, y1, *x, *y)) return 0;

                    else return 1;
                }
            }
    else return 0;
    }
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

    if (x < epsilon) return 0;
    else {
    for (i = 0; i < 10; ++i)
          rant = rant/2 + x/(2*rant);
    }      
    return rant;  
 }

int equaçao_reta (double x0, double y0, double x1, double y1, double *a, double *b, double *c) {
    /*Segundo a fórmula fornecida*/
    *a = y0 - y1;
    *b = x1- x0;
    *c = (x0 * x1) - (y0 * y1);
}

double dist_origem (double x, double y) {
    double dist;
    dist = raiz ((x*x) + (y*y), EPS);
    if (x == 0 && y == 0) dist = 0;
    return dist;
}

double dist_percorrida (double xv1, double yv1, double xv2, double yv2) {
    double dist;
    dist = raiz (((xv2 - xv1) * (xv2 - xv1) + (yv2 - yv1) * (yv2 - yv1)), EPS);
    if ((xv2 - xv1) == 0 && (yv2 - yv1) == 0) dist = 0;
    return dist;
}