#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "vectors.h"

#define ERR_CODE -99999

Vector *initVector(int n) {
    /**
     \brief Initialize pointer to a Vector.
     */
     
    Vector* v = (Vector *) malloc(sizeof(Vector));
    v->arr = (double *) malloc(sizeof(double) * n);
    v->dimension = n;

    return v;
}

Vector *createVector(double *a, int n) {
    /**
     \brief Create Vector from array of doubles.
     */
    
    Vector* v = (Vector *) malloc(sizeof(Vector));
    v->arr = (double *) malloc(sizeof(double) * n);

    v->dimension = n;

    for (register int i = 0; i < n; i++)
        v->arr[i] = a[i];

    return v;
}

Vector *scaleVector(Vector *v, double sf) {
    /**
     \brief Scale Vector by some scaling factor (sf).
     */
    
    Vector *v_sc = initVector(v->dimension);
    for (register int i = 0; i < v->dimension; i++)
        v_sc->arr[i] = v->arr[i] / sf;
    
    return v_sc;
}

void vctprintf(Vector *v) {
    /**
     \brief Print Vector onto STDOUT.
     */
    
    printf("<");
    for (register int i = 0; i < (v->dimension - 1); i++) {
        printf(" %.3f,", v->arr[i]);
    }
    printf(" %.3f >\n", v->arr[(v->dimension) - 1]);
}

double innerProduct(Vector *v1, Vector *v2) {
    /**
     \brief Return inner product of two Vectors.
     */
    
    if (v1->dimension != v2->dimension) {
        printf("\033[0;31m [ERR] Incompatible dimensions. \n \033[0m");
        return ERR_CODE;
    }

    double ip = 0;
    for (register int i = 0; i < v1->dimension; i++)
        ip = ip + (v1->arr[i] * v2->arr[i]);

    return ip;
}

double euclidNorm(Vector *v) {
    /**
     \brief Return Euclidean distance (Euclidean/L2 norm) of a Vector.
     */
    
    return pow(innerProduct(v, v), 0.5);
}

double taxiNorm(Vector *v) {
    /**
     \brief Return taxicab/L1 norm of a Vector.
     */
    
    double manhattan = 0;
    for (register int i = 0; i < v->dimension; i++) 
        manhattan = manhattan + ((v->arr[i] < 0) ? (- v->arr[i]) : (v->arr[i]));

    return manhattan;
}

double pNorm(Vector *v, int p) {
    /**
     \brief Return Lp norm of a Vector.
     */
    
    double lp = 0;
    for (register int i = 0; i < v->dimension; i++)
        lp = lp + ((v->arr[i] < 0) ? pow((- v->arr[i]), p) : pow(v->arr[i], p));

    return pow(lp, (double) 1 / p);
}

double maxNorm(Vector *v) {
    /**
     \brief Return max element of a Vector.
     */
    
    double max = v->arr[0];
    for (register int i = 1; i < v->dimension; i++)
        max = (max < v->arr[i]) ? v->arr[i] : max;

    return max;
}

void destroyVector(Vector *v) {
    /**
     \brief Free dynamically allocated space (Vector destructor).
     */
    free(v->arr);
    free(v);
}
