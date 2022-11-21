//rm command
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


int main(int argc, char **args){
    int test_flag=0;
    int flag=1;
    if(argc==3){
        chdir("/");
        chdir(*(args+2));
        int a = remove(*(args+1));
        if(a!=0){
            test_flag=1;
            printf("Unable to delete\n");
        }
      printf("%d",test_flag);
    }
    else if(argc==4){
       int flag2=0;
       int flag3=0;
        if(strcmp("-v",*(args+1))==0){
            chdir("/");
            chdir(*(args+3));
            printf("%s has been removed.\n",*(args+2));
            flag3=1;
            // printf("%d",flag3);
            int x = remove(*(args+2));
            if(x!=0){
                flag2=1;
                printf("Unable to delete\n");
            }
        }
      
        
        else if(strcmp("-i",*(args+1))==0){
            chdir("/");
            chdir(*(args+3));
            printf("Are you sure you want to remove %s? (Yes->Y/y, NO->N/n) : ",*(args+2));
            char Choice;
            scanf("%c",&Choice);
            if(Choice=='y'||Choice=='Y'){
                int x = remove(*(args+2));
                 flag=0;
                if(x!=0){
                    printf("Unable to delete\n");
                }
            }
          else{
            flag=1;
          }
        }
        else{
            printf("Please enter valid Command\n");
        }
    }
    exit(0);
}