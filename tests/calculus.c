#include "../src/vectors.h"
#include "../src/real_matrices.h"
#include "../src/calculus.h"

int main() {
    double a[4] = {2, 3, 4, 1};
    Vector* p = createVector(a, 4);

    Matrix* A = getDiffMatrix(4);
    mxprintf(A);

    Vector* sl = diffPolynomial(p);
    vctprintf(sl);

    destroyMatrix(A);
    destroyVector(p);
    destroyVector(sl);

    return 0;
}