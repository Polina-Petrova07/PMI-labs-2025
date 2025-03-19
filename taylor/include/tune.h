#pragma once

#include "double4.h"

#define ALLOCA_CUTOFF_TERMS 512
#define PREC "18"


#include <assert.h>
#include <limits.h>
#include <stdint.h>
static_assert(0 < LANE_WIDTH && LANE_WIDTH <= UINT_MAX        , "invalid lane width"     );
static_assert(SIZE_MAX / sizeof(double4) > ALLOCA_CUTOFF_TERMS, "invalid alloca() cutoff");
