#include<stdio.h>

#include"../src/vectors.h"
#include"../src/real_matrices.h"

int main() {
    double a[5] = {1.23, 1.12, 1.56, 1.98, 2.03};
    Vector *v1 = createVector(a, 5);

    double b[5] = {1.43, 1.23, 4.56, 1.98, 1.11};
    Vector *v2 = createVector(b, 5);

    Vector *v[2] = {v1, v2};
    Matrix *m = createMatrix(v, 2);
    mxprintf(m);

    Matrix *mt = getTranspose(m);
    mxprintf(mt);

    destroyVector(v1);
    destroyVector(v2);

    printf("Vectors done.\n");

    destroyMatrix(m);
    destroyMatrix(mt);

    printf("Matrices done.\n");

    double a1[3] = {3, 4, 5};
    double b1[3] = {9, 1, 2};
    double c1[3] = {1, 7, 1};

    v1 = createVector(a1, 3);
    v2 = createVector(b1, 3);
    Vector *v3 = createVector(c1, 3);

    Vector *v_t[3] = {v1, v2, v3};
    m = createMatrix(v_t, 3);
    mxprintf(m);

    printf("DET: %.3f\n", getDeterminant(m));

    Matrix *mi = getInverse(m);
    mxprintf(mi);

    Matrix *prod = matrixProduct(m, mi);
    mxprintf(prod);

    destroyVector(v1);
    destroyVector(v2);
    destroyVector(v3);

    destroyMatrix(m);
    destroyMatrix(mi);
    destroyMatrix(prod);

    double a2[3] = {3, 4, 5};
    double b2[3] = {9, 1, 2};
    double c2[3] = {1, 7, 1};
    double d2[3] = {3, 5, 1};

    v1 = createVector(a2, 3);
    v2 = createVector(b2, 3);
    v3 = createVector(c2, 3);
    Vector *v4 = createVector(d2, 3);

    Vector *v_1[2] = {v1, v2};
    Vector *v_2[2] = {v3, v4};

    Matrix *m1 = createMatrix(v_1, 2);
    Matrix *m2 = createMatrix(v_2, 2);

    double fb = frobNorm(m1, m2);
    printf("FROBENIUS NORM : %.3f\n", fb);

    Matrix *hd = hadamardProduct(m1, m2);
    mxprintf(hd);

    destroyVector(v1);
    destroyVector(v2);
    destroyVector(v3);
    destroyVector(v4);

    destroyMatrix(m1);
    destroyMatrix(m2);
    destroyMatrix(hd);
}