#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include "zwaveme_libft.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct				ZauxiliaryDiv_s
{
	union
	{
		uint64_t				value;
		struct
		{
			uint32_t			minor;
			uint32_t			major;
		};
	};
}							ZauxiliaryDiv_t;

// Чуть не правильно делит и самое главное - нужно ВСЕ div подменять
// static uint64_t _div(ZauxiliaryDiv_t dividend, ZauxiliaryDiv_t divisor) {
// 	uint32_t					offset;
// 	ZauxiliaryDiv_t				out;
// 	ZauxiliaryDiv_t				saveDivisor;

// 	if (dividend.major == 0) 
// 		return (dividend.minor / divisor.minor);
// 	saveDivisor.minor = divisor.minor;
// 	out.value = 0;
// 	offset = (31 - __builtin_clz(dividend.major)) + __builtin_clz(divisor.minor) + 1;
// 	divisor.value = divisor.value << offset;
// 	while (dividend.major != 0) {
// 		out.minor = out.minor << 1;
// 		if (dividend.value >= divisor.value) {
// 			dividend.value -= divisor.value;
// 			out.minor = out.minor | 1;
// 		}
// 		divisor.value = divisor.value >> 1;
// 	}
// 	out.value = out.value << (offset - 31 + __builtin_clz(out.minor));
// 	out.minor |= dividend.minor / saveDivisor.minor;
// 	return (out.value);
// }

// static uint64_t zdiv(uintmax_t dividend, uintmax_t divisor) {
// 	ZauxiliaryDiv_t				dividendTwo;
// 	ZauxiliaryDiv_t				divisorTwo;

// 	dividendTwo.value = dividend;
// 	divisorTwo.value = divisor;
// 	return (_div(dividendTwo, divisorTwo));
// }

#define SECSPERMIN	60L
#define MINSPERHOUR	60L
#define HOURSPERDAY	24L
#define SECSPERHOUR	(SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY	(SECSPERHOUR * HOURSPERDAY)
#define DAYSPERWEEK	7
#define MONSPERYEAR	12

#define YEAR_BASE	1900
#define EPOCH_YEAR      1970
#define EPOCH_WDAY      4
#define EPOCH_YEARS_SINCE_LEAP 2
#define EPOCH_YEARS_SINCE_CENTURY 70
#define EPOCH_YEARS_SINCE_LEAP_CENTURY 370

#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)

/* Move epoch from 01.01.1970 to 01.03.0000 (yes, Year 0) - this is the first
 * day of a 400-year long "era", right after additional day of leap year.
 * This adjustment is required only for date calculation, so instead of
 * modifying time_t value (which would require 64-bit operations to work
 * correctly) it's enough to adjust the calculated number of days since epoch.
 */
#define EPOCH_ADJUSTMENT_DAYS	719468L
/* year to which the adjustment was made */
#define ADJUSTED_EPOCH_YEAR	0
/* 1st March of year 0 is Wednesday */
#define ADJUSTED_EPOCH_WDAY	3
/* there are 97 leap years in 400-year periods. ((400 - 97) * 365 + 97 * 366) */
#define DAYS_PER_ERA		146097L
/* there are 24 leap years in 100-year periods. ((100 - 24) * 365 + 24 * 366) */
#define DAYS_PER_CENTURY	36524L
/* there is one leap year every 4 years */
#define DAYS_PER_4_YEARS	(3 * 365 + 366)
/* number of days in a non-leap year */
#define DAYS_PER_YEAR		365
/* number of days in January */
#define DAYS_IN_JANUARY		31
/* number of days in non-leap February */
#define DAYS_IN_FEBRUARY	28
/* number of years per era */
#define YEARS_PER_ERA		400

struct tm *gmtime_r(const time_t *tim_p, struct tm *res) {
	long days, rem;
	const time_t lcltime = *tim_p;
	int era, weekday, year;
	unsigned erayear, yearday, month, day;
	unsigned long eraday;

	days = lcltime / SECSPERDAY;
	rem = lcltime % SECSPERDAY;
	days = days + EPOCH_ADJUSTMENT_DAYS;
	if (rem < 0) {
		rem += SECSPERDAY;
		--days;
	}
	/* compute hour, min, and sec */
	res->tm_hour = (int) (rem / SECSPERHOUR);
	rem %= SECSPERHOUR;
	res->tm_min = (int)(rem / SECSPERMIN);
	res->tm_sec = (int)(rem % SECSPERMIN);
	/* compute day of week */
	if ((weekday = ((ADJUSTED_EPOCH_WDAY + days) % DAYSPERWEEK)) < 0)
		weekday += DAYSPERWEEK;
	res->tm_wday = weekday;
	/* compute year, month, day & day of year */
	/* for description of this algorithm see
	* http://howardhinnant.github.io/date_algorithms.html#civil_from_days */
	era = (days >= 0 ? days : days - (DAYS_PER_ERA - 1)) / DAYS_PER_ERA;
	eraday = days - era * DAYS_PER_ERA;/* [0, 146096] */
	erayear = (eraday - eraday / (DAYS_PER_4_YEARS - 1) + eraday / DAYS_PER_CENTURY - eraday / (DAYS_PER_ERA - 1)) / 365;/* [0, 399] */
	yearday = eraday - (DAYS_PER_YEAR * erayear + erayear / 4 - erayear / 100);/* [0, 365] */
	month = (5 * yearday + 2) / 153;/* [0, 11] */
	day = yearday - (153 * month + 2) / 5 + 1;	/* [1, 31] */
	month += month < 10 ? 2 : -10;
	year = ADJUSTED_EPOCH_YEAR + erayear + era * YEARS_PER_ERA + (month <= 1);
	res->tm_yday = yearday >= DAYS_PER_YEAR - DAYS_IN_JANUARY - DAYS_IN_FEBRUARY ? yearday - (DAYS_PER_YEAR - DAYS_IN_JANUARY - DAYS_IN_FEBRUARY) : yearday + DAYS_IN_JANUARY + DAYS_IN_FEBRUARY + isleap(erayear);
	res->tm_year = year - YEAR_BASE;
	res->tm_mon = month;
	res->tm_mday = day;
	res->tm_isdst = 0;
	return (res);
}


#ifdef __cplusplus
}
#endif