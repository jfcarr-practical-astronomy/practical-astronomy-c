#include "../lib/pa_datetime.h"
#include <math.h>
#include <stdio.h>

#ifndef _pa_test_datetime
#define _pa_test_datetime
void test_date_of_easter(int input_year, TFullDate expected_date);

void test_civil_date_to_day_number(int month, int day, int year,
                                   int expected_day_number);

void test_civil_time_to_decimal_hours(double hours, double minutes,
                                      double seconds,
                                      double expected_decimal_hours);

void test_decimal_hours_to_civil_time(double decimal_hours,
                                      TFullTime expected_civil_time);

void test_local_civil_time_to_universal_time(
    double lct_hours, double lct_minutes, double lct_seconds,
    bool is_daylight_savings, int zone_correction, double local_day,
    int local_month, int local_year, TFullDateTime expected_result);

void test_universal_time_to_local_civil_time(double ut_hours, double ut_minutes,
                                             double ut_seconds,
                                             bool is_daylight_savings,
                                             int zone_correction, int gw_day,
                                             int gw_month, int gw_year,
                                             TFullDateTime expected_result);

void test_universal_time_to_greenwich_sidereal_time(
    double ut_hours, double ut_minutes, double ut_seconds, double gw_day,
    int gw_month, int gw_year, TFullTime expected_result);

void test_greenwich_sidereal_time_to_universal_time(
    double gst_hours, double gst_minutes, double gst_seconds, double gw_day,
    int gw_month, int gw_year, TFullTimeWarning expected_result);

void test_greenwich_sidereal_time_to_local_sidereal_time(
    double gst_hours, double gst_minutes, double gst_seconds,
    double geographical_longitude, TFullTime expected_result);

void test_local_sidereal_time_to_greenwich_sidereal_time(
    double lst_hours, double lst_minutes, double lst_seconds,
    double geographical_longitude, TFullTime expected_result);
#endif