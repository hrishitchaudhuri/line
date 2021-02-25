#include<stdio.h>
#include "vectors.h"

#define ERR_CODE -99999

int main() {
    double a[5] = {1.23, 1.12, 1.56, 1.98, 2.03};

    Vector *v1 = createVector(a, 5);
    vctprintf(v1);

    scaleVector(v1, 10);
    vctprintf(v1);

    double b[5] = {1.43, 1.23, 4.56, 1.98, 1.11};

    Vector *v2 = createVector(b, 5);
    vctprintf(v2);

    double c[3] = {1, -2, 3};
    Vector *v3 = createVector(c, 3);

    printf("Inner product: %.3f \n", innerProduct(*v1, *v2));

    printf("Euclidean norm: %.3f \n", euclidNorm(*v3));
    printf("Taxicab norm: %.3f \n", taxiNorm(*v3));
    printf("L1-norm: %.3f \n", pNorm(*v3, 1));
    printf("L2-norm: %.3f \n", pNorm(*v3, 2));
    printf("Max norm: %.3f \n", maxNorm(*v3));

    return 0;
}