#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char rootLoc[250];
void *threader(void *arg) {
  char *arg_new = (char *)arg;
  system(arg_new);

  return NULL;
}

void threading(char *greens) {
  char *myosin = malloc(200 * sizeof(char));
  strcat(myosin, rootLoc);
  strcat(myosin, "/");
  strcat(myosin, greens);
  pthread_t thread;
  pthread_create(&thread, NULL, threader, myosin);
  pthread_join(thread, NULL);
}

void fork_exec_ls(char commands_1[], char commands_2[], char currPos[],
                  int count) {
  printf("checkpt 3");
  if (count == 1) {
    int p_id = fork();
    char file[] = "./";
    strcat(file, commands_1);
    if (p_id == 0) {
      char *args[] = {"./ls", currPos, NULL};
      int p = execvp(args[0], args);
    }
    int k = wait(NULL);
  } else if (count == 2) {
    int p_id = fork();
    char file[] = "./";
    strcat(file, commands_1);
    if (p_id == 0) {
      char *args[] = {"./ls", commands_2, currPos, NULL};
      int p = execvp(args[0], args);
    }
    int k = wait(NULL);
  } else {
    printf("Please Enter valid command.");
  }
}

void fork_exec_date(char *commands[120], char currPos[], int count) {

  if (count == 1) {
    int p_id = fork();
    char file[] = "./";
    strcat(file, commands[0]);
    if (p_id == 0) {
      char *args[] = {"./date", NULL};
      int p = execvp(args[0], args);
    }
    int k = wait(NULL);
  } else if (count == 2) {
    int p_id = fork();
    char file[] = "./";
    strcat(file, commands[0]);
    if (p_id == 0) {
      char *args[] = {"./date", commands[1], NULL};
      int p = execvp(args[0], args);
    }
    int k = wait(NULL);
  } else {
    printf("Please Enter valid command.");
  }
}

