#define ERR_CODE -99999

typedef struct matrix {
    int rows; int cols;
    Vector **vtr;
} Matrix;

Matrix *initMatrix(int, int);
Matrix *createMatrix(Vector **, int);
void mxprintf(Matrix *);

Matrix* getTranspose(Matrix *);
double getDeterminant(Matrix *);
Matrix *getCofactor(Matrix *, int, int);
Matrix* getInverse(Matrix *);
double frobNorm(Matrix *, Matrix *);
Matrix* hadamardProduct(Matrix *, Matrix *);
Matrix* matrixProduct(Matrix *, Matrix *);