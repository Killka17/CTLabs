#include "src/FloatIO.h"

int main(int argc, char** argv)
{
	struct ReadExpression read_number;

	read_number = ReadArguments(argc, argv);

	if (read_number.status != Success)
		return ERROR_ARGUMENTS_INVALID;

	switch (read_number.operation)
	{
	case Multiply:
		PrintFloat(floatMultiply(&read_number.first_number, &read_number.second_number, read_number.round_type));
		break;
	case Additional:
		PrintFloat(floatAddition(&read_number.first_number, &read_number.second_number, read_number.round_type));
		break;
	case Subtract:
		PrintFloat(floatSubtract(&read_number.first_number, &read_number.second_number, read_number.round_type));
		break;
	case Divide:
		PrintFloat(floatDivide(&read_number.first_number, &read_number.second_number, read_number.round_type));
		break;
	default:
		PrintFloat(read_number.first_number);
	}

	return 0;
}
