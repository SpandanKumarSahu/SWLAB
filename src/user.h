#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"
#include "booking.h"

struct user{
  char name[30];
  char password[30];
  int url;
};

typedef struct user User;

int verifyUser(User user){
  FILE* data;
  if ((data = fopen("../data/users.txt", "rb")) == NULL){
    printf("Error opening file\n");
    return 0;
  }
  User tempUser;
  while(fread(&tempUser,sizeof(tempUser),1,data)!=0){
    if(strcmp(tempUser.name,user.name)==0 && strcmp(tempUser.password, user.password)==0)
      return 1;
  }
  return 0;	
}

int postNewUserData(User user){
  FILE* data;
  if ( (data = fopen("../data/users.txt", "a")) == NULL ){
    printf("Error opening file\n");
    return 0;   
  }
  fseek(data, user.url* sizeof(User), SEEK_SET);
  fwrite(&user, sizeof(User), 1, data);
  fclose(data);
  return 1;
}

void printPortalUser(){
  printf("Welcome to Cargo Management System.\n");
  printf("Press: \n");
  printf("1 for Booking a train\n");
  printf("2 for Cancelling a booking\n");
  printf("3 for viewing your booking status\n");
  printf("4 for exit.\n");
  printf("Your choice : ");
}

void bookTrain(User user){
  char src[5],dest[5];
  printf("Enter Source Station Code: ");
  fflush(stdin);
  scanf("%s",src);
  printf("Enter Destination Station Code: ");
  fflush(stdin);
  scanf("%s",dest);
  displayTrainBySrcDest(src,dest);
  printf("\nEnter the train number of the train you wish to book (Press 0 to exit): ");
  int trainNumber;
  scanf("%d",&trainNumber);
  if(trainNumber==0){
    printf("Going Back. Booking forefeited\n");
  }
  else{
    Date bookDate;
    printf("Enter booking date\n");
    fill_date(&bookDate);
    int bookingConfirmation;
    bookingConfirmation=confirmBookTrain(user.url,trainNumber,bookDate);
    if(bookingConfirmation==0)
      printf("Unsuccessful Attempt to book the train. Forefeiting the process.\n");
    else if(bookingConfirmation==1)
      printf("The train is already booked for the date. Forefeiting and returning to main page.\n");
    else if(bookingConfirmation==2)
      printf("The train doesn't run on the given date. Please review. Forefeiting the process.\n");
    else
      printf("Transaction Succesful. Thanks for using our service. Proceeding to main page.\n");
  }
}

void cancelBooking(User user){
  int bookingID;
  printf("Enter the Booking ID which you wish to cancel");
  printf("%d",bookingID);
  FILE *data;
  if((data=fopen("../data/bookings.txt","rb"))==NULL)
     printf("Error in opening data.\n");
  else{
    bool access=false;
    Booking tempBooking;
 
    while(fread(&tempBooking,sizeof(Booking),1,data)!=0){
      if(tempBooking.userID==user.url && tempBooking.bookingID==bookingID){
	fclose(data);
	access=true;
      }
    }
    if(access){
      int errorCode=deleteRecordByBookingID(bookingID);
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
    }
    else{
      printf("Access Denied. Either the bookingID is incorrect or you are not the one who made the booking.\n");
    }
  }
}

void makeChoiceUser(int choice,User user){
  switch(choice){
  case 1: 
    bookTrain(user);
    break;
  case 2:
    cancelBooking(user);
    break;
  case 3:
    viewBookingUser(user.url);
    break;
  default:
    break;
  }
}    

void mainUser(User curr_user){
  int choice;
  do{
    printPortalUser();
    scanf("%d", &choice);
    makeChoiceUser(choice, curr_user);
  }while(choice !=4);
}

#endif

