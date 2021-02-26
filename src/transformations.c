#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "vectors.h"
#include "real_matrices.h"
#include "transformations.h"

Vector *get2DRotation(Vector *v, double rads) {
    if (v->dimension != 2) {
        printf("\033[0;31m [ERR] Rotation only allowed in R2 space. If you're working in R1, you do not need to rotate, and if you're higher, you can have fun solving SO(n) for yourself!\n \033[0m");
        exit(ERR_CODE);
    }

    Vector *rot = (Vector *) malloc(sizeof(Vector));
    rot->dimension = 2;
    rot->arr = (double *) malloc(sizeof(double) * rot->dimension);

    rot->arr[0] = cos(rads) * v->arr[0] - sin(rads) * v->arr[1];
    rot->arr[1] = sin(rads) * v->arr[0] + cos(rads) * v->arr[1];

    return rot;
}

Vector *get2DReflection(Vector *v, double rads) {
    if (v->dimension != 2) {
        printf("\033[0;31m [ERR] Reflection only allowed in R2 space.\n \033[0m");
        exit(ERR_CODE);
    }

    Vector *ref = (Vector *) malloc(sizeof(Vector));
    ref->dimension = 2;
    ref->arr = (double *) malloc(sizeof(double) * ref->dimension);

    ref->arr[0] = cos(2 * rads) * v->arr[0] + sin(2 * rads) * v->arr[1];
    ref->arr[1] = sin(2 * rads) * v->arr[0] - cos(2 * rads) * v->arr[1];

    return ref;    
}

Vector *get2DProjection(Vector *v, double rads) {
    if (v->dimension != 2) {
        printf("\033[0;31m [ERR] Projection only allowed in R2 space.\n \033[0m");
        exit(ERR_CODE);
    }

    Vector *proj = (Vector *) malloc(sizeof(Vector));
    proj->dimension = 2;
    proj->arr = (double *) malloc(sizeof(double) * proj->dimension);

    proj->arr[0] = pow(cos(rads), 2) * v->arr[0] + cos(rads) * sin(rads) * v->arr[1];
    proj->arr[1] = cos(rads) * sin(rads) * v->arr[0] - pow(sin(rads), 2) * v->arr[1];

    return proj;
}

Vector *get2DShear(Vector *v, int direction, double shear_factor) {
    if (v->dimension != 2) {
        printf("\033[0;31m [ERR] Shear map only allowed in R2 space.\n \033[0m");
        exit(ERR_CODE);
    }

    Vector *sh = (Vector *) malloc(sizeof(Vector));
    sh->dimension = 2;
    sh->arr = (double *) malloc(sizeof(double) * sh->dimension);

    if (direction) {
        sh->arr[0] = shear_factor * v->arr[1] + v->arr[0];
        sh->arr[1] = v->arr[1];
    }

    else {
        sh->arr[0] = v->arr[0];
        sh->arr[1] = shear_factor * v->arr[0] + v->arr[1];
    }

    return sh;
}