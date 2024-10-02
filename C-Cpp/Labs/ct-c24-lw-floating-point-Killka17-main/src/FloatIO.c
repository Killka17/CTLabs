#include "FloatIO.h"

int count_digits(uint64_t number)
{
	int count = 1;
	while (number /= 16)
	{
		count++;
	}
	return count;
}

void PrintFloat(struct FloatNumber float_number)
{
	if (isInfinity(&float_number))
	{
		if (isNegative(&float_number))
			printf("-");

		printf("inf");
		return;
	}

	if (isNaN(&float_number))
	{
		printf("nan");
		return;
	}

	if (isZero(&float_number))
	{
		if (isNegative(&float_number))
			printf("-");

		printf("0x0.");
		for (int i = 0; i < getPrecisionLen(float_number.float_type); ++i)
			printf("0");

		printf("p+0");
		return;
	}

	uint32_t mantis = getMantissa(&float_number);
	uint32_t exponent = (int32_t)getExponent(&float_number);
	int32_t bit_mantis = float_number.float_type == HalfPrecision ? BITS_MANTIS_HPF : BITS_MANTIS_SPF;

	if (isDenormalized(&float_number))
	{
		while ((mantis >> bit_mantis) == 0)
		{
			mantis <<= 1;
			--exponent;
		}

		++exponent;
		mantis &= getMantissaMask(float_number.float_type);
	}

	uint64_t mantis_out = mantis << (4 * getPrecisionLen(float_number.float_type) - bit_mantis);
	int32_t exponent_output = ((int32_t)exponent) - (float_number.float_type == SinglePrecision ? 127 : 15);

	if (isNegative(&float_number))
		printf("-");

	int32_t shift_mantis = getPrecisionLen(float_number.float_type) - count_digits(mantis_out);
	if (shift_mantis > 0)
	{
		printf("0x1.");
		for (int i = 0; i < shift_mantis; ++i)
			printf("0");

		printf("%lxp", mantis_out);
	}
	else
		printf("0x1.%lxp", mantis_out);

	if (exponent_output >= 0)
		printf("+");

	printf("%d\n", exponent_output);
}

struct ReadExpression* CheckReadExpression(struct ReadExpression* read_expression)
{
	if (read_expression->float_type != HalfPrecision && read_expression->float_type != SinglePrecision)
	{
		fprintf(stderr, "Incorrect format");
		read_expression->status = Failed;
	}
	else if ((int32_t)read_expression->round_type < (int32_t)0 || (int32_t)read_expression->round_type > (int32_t)3)
	{
		fprintf(stderr, "Incorrect rounding");
		read_expression->status = Failed;
	}
	else if (read_expression->operation != Not && read_expression->operation != Additional && read_expression->operation != Multiply &&
			 read_expression->operation != Subtract && read_expression->operation != Divide)
	{
		fprintf(stderr, "Invalid operation");
		read_expression->status = Failed;
	}

	return read_expression;
}

struct ReadExpression ReadArguments(const int argc, char** argv)
{
	struct ReadExpression read_number = { .operation = Not };

	if (argc < 2)
	{
		fprintf(stderr, "no arguments");
		return *CheckReadExpression(&read_number);
	}

	uint32_t arg_num = 1;
	char float_type;
	char operation;

	sscanf(argv[arg_num++], "%c", &float_type);
	read_number.float_type = (int32_t)float_type;
	read_number.first_number.float_type = (int32_t)float_type;

	sscanf(argv[arg_num++], "%d", &read_number.round_type);

	sscanf(argv[arg_num++], " 0x%x", &read_number.first_number.precision.single.number);

	if (argc > 4)
	{
		read_number.second_number.float_type = (int32_t)float_type;

		sscanf(argv[arg_num++], "%c", &operation);
		read_number.operation = (int32_t)operation;

		sscanf(argv[arg_num], "0x%x", &read_number.second_number.precision.single.number);
	}

	read_number.status = Success;

	return *CheckReadExpression(&read_number);
}
