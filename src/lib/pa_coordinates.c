#include "pa_datetime.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <math.h>
#include <stdio.h>

/**
 * Convert Angle (degrees,minutes,seconds) to Decimal Degrees
 */
double angle_to_decimal_degrees(double degrees, double minutes,
                                double seconds) {
  double a = fabs(seconds) / 60;
  double b = (fabs(minutes) + a) / 60;
  double c = fabs(degrees) + b;
  double d = (degrees < 0 || minutes < 0 || seconds < 0) ? -c : c;

  return d;
}

/**
 * Convert Decimal Degrees to an Angle (degrees, minutes, and seconds)
 */
TAngle decimal_degrees_to_angle(double decimal_degrees) {
  double unsigned_decimal = fabs(decimal_degrees);
  double total_seconds = unsigned_decimal * 3600;
  double seconds2_dp = dround(fmod(total_seconds, 60), 2);
  double corrected_seconds = (seconds2_dp == 60) ? 0 : seconds2_dp;
  double corrected_remainder =
      (seconds2_dp == 60) ? total_seconds + 60 : total_seconds;
  double minutes = fmod(floor(corrected_remainder / 60), 60);
  double unsigned_degrees = floor(corrected_remainder / 3600);
  double signed_degrees =
      (decimal_degrees < 0) ? -1 * unsigned_degrees : unsigned_degrees;

  return (TAngle){signed_degrees, minutes, floor(corrected_seconds)};
}

/**
 * Convert Right Ascension to Hour Angle
 *
 * @return THourAngle <double hour_angle_hours, double hour_angle_minutes,
 * double hour_angle_seconds>
 */
THourAngle right_ascension_to_hour_angle(double ra_hours, double ra_minutes,
                                         double ra_seconds, double lct_hours,
                                         double lct_minutes, double lct_seconds,
                                         bool is_daylight_savings,
                                         int zone_correction, double local_day,
                                         int local_month, int local_year,
                                         double geographical_longitude) {
  int daylight_saving = (is_daylight_savings) ? 1 : 0;

  double hour_angle = right_ascension_to_hour_angle_macro(
      ra_hours, ra_minutes, ra_seconds, lct_hours, lct_minutes, lct_seconds,
      daylight_saving, zone_correction, local_day, local_month, local_year,
      geographical_longitude);

  int hour_angle_hours = decimal_hours_hour(hour_angle);
  int hour_angle_minutes = decimal_hours_minute(hour_angle);
  double hour_angle_seconds = decimal_hours_second(hour_angle);

  return (THourAngle){hour_angle_hours, hour_angle_minutes, hour_angle_seconds};
}

/**
 * \brief Convert Hour Angle to Right Ascension
 *
 * @return TRightAscension <double right_ascension_hours, double
 * right_ascension_minutes, double right_ascension_seconds>
 */
TRightAscension hour_angle_to_right_ascension(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double lct_hours, double lct_minutes,
    double lct_seconds, bool is_daylight_savings, int zone_correction,
    double local_day, int local_month, int local_year,
    double geographical_longitude) {
  int daylight_saving = (is_daylight_savings) ? 1 : 0;

  double right_ascension = hour_angle_to_right_ascension_macro(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds, lct_hours,
      lct_minutes, lct_seconds, daylight_saving, zone_correction, local_day,
      local_month, local_year, geographical_longitude);

  int right_ascension_hours = decimal_hours_hour(right_ascension);
  int right_ascension_minutes = decimal_hours_minute(right_ascension);
  int right_ascension_seconds = decimal_hours_second(right_ascension);

  return (TRightAscension){right_ascension_hours, right_ascension_minutes,
                           right_ascension_seconds};
}

/**
 * Convert Equatorial Coordinates to Horizon Coordinates
 *
 * @return THorizonCoordinates <double azimuthDegrees, double azimuthMinutes,
 * double azimuthSeconds, double altitudeDegrees, double altitudeMinutes, double
 * altitudeSeconds>
 */
THorizonCoordinates equatorial_coordinates_to_horizon_coordinates(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double declination_degrees,
    double declination_minutes, double declination_seconds,
    double geographical_latitude) {
  double azimuth_in_decimal_degrees = equatorial_coordinates_to_azimuth(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds,
      geographical_latitude);

  double altitude_in_decimal_degrees = equatorial_coordinates_to_altitude(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds,
      geographical_latitude);

  double azimuth_degrees = decimal_degrees_degrees(azimuth_in_decimal_degrees);
  double azimuth_minutes = decimal_degrees_minutes(azimuth_in_decimal_degrees);
  double azimuth_seconds = decimal_degrees_seconds(azimuth_in_decimal_degrees);

  double altitude_degrees =
      decimal_degrees_degrees(altitude_in_decimal_degrees);
  double altitude_minutes =
      decimal_degrees_minutes(altitude_in_decimal_degrees);
  double altitude_seconds =
      decimal_degrees_seconds(altitude_in_decimal_degrees);

  return (THorizonCoordinates){azimuth_degrees,  azimuth_minutes,
                               azimuth_seconds,  altitude_degrees,
                               altitude_minutes, altitude_seconds};
}

/**
 * Convert Horizon Coordinates to Equatorial Coordinates
 *
 * @return TEquatorialCoordinates <double hour_angle_hours, double
 * hour_angle_minutes, double hour_angle_seconds, double declination_degrees,
 * double declination_minutes, double declination_seconds>
 */
TEquatorialCoordinates horizon_coordinates_to_equatorial_coordinates(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude) {
  double hour_angle_in_decimal_degrees = horizon_coordinates_to_hour_angle(
      azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
      altitude_minutes, altitude_seconds, geographical_latitude);

  double declination_in_decimal_degrees = horizon_coordinates_to_declination(
      azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
      altitude_minutes, altitude_seconds, geographical_latitude);

  int hour_angle_hours = decimal_hours_hour(hour_angle_in_decimal_degrees);
  int hour_angle_minutes = decimal_hours_minute(hour_angle_in_decimal_degrees);
  double hour_angle_seconds =
      decimal_hours_second(hour_angle_in_decimal_degrees);

  double declination_degrees =
      decimal_degrees_degrees(declination_in_decimal_degrees);
  double declination_minutes =
      decimal_degrees_minutes(declination_in_decimal_degrees);
  double declination_seconds =
      decimal_degrees_seconds(declination_in_decimal_degrees);

  return (TEquatorialCoordinates){hour_angle_hours,    hour_angle_minutes,
                                  hour_angle_seconds,  declination_degrees,
                                  declination_minutes, declination_seconds};
}
