#include "FloatUtils.h"

uint32_t getExponentMask(enum FloatType float_type)
{
	return (float_type == HalfPrecision) ? 0x1f : 0xff;
}

uint32_t getMantissaMask(enum FloatType float_type)
{
	return (float_type == HalfPrecision) ? 0x3ff : 0x7fffff;
}

uint32_t getMaxExponent(enum FloatType float_type)
{
	return (float_type == HalfPrecision) ? 15 : 127;
}

uint32_t getMaxMantissa(enum FloatType float_type)
{
	return (float_type == HalfPrecision) ? (1 << BITS_MANTIS_HPF) - 1 : (1 << BITS_MANTIS_SPF) - 1;
}

uint32_t getMantissa(struct FloatNumber* float_number)
{
	return (float_number->float_type == HalfPrecision)
			 ? float_number->precision.half.bits.mantis
			 : float_number->precision.single.bits.mantis;
}

uint32_t getExponent(struct FloatNumber* float_number)
{
	return (float_number->float_type == HalfPrecision)
			 ? float_number->precision.half.bits.exponent
			 : float_number->precision.single.bits.exponent;
}

uint32_t getSign(struct FloatNumber* float_number)
{
	return float_number->float_type == HalfPrecision
			 ? float_number->precision.half.bits.sign
			 : float_number->precision.single.bits.sign;
}

uint32_t getHighestBit(struct FloatNumber* float_number)
{
	uint32_t highest_bit = (float_number->float_type == HalfPrecision) ? BITS_MANTIS_HPF : BITS_MANTIS_SPF;
	uint32_t mantis = getMantissa(float_number);

	while ((mantis & (1 << highest_bit)) == 0 && highest_bit != 0)
		highest_bit--;

	return highest_bit;
}

int32_t getPrecisionLen(enum FloatType float_type)
{
	return (float_type == HalfPrecision) ? 3 : 6;
}

struct FloatNumber getMin(enum FloatType float_type)
{
	struct FloatNumber float_number;
	float_number.float_type = float_type;

	if (float_type == HalfPrecision)
		float_number.precision.half.number = 0xfbff;
	else
		float_number.precision.single.number = 0xff7fffff;

	return float_number;
}

struct FloatNumber getMax(enum FloatType float_type)
{
	struct FloatNumber float_number;
	float_number.float_type = float_type;

	if (float_type == HalfPrecision)
		float_number.precision.half.number = 0x7bff;
	else
		float_number.precision.single.number = 0x7f7fffff;

	return float_number;
}

struct FloatNumber getPositiveInfinity(enum FloatType float_type)
{
	struct FloatNumber float_number;
	float_number.float_type = float_type;

	if (float_type == HalfPrecision)
		float_number.precision.half.number = 0x7c00;
	else
		float_number.precision.single.number = 0x7f800000;

	return float_number;
}

struct FloatNumber getNegativeInfinity(enum FloatType float_type)
{
	struct FloatNumber float_number = getPositiveInfinity(float_type);

	if (float_type == HalfPrecision)
		float_number.precision.half.number |= 0x8000;
	else
		float_number.precision.single.number |= 0x80000000;

	return float_number;
}

struct FloatNumber getPositiveZero(enum FloatType float_type)
{
	struct FloatNumber float_number;
	float_number.float_type = float_type;

	if (float_type == HalfPrecision)
		float_number.precision.half.number = 0x0000;
	else
		float_number.precision.single.number = 0x00000000;

	return float_number;
}

struct FloatNumber getNegativeZero(enum FloatType float_type)
{
	struct FloatNumber float_number;
	float_number.float_type = float_type;

	if (float_type == HalfPrecision)
		float_number.precision.half.number = 0x8000;
	else
		float_number.precision.single.number = 0x80000000;

	return float_number;
}

struct FloatNumber getNaN(enum FloatType float_type)
{
	struct FloatNumber float_number;
	float_number.float_type = float_type;

	if (float_type == HalfPrecision)
		float_number.precision.half.number = 0xfc01;
	else
		float_number.precision.single.number = 0xffc00001;

	return float_number;
}

bool greaterAbs(struct FloatNumber* x, struct FloatNumber* y)
{
	if (getExponent(x) == getExponent(y))
		return getMantissa(x) > getMantissa(y);
	else
		return getExponent(x) > getExponent(y);
}

bool isNaN(struct FloatNumber* float_number)
{
	return getExponent(float_number) == getExponentMask(float_number->float_type) && getMantissa(float_number) != 0;
}

bool isInfinity(struct FloatNumber* float_number)
{
	return getExponent(float_number) == getExponentMask(float_number->float_type) && getMantissa(float_number) == 0;
}

bool isNegative(struct FloatNumber* float_number)
{
	return (float_number->float_type == HalfPrecision)
			 ? float_number->precision.half.bits.sign
			 : float_number->precision.single.bits.sign;
}

bool isZero(struct FloatNumber* float_number)
{
	if (float_number->float_type == HalfPrecision)
		return float_number->precision.half.bits.exponent == 0 && float_number->precision.half.bits.mantis == 0;
	else
		return getExponent(float_number) == 0 && getMantissa(float_number) == 0;
}

bool isDenormalized(struct FloatNumber* float_number)
{
	if (float_number->float_type == HalfPrecision)
		return float_number->precision.half.bits.exponent == 0;
	else
		return getExponent(float_number) == 0 && getMantissa(float_number) != 0;
}
