#include <stdio.h>
#define EPS 0.01

int iguais (double x, double y);

int main () {
    int a, b, estado;

    scanf ("%d %d", a, b);

    estado = iguais (a, b);
    printf ("%d", estado);
    return 0;
    //1 se |x-y|<EPS e 0 se |x-y|>=EPS//

}

int iguais (double x, double y) {
    if (x - y < EPS && y - x < EPS ) return 1;
    else return 0;
}