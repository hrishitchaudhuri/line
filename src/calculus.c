#include<stdio.h>
#include<stdlib.h>

#include "vectors.h"
#include "real_matrices.h"
#include "calculus.h"

Matrix *getDiffMatrix(int degree) {
    int ip_degree = degree;
    int op_degree = ip_degree - 1;

    Matrix *diff_t = initMatrix(ip_degree, op_degree);
    Matrix *diff = initMatrix(op_degree, ip_degree);

    for (register int i = 0; i < ip_degree; i++) {
        Vector *temp = (Vector *) malloc(sizeof(Vector));
        temp->dimension = op_degree;
        temp->arr = (double *) malloc(sizeof(double) * temp->dimension);

        for (register int j = 0; j < op_degree; j++)
            temp->arr[j] = 0;

        if ((i - 1) >= 0)
            temp->arr[i-1] = i;

        diff_t->vtr[i] = temp;
    }

    diff = getTranspose(diff_t);
    return diff;
}

Vector *diffPolynomial(Vector *p) {
    int ip_degree = p->dimension;

    Matrix *diff = getDiffMatrix(ip_degree);
    Matrix *poly = initMatrix(1, ip_degree);
    poly->vtr[0] = p;

    poly = getTranspose(poly);

    Matrix *sol = matrixProduct(diff, poly);
    sol = getTranspose(sol);
    return sol->vtr[0];
}