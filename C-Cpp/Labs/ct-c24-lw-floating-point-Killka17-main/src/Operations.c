#include "Operations.h"

uint64_t roundByRemainder(uint64_t mantissa, uint64_t remainder, uint64_t divider, bool is_negative, enum RoundType round_type)
{
	uint64_t comparison_divider = (divider & 1) == 0 ? (divider >> 1) : divider;
	uint64_t comparison_remainder = (divider & 1) == 0 ? remainder : (remainder << 1);

	switch (round_type)
	{
	case TowardZero:
	{
		break;
	}
	case TowardNearestEven:
	{
		if (comparison_remainder > comparison_divider || (comparison_remainder == comparison_divider && (mantissa & 1) != 0))
			++mantissa;
		break;
	}
	case TowardPosInfinity:
	{
		if (!is_negative && remainder != 0)
			++mantissa;
		break;
	}
	case TowardNegInfinity:
	{
		if (is_negative && remainder != 0)
			++mantissa;
		break;
	}
	}

	return mantissa;
}

uint64_t roundByShift(uint64_t mantissa, uint64_t remainder, int32_t shift, bool is_negative, bool sign, enum RoundType round_type)
{
	switch (round_type)
	{
	case TowardZero:
	{
		break;
	}
	case TowardNearestEven:
	{
		if (remainder & (1 << (shift - 1)) &&
			(remainder & ((1 << (shift - 1)) - 1)) | (remainder & (1 << (shift - 1)) && (mantissa & 1)))
			++mantissa;
		break;
	}
	case TowardPosInfinity:
	{
		if (!is_negative && remainder != 0)
			++mantissa;
		break;
	}
	case TowardNegInfinity:
	{
		if (is_negative && remainder != 0)
		{
			if (!sign)
				--mantissa;
			else
				++mantissa;
		}
		break;
	}
	}

	return mantissa;
}

struct FloatNumber getOverflowResult(bool is_negative, enum RoundType round_type, enum FloatType float_type)
{
	switch (round_type)
	{
	case TowardZero:
	{
		if (is_negative)
			return getMin(float_type);

		return getMax(float_type);
	}
	case TowardNearestEven:
	{
		if (is_negative)
			return getNegativeInfinity(float_type);

		return getPositiveInfinity(float_type);
	}
	case TowardPosInfinity:
	{
		if (is_negative)
			return getMin(float_type);

		return getPositiveInfinity(float_type);
	}
	case TowardNegInfinity:
	{
		if (is_negative)
			return getNegativeInfinity(float_type);

		return getMax(float_type);
	}
	}
}

struct FloatNumber checkFloatNumbers(struct FloatNumber* x, struct FloatNumber* y)
{
	enum FloatType float_type = x->float_type;

	if (isNaN(x))
	{
		return getNaN(float_type);
	}

	if (isNaN(y))
	{
		return getNaN(float_type);
	}

	if (isInfinity(x) || isInfinity(y))
	{
		if (isZero(x) || isZero(y))
			return getNaN(float_type);

		if (isNegative(x) == isNegative(y))
		{
			return getPositiveInfinity(float_type);
		}

		return getNegativeInfinity(float_type);
	}

	if (isZero(x) || isZero(y))
	{
		if (isNegative(x) == isNegative(y))
		{
			return getPositiveZero(float_type);
		}

		return getNegativeZero(float_type);
	}

	return *x;
}

uint32_t normalizationFloat(struct FloatNumber* float_number, int32_t* exponent, bool is_less)
{
	if (!isDenormalized(float_number))
	{
		uint32_t mantissa = getMantissa(float_number);

		if (is_less)
			mantissa |= (1 << (float_number->float_type == HalfPrecision ? BITS_MANTIS_HPF : BITS_MANTIS_SPF));

		return mantissa;
	}

	int32_t shift =
		(int32_t)((float_number->float_type == HalfPrecision)
					  ? (BITS_MANTIS_HPF - getHighestBit(float_number))
					  : (BITS_MANTIS_SPF - getHighestBit(float_number)));

	if (shift == (float_number->float_type == HalfPrecision ? BITS_MANTIS_HPF : BITS_MANTIS_SPF))
		return getMantissa(float_number);

	if (float_number->float_type == HalfPrecision)
	{
		*exponent -= shift;
		return float_number->precision.half.bits.mantis << shift;
	}
	else
	{
		*exponent -= shift;
		return float_number->precision.single.bits.mantis << shift;
	}
}

