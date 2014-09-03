#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define BOOK_TIME 54

char *months[12] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int month2int(char month[10]) {
	int month_int = -1, i = 0, l = 0;

	for (i = 0, l = 12; i < l; i++) {
		if (strcmp(month, months[i]) == 0) {
			return i;
		}
	}

	return month_int;
}

void usage() {
	printf("Usage: getaway [-h]|[-r] [\"date\"] [book_time]\n");
}

int main(int argc, char *argv[]) {
	int rc = 0, arg = 1, book_time = BOOK_TIME, reverse = 1;
	int this_day = 0, this_month = 0, this_year = 0;
	int day = 0, month = 0, year = 0, leapyear = 0;
	char *date = NULL, *pattern = NULL, month_str[10];
	time_t rawtime;
	struct tm *str_time;

	time(&rawtime);
	str_time = localtime(&rawtime);

	this_day = str_time->tm_mday;
	this_month = str_time->tm_mon;
	this_year = str_time->tm_year + 1900;

	if (argc > 1) {
		if (strcmp(argv[arg], "-h") == 0) {
			usage();

			rc = 1;
			goto cleanup;
		} else if (strcmp(argv[arg], "-r") == 0) {
			arg++;

			if (arg < argc) {
				date = argv[arg++];
			}

			reverse = -1;
		} else {
			date = argv[arg++];
		}

		if (arg < argc) {
			book_time = atoi(argv[arg]);
		}

		if (date) {
			pattern = strstr(date, ",") ? "%s %d, %d" : "%s %d %d";
			sscanf(date, pattern, month_str, &day, &year);
			month = month2int(month_str);
		}
	}

	if (!date) {
		day = this_day;
		month = this_month;
		year = this_year;
	}

	leapyear = year % 4;
	days[1] = (leapyear) ? 29 : 28;

	day += (book_time * reverse);

	while (day > days[month]) {
		day -= days[month];
		month++;
	}

	while (day < 0) {
		month--;

		if (month < 0) {
			month = 11;
			year--;

			leapyear = year % 4;
			days[1] = (leapyear) ? 29 : 28;
		}

		day += days[month];
	}

	if (month >= 12) {
		month = 0;
		year++;
	}

	printf("%s %d, %d\n", months[month], day, year);

cleanup:
	return rc;
}