/* program stelib */

#include <cstdlib>
#include "matrix.h"

namespace mymatrix {
  size_t allmem=0; // dov' è dichiarato il tipo size_t?
  size_t memCheck() { return allmem; }
}

matrix matrixNew(int nrow, int ncol)
{
  matrix m;
  size_t size=sizeof(int); 
  size_t sizep=sizeof(int*);

  if(nrow<=0||ncol<=0)return 0;
  if(!(m=(matrix)calloc((size_t)nrow,sizep)))return 0;
  mymatrix::allmem+=((size_t)nrow*sizep);
  if(!(m[0]=(int*)calloc((size_t)(nrow*ncol),size)))return 0;
  mymatrix::allmem+=((size_t)(nrow*ncol)*size);
  for(int r=1;r<nrow;r++)m[r]=m[r-1]+ncol;
  return m;
}

matrix matrixDelete(matrix m, int nrow, int ncol)
{
  free(m[0]);
  free(m);
  mymatrix::allmem-=sizeof(int)*(size_t)(nrow+1)*ncol;
  return m=0;
}
