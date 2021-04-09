#include<stdio.h>
#include<stdlib.h>

#include "vectors.h"
#include "real_matrices.h"
#include "calculus.h"

Matrix *getDiffMatrix(int degree) {
    int ip_degree = degree;
    int op_degree = ip_degree - 1;

    Matrix *diff_t = initMatrix(ip_degree, op_degree);
    Matrix *diff;

    for (register int i = 0; i < ip_degree; i++) {
        for (register int j = 0; j < op_degree; j++)
            diff_t->vtr[i]->arr[j] = 0;

        if ((i - 1) >= 0)
            diff_t->vtr[i]->arr[i-1] = i;
    }

    diff = getTranspose(diff_t);

    destroyMatrix(diff_t);
    return diff;
}

Vector *diffPolynomial(Vector *p) {
    Vector *sol_v;
    Matrix *sol_t, *poly_t;

    int ip_degree = p->dimension;

    Matrix *diff = getDiffMatrix(ip_degree);
    Matrix *poly = initMatrix(1, ip_degree);
    for (register int i = 0; i < ip_degree; i++)
        poly->vtr[0]->arr[i] = p->arr[i];

    poly_t = getTranspose(poly);

    Matrix *sol = matrixProduct(diff, poly_t);
    sol_t = getTranspose(sol);

    sol_v = initVector(sol_t->cols);
    for (register int i = 0; i < sol_t->cols; i++) 
        sol_v->arr[i] = sol_t->vtr[0]->arr[i];

    destroyMatrix(sol_t);
    destroyMatrix(sol);
    destroyMatrix(poly);
    destroyMatrix(poly_t);
    destroyMatrix(diff);

    return sol_v;
}