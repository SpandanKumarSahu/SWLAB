#ifndef BOOKING_H
#define BOOKING_H

#include <stdio.h>
#include <stdlib.h>
#include "train.h"
#include "mydate.h"

struct booking{
  int bookingID;
  int userID;
  Date bookingDate;
  Train bookedTrain;
};

typedef struct booking Booking;

int postNewBookingData(Booking newBooking){
  FILE *data;
  if ((data = fopen("../data/bookings.txt", "a")) == NULL)
    return 0;
  fwrite(&newBooking,sizeof(Booking),1,data);
  fclose(data);
  return 3;
}

int confirmBookTrain(int userID,int trainNumber,Date bookDate){
  Train tempTrain=getTrainData(trainNumber);
  int bookingID;
  FILE* data;
  if ((data = fopen("../data/bookingID.txt", "rb")) == NULL){
    printf("Error opening file\n");
    return 0;
  }
  fread(&bookingID, sizeof(int), 1, data);
  fclose(data);
  int tempBookingID=bookingID+1;
  if ((data = fopen("../data/bookingID.txt", "w")) == NULL){
    printf("Error opening file\n");
    return 0;
  }
  fwrite(&tempBookingID,sizeof(int),1,data);
  fclose(data);
  
  if(tempTrain.trainSchedule.days[dayofweek(bookDate.day, bookDate.month, bookDate.year)]==1){
    FILE* data;
    if ((data = fopen("../data/bookings.txt", "rb")) != NULL){
      Booking tempBooking;
      while(!feof(data)){
	fread(&tempBooking, sizeof(Booking),1,data);
	if(tempBooking.bookedTrain.trainNumber==trainNumber && dateEqual(tempBooking.bookingDate,bookDate)){
	  fclose(data);
	  return 1;
	}
      }
      fclose(data);      
    }
    Booking newBooking;
    newBooking.bookingID=bookingID;
    newBooking.userID=userID;
    newBooking.bookingDate=bookDate;
    newBooking.bookedTrain=tempTrain;
    return postNewBookingData(newBooking);
  }
  else{
    return 2;
  }
}


int deleteRecordByBookingID(int bookingID) {
  FILE *fp;
  FILE *fp_tmp;
  int found=0;
  Booking tempBooking;

  fp=fopen("../data/bookings.txt", "rb");
  if (!fp)
    return 0;
  fp_tmp=fopen("../data/tmp.txt", "wb");
  if (!fp_tmp)
    return 0;
  
  while (fread(&tempBooking,sizeof(Booking),1,fp) != 0) {
    if (tempBooking.bookingID==bookingID) {
      found=1;
    } else {
      fwrite(&tempBooking, sizeof(Booking), 1, fp_tmp);
    }
  }
  fclose(fp);
  fclose(fp_tmp);

  remove("../data/bookings.txt");
  rename("../data/tmp.txt", "../data/bookings.txt");
  
  if(found)
    return found;
  else return 2;

  return 0;
}

void printBooking(Booking tempBooking){
  printf("%d\t%d/%d/%d\t%d\t%s\t%d:%d\t%s\t%d:%d\t%d\n",tempBooking.bookingID,tempBooking.bookingDate.day,tempBooking.bookingDate.month,tempBooking.bookingDate.year,tempBooking.bookedTrain.trainNumber,tempBooking.bookedTrain.srcStationCode,tempBooking.bookedTrain.departureTime.hours,tempBooking.bookedTrain.departureTime.minutes,tempBooking.bookedTrain.destStationCode,tempBooking.bookedTrain.arrivalTime.hours,tempBooking.bookedTrain.arrivalTime.minutes,tempBooking.bookedTrain.fare);
}

void viewBookingUser(int userID){
  FILE *data;
  if((data=fopen("../data/bookings.txt","rb"))==NULL){
    printf("Error in operations. Inconvenience Regretted.\n");
  }
  else{
    Booking tempBooking;
    printf("Your ID: %d\n", userID);
    printf("BookingID\tBookingDate\tTrainNumber\tSource\tDepartureTime\tDestination\tArrivalTime\tFare\n");
    while(fread(&tempBooking,sizeof(Booking),1,data)!=0){
      if(tempBooking.userID==userID)
	printBooking(tempBooking);
    }
    fclose(data);
  }
}

void viewBookings(){
  FILE *data;
  if((data=fopen("../data/bookings.txt","rb"))==NULL){
    printf("Error in operations. Inconvenience Regretted.\n");
  }
  else{
    Booking tempBooking;
    printf("Admin\n");
    printf("BookingID\tBookingDate\tTrainNumber\tSource\tDepartureTime\tDestination\tArrivalTime\tFare\n");
    while(fread(&tempBooking,sizeof(Booking),1,data)!=0){
      printBooking(tempBooking);
    }
    fclose(data);
  }
}

#endif

