#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef _pa_lib_util
#define _pa_lib_util

bool is_leap_year(int input_year);

double dround(double input, int places);

double degrees_to_radians(double degrees);

double radians_to_degrees(double radians);
#endif