struct FloatNumber floatAddition(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type)
{
	if (x->float_type != y->float_type)
		return getNaN(x->float_type);

	struct FloatNumber check_numbers = checkFloatNumbers(x, y);
	if (check_numbers.precision.single.number != x->precision.single.number)
		return check_numbers;

	enum FloatType float_type = x->float_type;
	int32_t bits_mantis = float_type == SinglePrecision ? BITS_MANTIS_SPF : BITS_MANTIS_HPF;
	int32_t bits_exponent = float_type == SinglePrecision ? BITS_EXPONENT_SPF : BITS_EXPONENT_HPF;

	struct FloatNumber* less_number = greaterAbs(x, y) ? y : x;
	struct FloatNumber* greater_number = less_number == x ? y : x;

	int32_t less_exponent = (int32_t)getExponent(less_number);
	int32_t greater_exponent = (int32_t)getExponent(greater_number);

	uint64_t less_mantissa = normalizationFloat(less_number, &less_exponent, 1);
	uint32_t greater_mantissa = normalizationFloat(greater_number, &greater_exponent, 0);

	int32_t diff_exponent = greater_exponent - less_exponent;
	struct FloatNumber float_number;
	float_number.float_type = float_type;

	uint64_t reminder = less_mantissa & ((1 << (diff_exponent >= 64 ? 63 : diff_exponent)) - 1);
	less_mantissa >>= (diff_exponent >= 32 ? 31 : diff_exponent);

	bool sign = isNegative(x) ^ isNegative(y);
	less_mantissa = roundByShift(less_mantissa, reminder, diff_exponent, isNegative(less_number), sign, round_type);

	if (!sign)
		less_mantissa += greater_mantissa;
	else
		less_mantissa = (greater_mantissa < less_mantissa ? less_mantissa : greater_mantissa) -
						(greater_mantissa < less_mantissa ? greater_mantissa : less_mantissa);

	int32_t value_exponent = greater_exponent;

	if (sign && reminder && round_type == TowardZero)
		less_mantissa--;

	if (sign && isNegative(less_number))
		sign = 0;
	if (!sign && isNegative(less_number) && isNegative(greater_number))
		sign = 1;

	if (less_mantissa > getMaxMantissa(float_type))
	{
		less_mantissa &= (1 << bits_mantis) - 1;
		less_mantissa >>= 1;
		value_exponent++;
	}

	if (value_exponent > (int32_t)getMaxExponent(float_type) * 2)
		return getPositiveInfinity(float_type);

	if (value_exponent < 0)
		return getNegativeInfinity(float_type);

	float_number.precision.single.number = less_mantissa | (value_exponent << bits_mantis) | (sign << (bits_mantis + bits_exponent));

	return float_number;
}

struct FloatNumber floatSubtract(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type)
{
	if (y->float_type == HalfPrecision)
		y->precision.half.bits.sign ^= 1;
	else
		y->precision.single.bits.sign ^= 1;

	return floatAddition(x, y, round_type);
}

struct FloatNumber floatMultiply(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type)
{
	if (x->float_type != y->float_type)
		return getNaN(x->float_type);

	enum FloatType float_type = x->float_type;
	int32_t bits_mantis = float_type == SinglePrecision ? BITS_MANTIS_SPF : BITS_MANTIS_HPF;
	int32_t bits_exponent = float_type == SinglePrecision ? BITS_EXPONENT_SPF : BITS_EXPONENT_HPF;

	struct FloatNumber check_numbers = checkFloatNumbers(x, y);
	if (check_numbers.precision.single.number != x->precision.single.number)
		return check_numbers;

	uint64_t x_mantis = getMantissa(x);
	uint64_t y_mantis = getMantissa(y);
	int64_t x_exponent = (int64_t)getExponent(x) - getMaxExponent(float_type);
	int64_t y_exponent = (int64_t)getExponent(y) - getMaxExponent(float_type);

	if (x_exponent != -(int64_t)(getMaxExponent(float_type)))
	{
		x_mantis |= (1ll << bits_mantis);
	}
	else
	{
		++x_exponent;
	}

	if (y_exponent != -(int64_t)(getMaxExponent(float_type)))
	{
		y_mantis |= (1ll << bits_mantis);
	}
	else
	{
		++y_exponent;
	}

