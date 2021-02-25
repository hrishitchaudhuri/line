#include "vectors.h"
#include "real_matrices.h"
#include "linear_systems.h"

Vector* solveCramer(Matrix *res, Vector *vol) {
    double det = getDeterminant(res);

    if (det == 0) {
        printf("\033[0;31m [ERR] Infinite solutions exist. \n \033[0m");
        exit(ERR_CODE);
    }

    Vector *sln = (Vector *) malloc(sizeof(Vector));
    sln->dimension = vol->dimension;
    sln->arr = (double *) malloc(sizeof(double) * sln->dimension);

    Matrix* temp = (Matrix *) malloc(sizeof(Matrix));
    temp->cols = res->cols; temp->rows = res->rows;
    temp->vtr = (Vector **) malloc(sizeof(Vector *) * temp->rows);

    for (register int i = 0; i < temp->rows; i++) {
        temp->vtr[i] = (Vector *) malloc (sizeof(Vector));
        temp->vtr[i]->dimension = temp->cols;
        temp->vtr[i]->arr = (double *) malloc (sizeof(double) * temp->cols);
    }

    for (register int i = 0; i < temp->rows; i++)
        for (register int j = 0; j < temp->cols; j++)
            temp->vtr[i]->arr[j] = res->vtr[i]->arr[j];

    for (register int i = 0; i < temp->rows; i++) {
        for (register int j = 0; j < temp->cols; j++) 
            temp->vtr[j]->arr[i] = vol->arr[j];

        sln->arr[i] = getDeterminant(temp);
        for (register int j = 0; j < temp->cols; j++)
            temp->vtr[j]->arr[i] = res->vtr[j]->arr[i];       
    }
}