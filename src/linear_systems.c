#include<stdio.h>
#include<stdlib.h>

#include "vectors.h"
#include "real_matrices.h"
#include "linear_systems.h"

Vector* solveCramer(Matrix *res, Vector *vol) {
    double det = getDeterminant(res);

    if (det == 0) {
        printf("\033[0;31m [ERR] Infinite solutions exist. \n \033[0m");
        exit(ERR_CODE);
    }

    Vector *sln = initVector(vol->dimension);
    Matrix* temp = initMatrix(res->rows, res->cols);

    for (register int i = 0; i < temp->rows; i++)
        for (register int j = 0; j < temp->cols; j++)
            temp->vtr[i]->arr[j] = res->vtr[i]->arr[j];

    for (register int i = 0; i < temp->rows; i++) {
        for (register int j = 0; j < temp->cols; j++) 
            temp->vtr[j]->arr[i] = vol->arr[j];

        sln->arr[i] = getDeterminant(temp) / det;
        for (register int j = 0; j < temp->cols; j++)
            temp->vtr[j]->arr[i] = res->vtr[j]->arr[i];       
    }

    destroyMatrix(temp);
    return sln;
}

Vector *fsub(Vector *p, Vector *b, Matrix *l) {
    Vector *y = initVector(p->dimension);

    double counter = 0;
    for (register int i = 0; i < b->dimension; i++) {
        for (register int j = 0; j < i; j++)
            counter += l->vtr[i]->arr[j] * y->arr[j];

        y->arr[i] = b->arr[(int) p->arr[i]] - counter;
        counter = 0;
    }

    return y;
}

Vector *bsub(Matrix *u, Vector *y) {
    Vector *x = initVector(y->dimension);

    double counter = 0;
    for (register int i = x->dimension - 1; i >= 0; i--) {
        for (register int j = i + 1; j < x->dimension; j++)
            counter += u->vtr[i]->arr[j] * x->arr[j];
        
        x->arr[i] = (y->arr[i] - counter) / u->vtr[i]->arr[i];
        counter = 0;
    }

    return x;
}

void decomposeLU(Matrix *A, Matrix *L, Matrix *U) {
    for (register int i = 0; i < A->rows; i++) {
        for (register int j = 0; j < i; j++)
            U->vtr[i]->arr[j] = 0;

        for (register int j = i; j < A->cols; j++)
            L->vtr[i]->arr[j] = (i == j) ? 1 : 0;
    }

    for (register int i = 0; i < A->rows; i++) {
        U->vtr[i]->arr[i] = A->vtr[i]->arr[i];
        for (register int j = i + 1; j < A->cols; j++) {
            L->vtr[j]->arr[i] = A->vtr[j]->arr[i] / U->vtr[i]->arr[i];
            U->vtr[i]->arr[j] = A->vtr[i]->arr[j];
        }

        for (register int j = i + 1; j < A->cols; j++)
            for (register int k = i + 1; k < A->cols; k++)
                A->vtr[j]->arr[k] -= L->vtr[j]->arr[i] * U->vtr[i]->arr[k];
    }
}

void decomposeLUP(Matrix *A, Matrix *L, Matrix *U, Vector *P) {
    Matrix *A_cp = initMatrix(A->rows, A->cols);

    for (register int i = 0; i < A->rows; i++) 
        for (register int j = 0; j < A->cols; j++) 
            A_cp->vtr[i]->arr[j] = A->vtr[i]->arr[j];
    
    for (register int i = 0; i < P->dimension; i++)
        P->arr[i] = i;
    
    double p, temp; int k;
    for (register int i = 0; i < P->dimension; i++) {
        p = 0;
        for (register int j = i; j < P->dimension; j++)
            if ((A_cp->vtr[j]->arr[i] < 0 ? - A_cp->vtr[j]->arr[i] : A_cp->vtr[j]->arr[i]) > p) {
                p = A_cp->vtr[j]->arr[i] < 0 ? - A_cp->vtr[j]->arr[i] : A_cp->vtr[j]->arr[i];
                k = j;
            }

        if (p == 0) {
            printf("\033[0;31m [ERR] Singular Matrix \n \033[0m");
            exit(ERR_CODE);
        }
            
        temp = P->arr[k];
        P->arr[k] = P->arr[i];
        P->arr[i] = temp;

        for (register int j = 0; j < P->dimension; j++) {
            temp = A_cp->vtr[i]->arr[j];
            A_cp->vtr[i]->arr[j] = A_cp->vtr[k]->arr[j];
            A_cp->vtr[k]->arr[j] = temp;
        }

        for (register int j = i + 1; j < P->dimension; j++) {
            A_cp->vtr[j]->arr[i] /= A_cp->vtr[i]->arr[i];
            for (register int k = i + 1; k < P->dimension; k++)
                A_cp->vtr[j]->arr[k] -= A_cp->vtr[j]->arr[i] * A_cp->vtr[i]->arr[k];
        }
    }

    for (register int i = 0; i < A_cp->rows; i++)
        for (register int j = 0; j < A_cp->cols; j++) {
            if (i > j) {
                U->vtr[i]->arr[j] = 0;
                L->vtr[i]->arr[j] = A_cp->vtr[i]->arr[j];
            }

            else if (i == j) {
                L->vtr[i]->arr[j] = 1;
                U->vtr[i]->arr[j] = A_cp->vtr[i]->arr[j];
            }

            else {
                L->vtr[i]->arr[j] = 0;
                U->vtr[i]->arr[j] = A_cp->vtr[i]->arr[j];
            }
        }

    destroyMatrix(A_cp);
}

Vector *solveLUP(Matrix *A, Vector *b) {
    Matrix *L = initMatrix(A->rows, A->cols);
    Matrix *U = initMatrix(A->rows, A->cols);
    Vector *P = initVector(A->rows);
    
    decomposeLUP(A, L, U, P);

    Vector *y = fsub(P, b, L);
    Vector *x = bsub(U, y);

    destroyMatrix(L);
    destroyMatrix(U);

    destroyVector(P);
    destroyVector(y);
    
    return x;
}