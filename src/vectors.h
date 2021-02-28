typedef struct vector {
    int dimension;
    double *arr;
} Vector;

Vector *initVector(int);
Vector *createVector(double *, int);
void scaleVector(Vector *, double);
void vctprintf(Vector *);

double innerProduct(Vector, Vector);
double euclidNorm(Vector);
double taxiNorm(Vector);
double pNorm(Vector, int);
double maxNorm(Vector);