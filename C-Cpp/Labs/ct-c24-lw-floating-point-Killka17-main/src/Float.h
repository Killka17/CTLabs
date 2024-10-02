#ifndef FLOAT_
#define FLOAT_

#define BITS_MANTIS_SPF 23
#define BITS_EXPONENT_SPF 8

#define BITS_MANTIS_HPF 10
#define BITS_EXPONENT_HPF 5

#include <stdbool.h>
#include <stdint.h>

union SinglePFloatNumber
{
	uint32_t number;

	struct
	{
		uint32_t mantis : BITS_MANTIS_SPF;
		uint32_t exponent : BITS_EXPONENT_SPF;
		uint32_t sign : 1;
	} bits;
};

union HalfPFloatNumber
{
	uint32_t number;

	struct
	{
		uint32_t mantis : BITS_MANTIS_HPF;
		uint32_t exponent : BITS_EXPONENT_HPF;
		uint32_t sign : 1;
	} bits;
};

enum FloatType
{
	HalfPrecision = 'h',
	SinglePrecision = 'f'
};

struct FloatNumber
{
	union
	{
		union SinglePFloatNumber single;
		union HalfPFloatNumber half;
	} precision;

	enum FloatType float_type;
};

enum RoundType
{
	TowardZero = 0,
	TowardNearestEven = 1,
	TowardPosInfinity = 2,
	TowardNegInfinity = 3,
};

enum Operation
{
	Not = 0,
	Additional = '+',
	Subtract = '-',
	Divide = '/',
	Multiply = '*'
};

enum ArgReadStatus
{
	Failed,
	Success
};

#endif
