#include "../src/vectors.h"
#include "../src/transformations.h"

#define PI 3.141592653589

int main() {
    double a1[2] = {2, 3};

    Vector *v1 = createVector(a1, 2);

    Vector *v2 = get2DProjection(v1, PI / 4);
    Vector *v3 = get2DReflection(v1, PI / 3);
    Vector *v4 = get2DRotation(v1, PI / 6);
    Vector *v5 = get2DShear(v1, 1, 0.3);

    vctprintf(v1);
    vctprintf(v2);
    vctprintf(v3);
    vctprintf(v4);
    vctprintf(v5);

    destroyVector(v1);
    destroyVector(v2);
    destroyVector(v3);
    destroyVector(v4);
    destroyVector(v5);

    return 0;
}