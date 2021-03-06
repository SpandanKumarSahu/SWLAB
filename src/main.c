#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "admin.h"

void printChoices(){
  printf("\n Please enter \n 1. For user login \n 2. For new user registration \n 3. For admin login\n 4. For Exit\n");
  printf("\nYour Choice : ");
}

void printIncorrectChoice(){
  printf("You entered an incorrect choice. Please re-enter a proper one.\n");
}

void printUserLogin(User *user){
  printf("User Name : ");
  fflush(stdin);
  scanf("%s",user->name);
  printf("Password : ");
  fflush(stdin);
  scanf("%s",user->password); 
}

void printUserSignup(User *user){
  int url;
  FILE* data;
  if ((data = fopen("../data/userURL.txt", "rb")) == NULL){
    printf("Error opening file\n");
  }
  else{
    fread(&url, sizeof(int), 1, data);
    fclose(data);
  }
  user->url=url;
  if ((data = fopen("../data/userURL.txt", "w")) == NULL){
    printf("Error opening file\n");
  }
  else{
    int tempURL=url+1;
    fwrite(&tempURL,sizeof(int),1,data);
    fclose(data);
  }
  printf("User Name : ");
  scanf("%s",user->name);
  printf("Password : ");
  scanf("%s",user->password);
}

void printIncorrectLogin(){
  printf("\nThe Username and/or password you entered is incorrect.\n");
}

void makeChoice(int choice){
  User newUser,existingUser;
  int loginReport,errorCode;
  int adminPassword=112804;
  int tempPassword;
  while(!(choice>=1 && choice<=4)){
    printChoices();
    scanf("%d",&choice);
  }
  switch(choice){
    
  case 1:
    printUserLogin(&existingUser);
    loginReport=verifyUser(existingUser);
    if(loginReport==0){
      printIncorrectLogin();
      makeChoice(100);
    }
    else{
      mainUser(existingUser);
    }
    break;
    
  case 2:
    printUserSignup(&newUser);
    errorCode=postNewUserData(newUser);
    if(errorCode==0){
      printf("Sorry, the file couldn't be opened at this moment. Please try later.\n");
      makeChoice(100);
    }
    else{
      loginReport=verifyUser(newUser);
      if(loginReport==0){
	printIncorrectLogin();
	makeChoice(100);
      }
      else{
	mainUser(newUser);
      }
    }
    break;
    
  case 3:
    printf("Enter Admin Password:");
    scanf("%d",&tempPassword);
    if(adminPassword==tempPassword){
      printf("Redirecting.\n");
      mainAdmin();
    }
    else{
      printf("Incorrect Password");
    } 
    break;
    
  case 4:
    exit(1);
    break;
    
  default:
    printIncorrectChoice();
    makeChoice(100);
    break;
  }
}
    
int main(){
  printf("\t \t Welcome to Indian Railways Cargo Services Portal \n");
  printChoices();
  int choice;
  scanf("%d",&choice);
  makeChoice(choice);
  return 0;
}
