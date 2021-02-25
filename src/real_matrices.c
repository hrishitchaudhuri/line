#include<stdio.h>
#include<stdlib.h>

#include"vectors.h"
#include"real_matrices.h"

#define ERR_CODE -99999

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

Matrix* mtxTranspose(Matrix *m) {
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