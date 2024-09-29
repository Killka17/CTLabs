#include <stdint.h>
#include <stdio.h>

#define MARSENN_INT32_MAX INT32_MAX

void set_max_length(uint32_t head, uint32_t tail);

int8_t len(uint32_t numb);

void get_fact(uint32_t head, uint32_t tail, int8_t align, uint8_t first_len, uint8_t second_len);

uint32_t max(uint32_t a, uint32_t b);

int8_t max_length_second_colomn;

void make_headerLine(int8_t first_len, int8_t second_len);

void make_headerBody(int8_t first_len, int8_t second_len, int8_t align);

void print_fact(uint32_t i, uint32_t res, int8_t align, int8_t first_len, int8_t second_len);

void make_header(uint8_t max_length_first_colomn, uint8_t max_length_second_colomn, int8_t align);

void printWhitespaces(uint8_t n);

int main()
{
	int32_t num_temp_1, num_temp_2;
	int8_t align;

	if (scanf("%d %d %hhd", &num_temp_1, &num_temp_2, &align) != 3)
	{
		fprintf(stderr, "failed to read 3 values");
		return 1;
	}

	if (num_temp_1 < 0 || num_temp_2 < 0)
	{
		fprintf(stderr, "Negative values submitted");
		return 1;
	}
	uint32_t num_start = num_temp_1;
	uint32_t num_end = num_temp_2;

	uint8_t max_length_first_colomn;
	max_length_first_colomn = max(len(num_end), len(num_start));

	if (num_start <= num_end)
	{
		set_max_length(num_start, num_end);
		make_header(max_length_first_colomn, max_length_second_colomn, align);
		get_fact(num_start, num_end, align, max_length_first_colomn, max(max_length_second_colomn, 2));
		make_headerLine(max_length_first_colomn, max(max_length_second_colomn, 2));
	}
	else
	{
		set_max_length(num_start, UINT16_MAX);
		set_max_length(0, num_end);
		make_header(max_length_first_colomn, max_length_second_colomn, align);
		get_fact(num_start, UINT16_MAX, align, max_length_first_colomn, max(max_length_second_colomn, 2));
		get_fact(0, num_end, align, max_length_first_colomn, max(max_length_second_colomn, 2));
		make_headerLine(max_length_first_colomn, max(max_length_second_colomn, 2));
	}
	return 0;
}

void make_header(uint8_t max_length_first_colomn, uint8_t max_length_second_colomn, int8_t align)
{
	make_headerLine(max_length_first_colomn, max(max_length_second_colomn, 2));
	make_headerBody(max_length_first_colomn + 2, max(max_length_second_colomn + 2, 4), align);
	make_headerLine(max_length_first_colomn, max(max_length_second_colomn, 2));
}

void get_fact(uint32_t head, uint32_t tail, int8_t align, uint8_t first_len, uint8_t second_len)
{
	if (head == 0)
		print_fact(0, 1, align, first_len, second_len);
	uint64_t res = 1;
	for (uint32_t i = 1; i < head; i++)
		res = (res * i) % MARSENN_INT32_MAX;
	for (uint32_t i = max(head, 1); i <= tail; i++)
	{
		res = (res * i) % MARSENN_INT32_MAX;
		print_fact(i, res, align, first_len, second_len);
	}
}

void print_fact(uint32_t i, uint32_t res, int8_t align, int8_t first_len, int8_t second_len)
{
	if (align == 0)
	{
		printf("|");
		int8_t left = (first_len - len(i) + 1) >> 1;
		int8_t right = (first_len - len(i)) >> 1;
		for (int8_t j = 0; j < left + 1; j++)
			printf(" ");
		printf("%d", i);
		for (int8_t k = 0; k < right + 1; k++)
			printf(" ");
		printf("|");
		left = (second_len - len(res) + 1) >> 1;
		right = (second_len - len(res)) >> 1;
		for (int8_t p = 0; p < left + 1; p++)
			printf(" ");
		printf("%u", res);
		for (int8_t x = 0; x < right + 1; x++)
			printf(" ");
		printf("|\n");
	}
	else
	{
		printf("| %*d |", first_len * align, i);
		printf(" %*u |\n", second_len * align, res);
	}
}

uint32_t max(uint32_t a, uint32_t b)
{
	return a >= b ? a : b;
}

int8_t len(uint32_t numb)
{
	int8_t length = 1;
	numb /= 10;
	while (numb > 0)
	{
		length++;
		numb /= 10;
	}
	return length;
}

void set_max_length(uint32_t head, uint32_t tail)
{
	uint64_t res = 1;
	for (uint32_t i = 1; i <= tail; i++)
	{
		res = (res * i) % MARSENN_INT32_MAX;
		if (i >= head)
		{
			max_length_second_colomn = max(max_length_second_colomn, len(res));
		}
	}
}

void make_headerLine(int8_t first_len, int8_t second_len)
{
	printf("+");
	for (int8_t i = 0; i < first_len + 2; i++)
		printf("-");
	printf("+");
	for (int8_t i = 0; i < second_len + 2; i++)
		printf("-");
	printf("+\n");
}

void make_headerBody(int8_t first_len, int8_t second_len, int8_t align)
{
	if (align == 0)
	{
		printf("|");
		printWhitespaces(first_len);
		printf("n");
		printWhitespaces(first_len - 1);
		printf("|");
		printWhitespaces(second_len - 1);
		printf("n!");
		printWhitespaces(second_len - 2);
		printf("|\n");
	}
	else
	{
		printf("| %*s |", (first_len - 2) * align, "n");
		printf(" %*s |\n", (second_len - 2) * align, "n!");
	}
}
void printWhitespaces(uint8_t n)
{
	for (uint8_t i = 0; i < n >> 1; i++)
		printf(" ");
}
