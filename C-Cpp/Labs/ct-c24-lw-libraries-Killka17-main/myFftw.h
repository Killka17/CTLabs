#ifndef LAB2_MYFFTW_H
#define LAB2_MYFFTW_H

#include "myFfmpeg.h"
#include "return_codes.h"

#include <fftw3.h>

int max_index(const double *arr, int size);
int cross_correlation(DataArr *arr1, DataArr *arr2, int *result);

#endif
