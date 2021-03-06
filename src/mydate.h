#ifndef MYDATE_H
#define MYDATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct date{
  int day;
  int month;
  int year;
};

typedef struct date Date;

struct time{
  int hours;
  int minutes;
};

typedef struct time Time;

// 0 for Sunday and 6 for Saturday.

struct schedule{
  bool days[7];
};

typedef struct schedule Schedule;

void fill_schedule(Schedule *ptr){
  printf("\n Now enter 7 numbers(space seperated) indicating the days on which the train runs.\n");
  printf("1 if it runs on the day, 0 otherwise. Start from Sunday.");
  for(int i=0;i<7;i++)
    scanf("%d",&(ptr->days[i]));
}

void fill_time(Time *ptr, char *s){
  printf("Enter hours , minutes of %s time ( in hh mm format) ", s);
  scanf("%d %d", &(ptr->hours), &(ptr->minutes));
}

void fill_date(Date *ptr){
  printf("Enter Day: ");
  scanf("%d",&(ptr->day));
  printf("Enter Month: ");
  scanf("%d",&(ptr->month));
  printf("Enter Year: ");
  scanf("%d",&(ptr->year));
}

int dayofweek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int dateEqual(Date date1, Date date2){
  return (date1.year==date2.year && date1.month==date2.month && date1.day==date2.day);
}

#endif

