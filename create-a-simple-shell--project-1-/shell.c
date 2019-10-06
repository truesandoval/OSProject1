#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) { 
        // Print the shell prompt.
        printf(" %s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        else{
          char* token;
          
          //retrieve the first token
          token = strtok(command_line, delimiters);
          
          while(token != NULL){
            printf(" %s\n", token);
            token = strtok(NULL, delimiters);
          }
          pid_t pid;
          int status;
          
          if ((pid = fork() < 0)){
            printf("ERROR: forking child process failed\n");
            exit(1);
          }
          else if(pid == 0){
            if (execvp(*arguments, arguments) < 0){
              printf("ERROR: execution failed\n");
            exit(1);
            }
          }
          else{
            while (wait(&status)!= pid);
            return;
          }
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 1. Tokenize the command line input (split it on whitespace) YUP
        // 2. Create a child process which will execute the command line input
        // 3. The parent process should wait for the child to complete
        // 
        // Hints (put these into Google):
        // man fork
        // man execve
        // man wait
        // man strtok
   
    
    // This should never be reached.
    return -1;
}
}
