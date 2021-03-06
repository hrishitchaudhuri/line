#include<stdio.h>
#include<stdlib.h>

#include"vectors.h"
#include"real_matrices.h"

Matrix *initMatrix(int rw, int cl) {
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    m->cols = cl; 
    m->rows = rw;

    m->vtr = (Vector **) malloc(sizeof(Vector *) * m->rows);
    for (register int i = 0; i < m->rows; i++)
        m->vtr[i] = initVector(m->cols);

    return m;
}

Matrix *createMatrix(Vector **v, int n) {
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    m->rows = n;
    m->cols = v[0]->dimension;

    m->vtr = (Vector **) malloc(sizeof(Vector *) * m->rows);
    for (register int i = 0; i < m->rows; i++)
        m->vtr[i] = initVector(m->cols);


    for (register int i = 0; i < m->rows; i++)
        for (register int j = 0; j < m->cols; j++)
            m->vtr[i]->arr[j] = v[i]->arr[j];

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
    Matrix *mt = initMatrix(m->cols, m->rows);

    for (register int i = 0; i < m->rows; i++)
        for (register int j = 0; j < m->cols; j++)
            mt->vtr[j]->arr[i] = m->vtr[i]->arr[j];

    return mt;
}

Matrix *getCofactor(Matrix *m, int rw, int cl) {
    Matrix *cf = initMatrix(m->rows - 1, m->cols - 1);

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
        exit(ERR_CODE);
    }

    int res = 0, det_sign = 1;
    Matrix *cf;

    if (m->rows == 1) return m->vtr[0]->arr[0];

    for (register int i = 0; i < m->rows; i++) {
        cf = getCofactor(m, 0, i);
        res = res + det_sign * m->vtr[0]->arr[i] * getDeterminant(cf);
        det_sign = -det_sign; 

        destroyMatrix(cf);
    }

    return res;
}

Matrix* getInverse(Matrix *m) {
    double det = getDeterminant(m);
    int det_sign = 1; 
    double res = 0;

    Matrix *inv = initMatrix(m->rows, m->cols);

    Matrix *cf;

    for (register int i = 0; i < m->rows; i++)
        for (register int j = 0; j < m->cols; j++) {
            cf = getCofactor(m, i, j);
            res = det_sign * getDeterminant(cf);
            inv->vtr[i]->arr[j] = res;
            det_sign = - det_sign;

            destroyMatrix(cf);
        }

    Matrix *inv_t = getTranspose(inv);

    for (register int i = 0; i < inv_t->rows; i++)
        for (register int j = 0; j < inv_t->cols; j++)
            inv_t->vtr[i]->arr[j] /= det;

    destroyMatrix(inv);

    return inv_t;
}

double frobNorm(Matrix *m1, Matrix *m2) {
    double sum = 0;
    for (register int i = 0; i < m1->rows; i++)
        for (register int j = 0; j < m1->cols; j++)
            sum += m1->vtr[i]->arr[j] * m2->vtr[i]->arr[j];
    
    return sum;
}

Matrix* hadamardProduct(Matrix *m1, Matrix *m2) {
    Matrix *hdmd = initMatrix(m1->rows, m1->cols);

    for (register int i = 0; i < m1->rows; i++)
        for (register int j = 0; j < m1->cols; j++)
            hdmd->vtr[i]->arr[j] = m1->vtr[i]->arr[j] * m2->vtr[i]->arr[j];

    return hdmd;
}

Matrix* matrixProduct(Matrix *m1, Matrix *m2) {
    if (m1->cols != m2->rows) {
        printf("\033[0;31m>> [ERR] Incompatible dimensions. \n \033[0m");
        exit(ERR_CODE);
    }

    Matrix *prod = initMatrix(m1->rows, m2->cols);

    for (register int i = 0; i < m1->rows; i++)
        for (register int j = 0; j < m2->cols; j++) {
            prod->vtr[i]->arr[j] = 0;
            for (register int k = 0; k < m1->cols; k++) 
                prod->vtr[i]->arr[j] += m1->vtr[i]->arr[k] * m2->vtr[k]->arr[j]; // lol strassen
        }

    return prod;
}

void destroyMatrix(Matrix *m) {
    for (register int i = 0; i < m->rows; i++)
        destroyVector(m->vtr[i]);
    free(m->vtr);
    free(m);
}