	uint64_t value_mantis = x_mantis * y_mantis;
	uint64_t old_mantis = value_mantis;
	int64_t value_exponent = x_exponent + y_exponent;
	value_exponent += getMaxExponent(float_type);
	int64_t mantis_divider_exponent = 0;
	bool value_is_negative = isNegative(x) ^ isNegative(y);

	while ((value_mantis >> (2 * bits_mantis)) != 1)
	{
		if ((value_mantis >> (2 * bits_mantis)) > 1)
		{
			value_mantis >>= 1;
			++value_exponent;
			++mantis_divider_exponent;
		}
		else
		{
			if (value_exponent <= 0)
			{
				break;
			}

			value_mantis <<= 1;
			--value_exponent;
			--mantis_divider_exponent;
		}
	}

	if (value_exponent <= 0)
	{
		int64_t shift = (int64_t)(63l) < -value_exponent + 1 ? (int64_t)(63l) : -value_exponent + 1;
		value_mantis >>= shift;
		mantis_divider_exponent += shift;
		value_exponent = 0;
	}

	value_mantis >>= bits_mantis;
	mantis_divider_exponent += bits_mantis;
	uint64_t divider = 1ll << ((int64_t)(63l) < mantis_divider_exponent ? (int64_t)(63l) : mantis_divider_exponent);
	uint64_t remainder = old_mantis & (divider - 1);
	value_mantis = roundByRemainder(value_mantis, remainder, divider, value_is_negative, round_type);

	value_mantis &= getMantissaMask(float_type);

	if (value_exponent >= getExponentMask(float_type))
	{
		return getOverflowResult(value_is_negative, round_type, float_type);
	}

	int32_t sign_shift = bits_mantis + bits_exponent;

	struct FloatNumber float_number;
	float_number.float_type = float_type;

	if (float_type == HalfPrecision)
		float_number.precision.half.number = value_mantis | (value_exponent << bits_mantis) | (value_is_negative << sign_shift);
	else
		float_number.precision.single.number = value_mantis | (value_exponent << bits_mantis) | (value_is_negative << sign_shift);

	return float_number;
}

struct FloatNumber floatDivide(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type)
{
	if (x->float_type != y->float_type)
		return getNaN(x->float_type);

	enum FloatType float_type = x->float_type;
	int32_t bits_mantis = float_type == SinglePrecision ? BITS_MANTIS_SPF : BITS_MANTIS_HPF;
	int32_t bits_exponent = float_type == SinglePrecision ? BITS_EXPONENT_SPF : BITS_EXPONENT_HPF;
	bool sign = getSign(x) ^ getSign(y);

	if ((isNaN(x) || isNaN(y)) || (isZero(x) && isZero(y)) || (isInfinity(x) && isInfinity(y)))
		return getNaN(x->float_type);

	if (isZero(y))
		return getPositiveInfinity(float_type);

	if (isInfinity(y))
		return getPositiveZero(float_type);

	if (isInfinity(x))
		return *x;

	uint64_t x_mantis = getMantissa(x);
	uint64_t y_mantis = getMantissa(y);

	int64_t x_exponent = (int64_t)getExponent(x);
	int64_t y_exponent = (int64_t)getExponent(y);

	int64_t new_exponent = (x_exponent - y_exponent) + getMaxExponent(float_type);
	x_mantis = (x_mantis | ((1 << bits_mantis)) * (x_exponent > 0));
	y_mantis = (y_mantis | ((1 << bits_mantis)) * (y_exponent > 0));

	uint64_t new_mantissa = (x_mantis << (bits_mantis + 1)) / y_mantis;

	if ((x_mantis << (bits_mantis + 1)) != new_mantissa * y_mantis)
		new_mantissa++;

	if (new_mantissa & (1 << (bits_mantis + 1)))
	{
		if (round_type == TowardZero)
			new_mantissa--;
		else
			new_mantissa = roundByShift(new_mantissa, 1, bits_mantis, sign, sign, round_type);

		new_mantissa >>= 1;
	}
	else
	{
		new_exponent--;
	}

	new_mantissa &= (1 << bits_mantis) - 1;

	struct FloatNumber result_number;
	result_number.float_type = float_type;

	result_number.precision.single.number = new_mantissa | (new_exponent << bits_mantis) | (sign << (bits_mantis + bits_exponent));

	return result_number;
}
