#include "myFftw.h"

int max_index(const double *arr, int size)
{
	int ind = 0;
	double max_element = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max_element)
		{
			ind = i;
			max_element = arr[i];
		}
	}
	return ind;
}

int cross_correlation(DataArr *arr1, DataArr *arr2, int *result)
{
	int size = arr1->size + arr2->size - 1;
	fftw_complex *out_first, *out_second, *out;
	fftw_plan plan_x = NULL, plan_y = NULL, plan_inv = NULL;
	double *first, *second, *res;

	out_first = fftw_alloc_complex(size);
	out_second = fftw_alloc_complex(size);
	first = fftw_alloc_real(size);
	second = fftw_alloc_real(size);
	res = fftw_alloc_real(size);
	out = fftw_alloc_complex(size);

	if (!out_first || !out_second || !first || !second || !res || !out)
	{
		fprintf(stderr, "Allocation failed.\n");
		fftw_free(out_first);
		fftw_free(out_second);
		fftw_free(first);
		fftw_free(second);
		fftw_free(res);
		fftw_free(out);
		return ERROR_NOTENOUGH_MEMORY;
	}

	for (int i = 0; i < size; i++)
	{
		first[i] = (i < arr1->size) ? arr1->arr[i] : 0;
		second[i] = (i < arr2->size) ? arr2->arr[i] : 0;
	}

	plan_x = fftw_plan_dft_r2c_1d(size, first, out_first, FFTW_ESTIMATE);
	plan_y = fftw_plan_dft_r2c_1d(size, second, out_second, FFTW_ESTIMATE);
	if (!plan_x || !plan_y)
	{
		fprintf(stderr, "FFT planning failed.\n");
		fftw_destroy_plan(plan_x);
		fftw_destroy_plan(plan_y);
		fftw_free(out_first);
		fftw_free(out_second);
		fftw_free(first);
		fftw_free(second);
		fftw_free(res);
		fftw_free(out);
		return ERROR_NOTENOUGH_MEMORY;
	}

	fftw_execute(plan_x);
	fftw_execute(plan_y);

	for (int i = 0; i < size; i++)
	{
		out[i][0] = out_first[i][0] * out_second[i][0] + out_first[i][1] * out_second[i][1];
		out[i][1] = -(out_first[i][0] * out_second[i][1] - out_first[i][1] * out_second[i][0]);
	}

	plan_inv = fftw_plan_dft_c2r_1d(size, out, res, FFTW_ESTIMATE);
	if (!plan_inv)
	{
		fprintf(stderr, "IFFT planning failed.\n");
		fftw_destroy_plan(plan_x);
		fftw_destroy_plan(plan_y);
		fftw_free(out_first);
		fftw_free(out_second);
		fftw_free(out);
		fftw_free(first);
		fftw_free(second);
		fftw_free(res);
		return ERROR_NOTENOUGH_MEMORY;
	}
	fftw_execute(plan_inv);

	int ans = max_index(res, size);
	if (ans > arr1->size)
	{
		ans = ans - size;
	}

	fftw_destroy_plan(plan_x);
	fftw_destroy_plan(plan_y);
	fftw_destroy_plan(plan_inv);
	fftw_free(out_first);
	fftw_free(out_second);
	fftw_free(out);
	fftw_free(first);
	fftw_free(second);
	fftw_free(res);

	*result = ans;

	return SUCCESS;
}
