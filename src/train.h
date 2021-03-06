#ifndef TRAIN_H
#define TRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydate.h"

typedef struct train Train;

struct train{
  int trainNumber;
  char srcStationCode[5];
  char destStationCode[5];
  Schedule trainSchedule;
  Time arrivalTime;
  Time departureTime;
  Time journeyTime;
  char trainType;
  int fare;
};


int postNewTrainData(Train train){
  FILE* data;
  if ( (data = fopen("../data/trains.txt", "a")) == NULL ){
    printf("Error opening file\n");
    return 0;   
  }
  fwrite(&train, sizeof(Train), 1, data);
  fclose(data);
  return 1;
}

int inputNewTrain(){
  Train newTrain;
  printf("Enter train number : ");
  scanf("%d", &newTrain.trainNumber);
  printf("Enter source Station Code : ");
  fflush(stdin);
  scanf("%s", newTrain.srcStationCode);
  printf("Enter destination Station Code : ");
  fflush(stdin);
  scanf("%s", newTrain.destStationCode);
  fill_schedule(&(newTrain.trainSchedule));
  fill_time(&(newTrain.arrivalTime),"arrival");
  fill_time(&(newTrain.departureTime),"departure");
  fill_time(&(newTrain.journeyTime),"journey");
  printf("Enter Train type (A/B/C): ");
  fflush(stdin);
  scanf("%c",&(newTrain.trainType));
  printf("Enter journey fare: ");
  scanf("%d",&(newTrain.fare));
  return postNewTrainData(newTrain);
}

void printTrainData(Train train){
  printf("%d\t%d:%d\t%d:%d\t%c\t%d\n",train.trainNumber,train.departureTime.hours,train.departureTime.minutes,train.arrivalTime.hours,train.arrivalTime.minutes,train.trainType,train.fare);
}

void displayTrainBySrcDest(char *src, char *dest){
  FILE* data;
  if ((data = fopen("../data/trains.txt", "rb")) == NULL){
    printf("Error opening file\n");
  }
  else{
    Train tempTrain;
    int count=0;
    printf("Source: %s \nDestination: %s",src,dest);
    printf("\nTrainNumber\tDeparture\tArrival\tTrainType\tFare\n");
    while(!feof(data)){
      fread(&tempTrain, sizeof(Train), 1, data);
      if(strcmp(tempTrain.srcStationCode,src)==0 && strcmp(tempTrain.destStationCode,dest)==0){
	printTrainData(tempTrain);
	count++;
      }
    }
    if(count==0)
      printf("Sorry there were no such trains available\n");
  }
}

void displayAllTrains(){
  FILE* data;
  if ((data = fopen("../data/trains.txt", "rb")) == NULL){
    printf("Error opening file\n");
  }
  else{
    Train train;
    int count=0;
    printf("\nTrainNumber\tSource\tDeparture\tDestination\tArrival\tTrainType\tFare\n");
    while(!feof(data)){
      fread(&train, sizeof(Train), 1, data);
      printf("%d\t%s\t%d:%d\t%s\t%d:%d\t%c\t%d\n",train.trainNumber,train.srcStationCode,train.departureTime.hours,train.departureTime.minutes,train.destStationCode,train.arrivalTime.hours,train.arrivalTime.minutes,train.trainType,train.fare);
    }
    if(count==0)
      printf("Sorry there were no trains available\n");
  }
}


Train getTrainData(int number){
  FILE* data;
  Train tempTrain;
  tempTrain.trainNumber=-1;
  if ((data = fopen("../data/trains.txt", "rb")) == NULL){
    printf("Error opening file\n");
    return tempTrain;
  }
  else{
    while(!feof(data)){
      fread(&tempTrain, sizeof(Train), 1, data);
      if(tempTrain.trainNumber==number){
	fclose(data);
	return tempTrain;
      }
    }
  }
  fclose(data);
  return tempTrain;
}
#endif
