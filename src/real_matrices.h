typedef struct matrix {
    int rows; int cols;
    Vector **vtr;
} Matrix;

Matrix *createMatrix(Vector **, int);
void mxprintf(Matrix *);

Matrix* mtxTranspose(Matrix *);
double getDeterminant(Matrix *);
Matrix *getCofactor(Matrix *, int, int);