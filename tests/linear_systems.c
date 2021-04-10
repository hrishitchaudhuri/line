#include "../src/vectors.h"
#include "../src/real_matrices.h"
#include "../src/linear_systems.h"

int main() {
    double a1[3] = {1, 2, 0};
    double a2[3] = {3, 4, 4};
    double a3[3] = {5, 6, 3};

    double b[3] = {3, 7, 8};

    Vector *v1 = createVector(a1, 3);
    Vector *v2 = createVector(a2, 3);
    Vector *v3 = createVector(a3, 3);

    Vector *v[3] = {v1, v2, v3};
    Matrix *A = createMatrix(v, 3);

    Vector *B = createVector(b, 3);

    mxprintf(A);
    vctprintf(B);

    Vector *sol = solveLUP(A, B);
    vctprintf(sol);

    mxprintf(A);
    vctprintf(B);

    destroyVector(sol);

    sol = solveCramer(A, B);
    vctprintf(sol);

    mxprintf(A);
    vctprintf(B);

    destroyVector(v1);
    destroyVector(v2);
    destroyVector(v3);

    destroyVector(sol);
    destroyVector(B);
    destroyMatrix(A);

    return 0;
}