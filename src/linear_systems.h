#define ERR_CODE -99999

Vector *solveCramer(Matrix *, Vector *);
Vector *fsub(Vector *, Vector *, Matrix *);
Vector *bsub(Matrix *, Vector *);

void decomposeLU(Matrix *, Matrix *, Matrix *);
void decomposeLUP(Matrix *, Matrix *, Matrix *, Vector *);
Vector *solveLUP(Matrix *, Vector *);