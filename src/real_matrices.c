#include<stdio.h>
#include<stdlib.h>

#include"vectors.h"
#include"real_matrices.h"

Matrix *createMatrix(Vector **v, int n) {
    //! ENSURE COMPATIBLE VECTORS ONLY. DOES NOT INIT OUT-OF-RANGE VECTORS.
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    m->vtr = (Vector **) malloc(sizeof(Vector *) * n);

    m->vtr = v;
    m->rows = n;
    m->cols = v[0]->dimension;

    return m;
}

void mxprintf(Matrix *m) {
    printf("[\n");
    for (register int i = 0; i < m->rows; i++) {
        vctprintf(m->vtr[i]);
    }

    printf("]\n");
}

Matrix* getTranspose(Matrix *m) {
    Matrix *mt = (Matrix *) malloc(sizeof(Matrix));
    mt->cols = m->rows; mt->rows = m->cols;

    mt->vtr = (Vector **) malloc(sizeof(Vector *) * mt->rows);
    for (register int i = 0; i < mt->rows; i++) {
        mt->vtr[i] = (Vector *) malloc (sizeof(Vector));
        mt->vtr[i]->dimension = mt->cols;
        mt->vtr[i]->arr = (double *) malloc (sizeof(double) * mt->cols);
    }

    for (register int i = 0; i < m->rows; i++)
        for (register int j = 0; j < m->cols; j++)
            mt->vtr[j]->arr[i] = m->vtr[i]->arr[j];

    return mt;
}

Matrix *getCofactor(Matrix *m, int rw, int cl) {
    Matrix *cf = (Matrix *) malloc(sizeof(Matrix));
    cf->cols = (m->cols) - 1; 
    cf->rows = (m->rows) - 1;

    cf->vtr = (Vector **) malloc(sizeof(Vector *) * cf->rows);
    for (register int i = 0; i < cf->rows; i++) {
        cf->vtr[i] = (Vector *) malloc (sizeof(Vector));
        cf->vtr[i]->dimension = cf->cols;
        cf->vtr[i]->arr = (double *) malloc (sizeof(double) * cf->cols);
    }

    int row_cnt = 0, col_cnt = 0;
    for (register int i = 0; i < m->rows; i++)
        for (register int j = 0; j < m->cols; j++)
            if ((i != rw) && (j != cl)) {
                cf->vtr[row_cnt]->arr[col_cnt] = m->vtr[i]->arr[j];
                col_cnt++;

                if (col_cnt == cf->cols) {
                    col_cnt = 0;
                    row_cnt++;
                }
            }
    
    return cf;
}

double getDeterminant(Matrix *m) {
    if (m->rows != m->cols) {
        printf("\033[0;31m [ERR] Incompatible dimensions. \n \033[0m");
        return ERR_CODE;
    }

    int res = 0, det_sign = 1;
    Matrix *cf;

    if (m->rows == 1) return m->vtr[0]->arr[0];

    for (register int i = 0; i < m->rows; i++) {
        cf = getCofactor(m, 0, i);
        res = res + det_sign * m->vtr[0]->arr[i] * getDeterminant(cf);
        det_sign = -det_sign; 
    }

    return res;
}

Matrix* getInverse(Matrix *m) {
    double det = getDeterminant(m);
    int det_sign = -1; 
    double res = 0;

    Matrix *inv = (Matrix *) malloc(sizeof(Matrix));
    inv->cols = m->cols; 
    inv->rows = m->rows;

    inv->vtr = (Vector **) malloc(sizeof(Vector *) * inv->rows);
    for (register int i = 0; i < inv->rows; i++) {
        inv->vtr[i] = (Vector *) malloc (sizeof(Vector));
        inv->vtr[i]->dimension = inv->cols;
        inv->vtr[i]->arr = (double *) malloc (sizeof(double) * inv->cols);
    }

    Matrix *cf;

    for (register int i = 0; i < m->rows; i++)
        for (register int j = 0; j < m->cols; j++) {
            cf = getCofactor(m, i, j);
            res = det_sign * getDeterminant(cf);
            inv->vtr[i]->arr[j] = res;
            det_sign = - det_sign;
        }

    inv = getTranspose(inv);

    for (register int i = 0; i < inv->rows; i++)
        for (register int j = 0; j < inv->cols; j++)
            inv->vtr[i]->arr[j] /= det;

    return inv;
}

double frobNorm(Matrix *m1, Matrix *m2) {
    double sum;
    for (register int i = 0; i < m1->rows; i++)
        for (register int j = 0; j < m1->cols; j++)
            sum += m1->vtr[i]->arr[j] * m2->vtr[i]->arr[j];
    
    return sum;
}

Matrix* hadamardProduct(Matrix *m1, Matrix *m2) {
    Matrix *hdmd = (Matrix *) malloc(sizeof(Matrix));
    hdmd->cols = m1->cols; 
    hdmd->rows = m1->rows;

    hdmd->vtr = (Vector **) malloc(sizeof(Vector *) * hdmd->rows);
    for (register int i = 0; i < hdmd->rows; i++) {
        hdmd->vtr[i] = (Vector *) malloc (sizeof(Vector));
        hdmd->vtr[i]->dimension = hdmd->cols;
        hdmd->vtr[i]->arr = (double *) malloc (sizeof(double) * hdmd->cols);
    }

    for (register int i = 0; i < m1->rows; i++)
        for (register int j = 0; j < m1->cols; j++)
            hdmd->vtr[i]->arr[j] = m1->vtr[i]->arr[j] * m2->vtr[i]->arr[j];

    return hdmd;
}

Matrix* matrixProduct(Matrix *m1, Matrix *m2) {
    Matrix *prod = (Matrix *) malloc(sizeof(Matrix));
    prod->cols = m1->cols; 
    prod->rows = m1->rows;

    prod->vtr = (Vector **) malloc(sizeof(Vector *) * prod->rows);
    for (register int i = 0; i < prod->rows; i++) {
        prod->vtr[i] = (Vector *) malloc (sizeof(Vector));
        prod->vtr[i]->dimension = prod->cols;
        prod->vtr[i]->arr = (double *) malloc (sizeof(double) * prod->cols);
    }

    for (register int i = 0; i < m1->rows; i++)
        for (register int j = 0; j < m1->cols; j++) {
            prod->vtr[i]->arr[j] = 0;
            for (register int k = 0; k < prod->rows; k++) 
                prod->vtr[i]->arr[j] += m1->vtr[i]->arr[k] * m2->vtr[k]->arr[j]; // lol strassen
        }

    return prod;
}