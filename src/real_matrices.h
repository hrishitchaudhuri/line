#define ERR_CODE -99999

typedef struct matrix {
    int rows; int cols;
    Vector **vtr;
} Matrix;

void mxprintf(Matrix *);

double getDeterminant(Matrix *);
double frobNorm(Matrix *, Matrix *);

Matrix *initMatrix(int, int);
Matrix *createMatrix(Vector **, int);
Matrix* getTranspose(Matrix *);
Matrix *getCofactor(Matrix *, int, int);
Matrix* getInverse(Matrix *);
Matrix* hadamardProduct(Matrix *, Matrix *);
Matrix* matrixProduct(Matrix *, Matrix *);

void destroyMatrix(Matrix *);