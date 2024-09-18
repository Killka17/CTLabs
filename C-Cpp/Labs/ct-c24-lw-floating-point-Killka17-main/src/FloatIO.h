#ifndef READ_EXPRESSION_
#define READ_EXPRESSION_

#include "Operations.h"
#include "return_codes.h"

#include <stdio.h>
#include <stdlib.h>

struct ReadExpression
{
	struct FloatNumber first_number;
	struct FloatNumber second_number;
	enum Operation operation;
	enum FloatType float_type;
	enum RoundType round_type;
	enum ArgReadStatus status;
};

struct ReadExpression* CheckReadExpression(struct ReadExpression*);
struct ReadExpression ReadArguments(int, char**);

int count_digits(uint64_t number);

void PrintFloat(struct FloatNumber float_number);

#endif