int main() {

  char presentLoc[250];
  int Flag = 1;
  getcwd(rootLoc, 250);

  while (Flag == 1) {
    getcwd(presentLoc, 250);
    printf("Shell-Simulator: %s$ ", presentLoc);
    char command_input[120];
    fgets(command_input, 120, stdin);

    char currLoc[250];
    char *command_new = strtok(command_input, "\n");
    int var = 0;
    char *commandList[120];
    int command_count = 0; // Stores the number of strings in command arr
    getcwd(currLoc, 250);

    char *tokCommand = strtok(command_new, " ");
    while (tokCommand != NULL) {
      var = 1;
      commandList[command_count] = tokCommand;
      ++command_count;
      tokCommand = strtok(NULL, " ");
    }
    // if flag_t=1 then pthread, if 0 then fork-exec
    int flag_t = 0, pos_t;
    if (strstr(commandList[0], "&t") != NULL) {
      flag_t = 1;
      command_input[strlen(commandList[0]) - 1] = ' ';
      command_input[strlen(commandList[0]) - 2] = ' ';
      printf("%s", command_input);
    }

    // printf("\ncommands :%d\n", command_count);

    if (strcmp("echo", commandList[0]) == 0) {
      if (command_count > 2) {
        if (strcmp("-n", commandList[1]) == 0) {
          int k = 2;
          while (k < command_count) {
            printf("%s ", commandList[k]);
            k++;
          }
        } else if (strcmp("-n", commandList[1]) != 0) {
          int k = 1;
          while (k < command_count) {
            printf("%s ", commandList[k]);
            k++;
          }
          printf("\n");
        }
      }

      if (command_count == 2) {
        int chk1 = 0;
        if (strcmp("--help", commandList[1]) == 0) {
          printf("\necho - Write arguments to the standard output.\n");
          printf("Available functionalities: -n, --help.\n");
        } else {
          chk1++;
          printf("%s\n", commandList[1]);
        }
      }

    }

    // pwd command , with -L and -P functionality
    else if (strcmp("pwd", commandList[0]) == 0) {
      int chk3 = 0;
      if (command_count == 1) {
        char currentLoc[400];
        chk3 = 1;
        getcwd(currentLoc, 400);
        printf("%s\n", currentLoc);
      } else if (command_count != 1) {
        chk3 = 2;
        int flag_1 = 0;
        if (strcmp("-L", commandList[1]) == 0) {
          flag_1 = 1;
          printf("%s\n", getenv("PWD"));
        } else if (strcmp("-P", commandList[1]) == 0) {
          char currentLoc[250];
          flag_1 = 2;
          getcwd(currentLoc, 250);
          printf("%s\n", currentLoc);
        } else {
          flag_1 = 3;
          printf("Please enter a valid Command\n");
        }
      }
    }

    // cd command  / , ~ and .. & options -P and --help

    else if (strcmp("cd", commandList[0]) == 0) {
      int Chk = 0;
      if (command_count == 2 && strcmp("--help", commandList[1]) == 0) {
        printf("\npwd - print name of current/working directory\n");
        printf("Available functionalities : -P, --help\n");

      }

      else if (command_count == 2 && strcmp("~", commandList[1]) == 0) {
        chdir(getenv("HOME"));
      }

      else if (command_count == 2 && strcmp("/", commandList[1]) == 0) {
        chdir("/");
      } else if (command_count == 2 && strcmp("..", commandList[1]) == 0) {
        // printf("checkpoint\n");
        char currentLoc[250];
        char newLoc[250] = "";

        getcwd(currentLoc, sizeof(currentLoc));
        char *localArr[250];

        int count = 0;

        char *LocalToken = strtok(currentLoc, "/");
        Chk = 1;
        while (LocalToken != NULL) {
          localArr[count] = LocalToken;
          ++count;
          LocalToken = strtok(NULL, "/");
        }
        for (int i = 0; i < count - 1; i++) {
          strcat(newLoc, "/");
          strcat(newLoc, localArr[i]);
        }
        //  printf("%s",newLoc);
        if (chdir(newLoc) == -1) {
          printf("We're in trouble!\n");
        }
      }

      else if ((strcmp("..", commandList[1]) != 0 ||
                strcmp("/", commandList[1]) != 0 ||
                strcmp("-P", commandList[1]) != 0 ||
                strcmp("~", commandList[1]) != 0 ||
                strcmp("--help", commandList[1]) != 0) &&
               command_count == 2) {
        char currentLoc[250];
        getcwd(currentLoc, 250);
        strcat(currentLoc, "/");
        int chk = 0;
        strcat(currentLoc, commandList[1]);
        int res = chdir(currentLoc);
        if (res != 0 && strcmp("~", commandList[1]) != 0) {
          chk = -1;
          printf("No such directory found\n");
        }
        if (strcmp("~", commandList[1]) == 0) {
          chk = 1;
          chdir(getenv("HOME"));
        }
      } else if (strcmp("-P", commandList[1]) == 0) {
        if (command_count == 3) {
          char currentLoc[200];
          getcwd(currentLoc, sizeof(currentLoc));
          strcat(currentLoc, "/");
          strcat(currentLoc, commandList[2]);
          int res = chdir(currentLoc);
          if (res != 0) {
            printf("No such directory found\n");
          }
        } else {
          printf("Please enter a valid Command\n");
        }
      }

      else {
        printf("Please enter a valid Command\n");
      }

    }

    //*******************************************************************************
    //*******************************************************************************
    //*******************************************************************************
    //               *****************EXTERNAL COMMANDS:************

    //********************************************************************************
    // date command, -u functionality (for UTC time)
    else if ((strcmp("date", commandList[0]) == 0) && flag_t == 0) {
      // printf("heree");
      char curPos[250];
      getcwd(curPos, 250);
      chdir("/");
      chdir(rootLoc);
      // printf("chk1");
      if (command_count == 1) {
        // char file[]="./";
        // strcat(file,commandList[0]);
        int p_id = fork();
        if (p_id == -1) {
          printf("error");
        }
        // printf("chk1");
        if (p_id == 0) {
          char filename[] = "./date";
          char *args[] = {filename, curPos, NULL};
          // printf("chk2");
          // printf("wwwwwww");
          if (execvp(args[0], args) == -1) {
            // printf("errrorrr.");
          }
        }
        // printf("hhhheeeee");
        else {
          wait(NULL);
        }
      } else if (command_count == 2) {
        // char file[]="./";
        // strcat(file,commandList[0]);
        int p_id = fork();
        // printf("chk1");
        if (p_id == 0) {
          // printf("chk1");
          char filename[] = "./date";
          char *args[] = {filename, commandList[1], NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      }

      // fork_exec_date(commandList,curPos,command_count);

      chdir("/");
      chdir(curPos);
    }

    else if (flag_t == 1) {
      printf("%s", command_input);
      threading(command_input);

    }

    //********************************************************************************

    // ls command call -Q flag, -i flag
    else if (strcmp("ls", commandList[0]) == 0) {
      // printf("checkpt 1");
      char currPosition[250];
      getcwd(currPosition, 250);
      chdir("/");
      chdir(rootLoc);
      // printf("checkpt 2");

      if (command_count == 1) {
        char file[] = "./";
        // strcat(file,commandList[0]);
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./ls";
          char *args[] = {filename, currPosition, NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      } else if (command_count == 2) {
        char file[] = "./";
        // strcat(file,commandList[0]);
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./ls";
          char *args[] = {filename, commandList[1], currPosition, NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      }

      // fork_exec_ls(commandList[0],commandList[1],currPosition,command_count);
      // printf("checkpt 4");
      chdir("/");
      chdir(currPosition);

    }

    //***************************************************************************
    // rm command call
    else if (strcmp("rm", commandList[0]) == 0) {
      char curPos[250];
      getcwd(curPos, 250);
      chdir("/");
      chdir(rootLoc);
      if (command_count == 2) {
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./rm";
          char *args[] = {filename, commandList[1], curPos, NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      } else if (command_count > 2) {
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./rm";
          char *args[] = {filename, commandList[1], commandList[2], curPos,
                          NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      }
      chdir("/");
      chdir(curPos);
    }
    //**********************************************************************

    // mkdir command call with -v and -p flags
    else if (strcmp("mkdir", commandList[0]) == 0) {
      char curPos[250];
      getcwd(curPos, 250);
      chdir("/");
      chdir(rootLoc);
      if (command_count == 2) {
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./mkdir";
          char *args[] = {filename, commandList[1], curPos, NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      } else if (command_count > 2) {
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./mkdir";
          char *args[] = {filename, commandList[1], commandList[2], curPos,
                          NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      }
      chdir("/");
      chdir(curPos);

    }
    //******************************************************************************

    // cat command call with flags -n (for numbering) and -e (for $sign at end
    // of line)
    else if (strcmp("cat", commandList[0]) == 0) {
      char currPos[250];
      getcwd(currPos, 250);
      chdir("/");
      chdir(rootLoc);
      if (command_count == 2) {
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./cat";
          char *args[] = {filename, commandList[1], currPos, NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      } else if (command_count > 2) {
        int p_id = fork();
        if (p_id == 0) {
          char filename[] = "./cat";
          char *args[] = {filename, commandList[1], commandList[2], currPos,
                          NULL};
          execvp(args[0], args);
        } else {
          wait(NULL);
        }
      }
      chdir("/");
      chdir(currPos);
    }
  }

  return 0;
}
