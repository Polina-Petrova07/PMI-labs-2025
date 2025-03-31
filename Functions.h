#pragma once

#include "math.h"
#include "stdio.h"
#include "locale.h"


double sin_teilor_pr(double value_x, int len_teilor);

double sin_teilor_obr(double value_x, int len_teilor);

double cos_teilor_pr(double value_x, int len_teilor);

double cos_teilor_obr(double value_x, int len_teilor);

double exp_teilor_pr(double value_x, int len_teilor);

double exp_teilor_obr(double value_x, int len_teilor);

double log_teilor_pr(double value_x, int len_teilor);

double log_teilor_obr(double value_x, int len_teilor);