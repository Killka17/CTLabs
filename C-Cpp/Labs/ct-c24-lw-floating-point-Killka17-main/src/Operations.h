#ifndef OPERATIONS_
#define OPERATIONS_

#include "FloatUtils.h"

uint64_t roundByRemainder(uint64_t mantissa, uint64_t remainder, uint64_t divider, bool is_negative, enum RoundType round_type);
uint64_t roundByShift(uint64_t mantissa, uint64_t remainder, int32_t shift, bool is_negative, bool sign, enum RoundType round_type);

struct FloatNumber getOverflowResult(bool is_negative, enum RoundType round_type, enum FloatType float_type);

struct FloatNumber checkFloatNumbers(struct FloatNumber* x, struct FloatNumber* y);

uint32_t normalizationFloat(struct FloatNumber* float_number, int32_t* exponent, bool is_less);

struct FloatNumber floatAddition(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type);
struct FloatNumber floatSubtract(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type);
struct FloatNumber floatMultiply(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type);
struct FloatNumber floatDivide(struct FloatNumber* x, struct FloatNumber* y, enum RoundType round_type);

#endif
