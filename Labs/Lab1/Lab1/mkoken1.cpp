/*
 * @author Matthew Koken <mkoken@scu.edu>
 * @assignment COEN 177 Assignment 1
 * @file mkoken1.cpp
*/
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_CMD_LENGTH 100
#define MAX_NUM_CMDS 2

//run single word commands
//fork creates a child process
//execv -> execvp()
//waitPID

//commands to test: ls, pwd, ./executable

int main(int argc, char** argv)
{
    char buffer[MAX_CMD_LENGTH];
    char *cmd[MAX_NUM_CMDS];
    pid_t pid;
    int status;

    //Main loop
    while (true) {
        //print the prompt
        printf("~$ ");


        //read the line
        if(!fgets(buffer, MAX_CMD_LENGTH, stdin))  //get command and put it in line
            break;

        //strip newline
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n')
            buffer[len - 1] = '\0'; //null terminate

        //add the processed input to the list of command + arguments
        //cmd{command, arg1, arg2...}
        //to have a command like "ps -aux", parse the command string into individuals, ' ' as delimiter
        //then add to the cmd array
        // so cmd[0] = the command, cmd[1...MAX_NUM_CMDS] are arguments
        cmd[0] = buffer;

        //quit
        if (strcmp(buffer, "exit") == 0) {
          return 0;
        } else {
            //spawn a child process, execute
            pid = fork();

            if(pid) {
                //Congratulation's, you're a parent!
                //waiting on child
                waitpid(-1, &status, 0);
                //child finished
            } else {
                //You're the child, do what you're told
                if(execvp(cmd[0], cmd)) { //if true, we had an error
                    //cmd{command, arg1, arg2...}

                    //break if execvp has an error
                    puts(strerror(errno));
                    return 0;
                }
            }
        }
    }

    return 0;
}
