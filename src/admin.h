#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include "train.h"
#include "booking.h"

void printPortalAdmin(){
  printf("Welcome to Cargo Management System.\n");
  printf("Press: \n");
  printf("1 for Adding a train\n");
  printf("2 for Cancelling a train\n");
  printf("3 for Removing a train permanently.\n");
  printf("4 for Viewing all Bookings. \n");
  printf("5 for exit.\n");
  printf("Your choice : ");
}

void cancelTrain(){
}

void removeTrain(){
  //Currently not implemented.
  //When you remove a train, remove all its dependencies(bookings).
  printf("Currently this is not implemented.\n");
}


void makeChoiceAdmin(int choice){
  int errorCode;
  int bookingID;
  switch(choice){
  case 1: 
    errorCode=inputNewTrain();
    if(errorCode==0)
      printf("Sorry, the train couldnot be added.\n");
    break;
  case 2:
    printf("Enter the booking ID of the reservation which you wish to cancel: ");
    scanf("%d",&bookingID);
    errorCode=deleteRecordByBookingID(bookingID);
    switch(errorCode){
    case 0:
      printf("Error in operations. Inconvenience regretted.\n");
      break;
    case 1:
      printf("Successfully deleted the record.\n");
      break;
    default:
      printf("Unknown error. Please report this to admin.\n");
      break;
    } 
    break;
  case 3:
    removeTrain();
    break;
  case 4:
    viewBookings();
    break;
  default:
    break;
  }
} 

void mainAdmin(){
  int choice;
  do{
    printPortalAdmin();
    scanf("%d", &choice);
    makeChoiceAdmin(choice);
  }while(choice <=5 && choice>=1);
}

#endif
 
