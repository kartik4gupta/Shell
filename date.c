#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc,char **args){
// {printf("weeehereee....");
  // char com[100];
  // for(int i=0;i<argc;i++){
  //   com[i]=*(args+1);
  // }
    // printf("%p",*(args+1));
    time_t T = time(NULL);
    struct tm tm;
    if((strcmp("-R",*(args+1))==0)||argc==1){
        tm = *localtime(&T);
    }  
    else{
        if(strcmp("-u",*(args+1))==0){
            tm = *gmtime(&T);
        }
        else{
            printf("Please enter a valid command\n");
            exit(0);
        }
    }

    char Month[5];
    char Day[5];

    switch(tm.tm_mon+1){
      case 1:
        strcpy(Month,"Jan");
        break;
      case 2:
        strcpy(Month,"Feb");
        break;
      case 3:
        strcpy(Month,"Mar");
        break;
      case 4:
        strcpy(Month,"Apr");
        break;
      case 5:
        strcpy(Month,"May");
        break;
      case 6:
        strcpy(Month,"Jun");
        break;
      case 7:
        strcpy(Month,"Jul");
        break;
      case 8:
        strcpy(Month,"Aug");
        break;
      case 9:
        strcpy(Month,"Sep");
        break;
      case 10:
        strcpy(Month,"Oct");
        break;
      case 11:
        strcpy(Month,"Nov");
        break;
      case 12:
        strcpy(Month,"Dec");
        break;
      
    }
  switch(tm.tm_wday+1){
    case 1:
      strcpy(Day,"Sun");
      break;
    case 2:
      strcpy(Day,"Mon");
      break;
    case 3:
      strcpy(Day,"Tue");
      break;
    case 4:
      strcpy(Day,"Wed");
      break;
    case 5:
      strcpy(Day,"Thu");
      break;
    case 6:
      strcpy(Day,"Fri");
      break;
    case 7:
      strcpy(Day,"Sat");
      break;
  }
  
    if(( (strcmp("-R",*(args+1))==0) && argc==2)||argc==1) {
        if(argc==1){
            printf("%s %s %d %02d:%02d:%02d IST %d\n", Day, Month, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
               tm.tm_year + 1900);
        }
        if(argc!=1){
            printf("%s, %d %s %d %02d:%02d:%02d +0530 \n", Day, tm.tm_mday, Month, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
    }
    else {
        printf("%s %s %d %02d:%02d:%02d UTC %d\n", Day, Month, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
               tm.tm_year + 1900);
    }
    exit(0);
}