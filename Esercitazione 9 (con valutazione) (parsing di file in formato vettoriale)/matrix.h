/* smatvec.h */

#ifndef SMATVEC_H
#define SMATVEC_H

typedef int ** matrix;
matrix matrixNew(int, int);
matrix matrixDelete(matrix, int, int);

#endif
