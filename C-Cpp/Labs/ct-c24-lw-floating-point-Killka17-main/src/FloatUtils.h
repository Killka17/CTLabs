#ifndef FLOAT_UTILS_
#define FLOAT_UTILS_

#include "Float.h"

uint32_t getExponentMask(enum FloatType float_type);
uint32_t getMantissaMask(enum FloatType float_type);
uint32_t getMaxExponent(enum FloatType float_type);
uint32_t getMaxMantissa(enum FloatType float_type);
uint32_t getMantissa(struct FloatNumber* float_number);
uint32_t getExponent(struct FloatNumber* float_number);
uint32_t getSign(struct FloatNumber* float_number);
uint32_t getHighestBit(struct FloatNumber* float_number);
int32_t getPrecisionLen(enum FloatType float_type);

struct FloatNumber getMin(enum FloatType float_type);
struct FloatNumber getMax(enum FloatType float_type);

struct FloatNumber getPositiveInfinity(enum FloatType float_type);
struct FloatNumber getNegativeInfinity(enum FloatType float_type);
struct FloatNumber getPositiveZero(enum FloatType float_type);
struct FloatNumber getNegativeZero(enum FloatType float_type);
struct FloatNumber getNaN(enum FloatType float_type);

bool greaterAbs(struct FloatNumber* x, struct FloatNumber* y);

bool isNaN(struct FloatNumber* float_number);
bool isInfinity(struct FloatNumber* float_number);
bool isNegative(struct FloatNumber* float_number);
bool isZero(struct FloatNumber* float_number);
bool isDenormalized(struct FloatNumber* float_number);

#endif
