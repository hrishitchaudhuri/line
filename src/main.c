#include<stdio.h>

#include "vectors.h"
#include "real_matrices.h"
#include "linear_systems.h"
#include "transformations.h"
#include "calculus.h"

int main() {
    /*
    double a[5] = {1.23, 1.12, 1.56, 1.98, 2.03};

    Vector *v1 = createVector(a, 5);
    vctprintf(v1);

    scaleVector(v1, 10);
    vctprintf(v1);

    double b[5] = {1.43, 1.23, 4.56, 1.98, 1.11};

    Vector *v2 = createVector(b, 5);
    vctprintf(v2);

    double c[3] = {1, -2, 3};
    Vector *v3 = createVector(c, 3);

    printf("Inner product: %.3f \n", innerProduct(*v1, *v2));

    printf("Euclidean norm: %.3f \n", euclidNorm(*v3));
    printf("Taxicab norm: %.3f \n", taxiNorm(*v3));
    printf("L1-norm: %.3f \n", pNorm(*v3, 1));
    printf("L2-norm: %.3f \n", pNorm(*v3, 2));
    printf("Max norm: %.3f \n", maxNorm(*v3));

    Vector *v[2] = {v1, v2};
    Matrix *m = createMatrix(v, 2);

    mxprintf(m);

    Matrix *mt = getTranspose(m);
    mxprintf(mt);
    
    double a1[3] = {3, 4, 5};
    double b1[3] = {9, 1, 2};
    double c1[3] = {1, 7, 1};

    Vector *v1 = createVector(a1, 3);
    Vector *v2 = createVector(b1, 3);
    Vector *v3 = createVector(c1, 3);

    Vector *v[3] = {v1, v2, v3};
    Matrix *m = createMatrix(v, 3);
    mxprintf(m);

    printf("DET: %.3f\n", getDeterminant(m));

    Matrix *mi = getInverse(m);
    mxprintf(mi);

    Matrix *prod = matrixProduct(m, mi);
    mxprintf(prod);

    double a2[3] = {3, 4, 5};
    double b2[3] = {9, 1, 2};
    double c2[3] = {1, 7, 1};
    double d2[3] = {3, 5, 1};

    Vector *v1 = createVector(a2, 3);
    Vector *v2 = createVector(b2, 3);
    Vector *v3 = createVector(c2, 3);
    Vector *v4 = createVector(d2, 3);

    Vector *v_1[2] = {v1, v2};
    Vector *v_2[2] = {v3, v4};

    Matrix *m1 = createMatrix(v_1, 2);
    Matrix *m2 = createMatrix(v_2, 2);

    double fb = frobNorm(m1, m2);
    printf("FROBENIUS NORM : %.3f\n", fb);

    Matrix *hd = hadamardProduct(m1, m2);
    mxprintf(hd);

   double a[4] = {2, 3, 4, 1};
   Vector* p = createVector(a, 4);

   Matrix* A = getDiffMatrix(4);
   mxprintf(A);

   Vector* sl = diffPolynomial(p);
   vctprintf(sl);

   double a[4] = {2, 0, 2, 0.6};
   double b[4] = {3, 3, 4, -2};
   double c[4] = {5, 5, 4, 2};
   double d[4] = {-1, -2, 3.4, -1};

   Vector *v1 = createVector(a, 4);
   Vector *v2 = createVector(b, 4);
   Vector *v3 = createVector(c, 4);
   Vector *v4 = createVector(d, 4);

   Vector *v[4] = {v1, v2, v3, v4};

   Matrix *m = createMatrix(v, 4);
   Matrix *l = initMatrix(4, 4);
   Matrix *u = initMatrix(4, 4);
   Vector *p = initVector(4);

   decomposeLUP(m, l, u, p);
   mxprintf(l); mxprintf(u);
   vctprintf(p);

   double a1[3] = {1, 2, 0};
   double a2[3] = {3, 4, 4};
   double a3[3] = {5, 6, 3};

   double b[3] = {3, 7, 8};

   Vector *v[3] = {createVector(a1, 3), createVector(a2, 3), createVector(a3, 3)};
   Matrix *A = createMatrix(v, 3);

   Vector *B = createVector(b, 3);

   Vector *sol = solveLUP(A, B);
   vctprintf(sol);

   */

   double a1[4] = {2, 3, 1, 5};
   double a2[4] = {6, 13, 5, 19};
   double a3[4] = {2, 19, 10, 23};
   double a4[4] = {4, 10, 11, 31};

   Vector *v[4] = {createVector(a1, 4), createVector(a2, 4), createVector(a3, 4), createVector(a4, 4)};
   Matrix *A = createMatrix(v, 4);
   Matrix *L = initMatrix(4, 4);
   Matrix *U = initMatrix(4, 4);

   decomposeLU(A, L, U);

   mxprintf(L); mxprintf(U);

   return 0;
}