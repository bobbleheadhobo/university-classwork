// Joey Troyer
// 9/22/23
// Purpose: To learn how shells work and get experience using fork, dup2..etc

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* function which takes a character buffer and parses the buffer into tokens using th
    strtok subroutine */

/*returns the number of arguments read in  */
int parse(char* buff, char* argv[])
{  int i,j;
   char *point;

   j=-1;

   point=strtok(buff,"  ");

   while (point != NULL)
     {

        j++;
        argv[j]=point;
        point=strtok(NULL,"     ");
     }
     argv[j+1]='\0';

     return(j);
}
 

int main()
{
    // for arguments and parser
    int args;
    int i;
    char line[200];
    char* argv[100];

    // for the child forks
    int status;
    pid_t child;

    // for errors in io redirection and 
    int skipOuterLoop = 0;


    while (1)
    {

    /* Print the prompt */
    printf("%% ");
    fflush(stdout);


        if (fgets(line, sizeof(line), stdin) == NULL) {
            perror("something broke");
            exit(1); // Exit loop on EOF or error
        }

        if (line[0] == '\n') {
            continue; // Skip to the next iteration of the loop
        }

        // Remove newline character
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        args = parse(line, argv);

        skipOuterLoop = 0;
        // handle errors bad input
        for (int i = 0; i <= args; i++) {
            if (strcmp(argv[i], "<") == 0 || strcmp(argv[i], ">") == 0) {
                skipOuterLoop = 0;

                // error expl: cat <
                if (i + 1 > args || argv[i + 1] == NULL) {
                    fprintf(stderr, "Error: Expected a filename after '%s'.\n", argv[i]);
                    skipOuterLoop = 1;
                    break;
                }

                // error expl: cat < <
                if (strcmp(argv[i + 1], "<") == 0 || strcmp(argv[i + 1], ">") == 0) {
                    fprintf(stderr, "Error: Expected a filename after '%s', but found another redirection symbol.\n", argv[i]);
                    skipOuterLoop = 1;
                    break;
                }

                // error expl: cat < foo bar
                if (argv[i + 2] != NULL && strcmp(argv[i + 2], "<") != 0 && strcmp(argv[i + 2], ">") != 0) {
                    fprintf(stderr, "Error: Multiple filenames provided after '%s'. Only one expected.\n", argv[i]);
                    skipOuterLoop = 1;
                    break;
                }
            }
        }

        // go to next main loop
        if (skipOuterLoop == 1)
            continue;

        // for command 'exit'
        if ((strcmp(argv[0], "exit") == 0)) {
            exit(0);
        }

        // Handle the 'cd' and 'chdir' command 
        if ((strcmp(argv[0], "cd") == 0) || (strcmp(argv[0], "chdir") == 0)) {
            if (argv[1] == NULL) {
                fprintf(stderr, "Missing Argument\n");
                continue;
            }
            if (chdir(argv[1]) != 0) {
                //error
                perror("cd");
            }
            else{
                // successful
                child=fork();
                if (child != 0) { //parent
                    waitpid(child, &status, 0);

                }else {// child
                    execl("/bin/pwd", "pwd", NULL);

                    // If execl fails
                    printf("Failed to execute command: %c\n", argv[0]);
                    exit(0); //end the child
                }
                }
            continue; // Skip the rest of the loop iteration
        } // end cd


        // for command 'pwd' using getwd()
        if ((strcmp(argv[0], "pwd") == 0)) {
            char buffer[1024];

            child=fork();
            if (child != 0) {
                waitpid(child, &status, 0);
            }else {
                if (getcwd(buffer, sizeof(buffer)) != NULL) {
                    printf("%s\n", buffer);
                } else {
                    perror("getcwd() error");
                }
                exit(0); //end the child

            }
            continue;
        }


    if ((strcmp(argv[0], "echo") == 0)) {
        child=fork();
        if (child != 0) { // parent
            waitpid(child, &status, 0);
        } else {
            int count = 0;
            // count how many characters are in the argv array
            for (int i = 1; argv[i] != NULL; i++) {
                for (int j = 0; argv[i][j] != '\0'; j++) {
                    count++;
                }
                if (argv[i + 1] != NULL) count++; // Add 1 for the space
            }

            char* temp_args = malloc(count + 1);  // add one for the null terminator
            temp_args[0] = '\0';  // Initialize the string to be empty

            // put everything in the array into a string
            for (int i = 1; i <= args; i++) {
                strcat(temp_args, argv[i]);

                if (i < args) {
                    strcat(temp_args, " "); // add in the spaces
                }
            }

            if(printf("%s\n", temp_args) < 0)
                perror("Echo");

            free(temp_args);
            exit(0);  // end the child
        }
        continue;
    } //end echo



        // for command 'mkdir'
        if ((strcmp(argv[0], "mkdir") == 0)) {
            if (argv[1] == NULL) {
                fprintf(stderr, "missing argument\n");
                continue;
            }
            child=fork();
            if (child != 0) { // parent
                waitpid(child, &status, 0);
            }else {// child

                // creates directory and give everyone read/write/execute permissions
                if (mkdir(argv[1], 0755) == -1) {
                    perror("mkdir");
                }
                exit(0); //end the child
            }
            continue;
        }


    // save original file distinctor
    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);

    // Arrays to store positions of redirection operators and filenames
    int remove_indices[2 * args];
    int remove_count = 0;

    // Handle All Input Redirections
    for (int i = 0; i < args; i++) {
        if (strcmp(argv[i], "<") == 0) {

            // open file in read only
            int fd = open(argv[i + 1], O_RDONLY);
            if (fd == -1) {
                perror("< Failed to open file for reading");
                skipOuterLoop = 1;
                break;
            }

            // change input to come from the file not the terminal
            if (dup2(fd, STDIN_FILENO) == -1) {
                perror("< Failed to redirect stdin");
                skipOuterLoop = 1;
                break;
            }
            close(fd);

            // Remember positions to remove later
            remove_indices[remove_count++] = i;      // '<' position
            remove_indices[remove_count++] = i + 1;  // filename position
        }


    // Handle All Output Redirections
        if (strcmp(argv[i], ">") == 0) {

            // open file in write only | create it if not there | delete everything if not empty | give everyone read/write/execute permission
            int fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("> Failed to open file for writing");
                skipOuterLoop = 1;
                break;
            }

            // tell to output everything in to a file not the terminal
            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("> Failed to redirect stdout");
                skipOuterLoop = 1;
                break;
            }
            close(fd);

            // Remember positions for later removal
            remove_indices[remove_count++] = i;      // '>' position
            remove_indices[remove_count++] = i + 1;  // filename position
        }
    }

        // if error go to next main loop
        if(skipOuterLoop == 1){
            // set stdin and stdout back to terminal
            dup2(original_stdin, STDIN_FILENO);
            close(original_stdin);

            dup2(original_stdout, STDOUT_FILENO);
            close(original_stdout);
            continue;
        }

        // 3. remove <> and file names
        if(remove_count > 0){
        for (int i = remove_count - 1; i >= 0; i--) {
            for (int j = remove_indices[i]; j < args - 1; j++) {
                argv[j] = argv[j + 1];
            }
            args--;
        }
        argv[args+1] = NULL; //set new last entry to null
        }

    // this part handles all commands with a given path
    child=fork();
    if (child != 0) { // Parent
                waitpid(child, &status, 0);
    }
    else { // Child     
        execvp(argv[0], argv);
    
        // If execv fails
        perror("Failed to execute command");
        exit(0); //end the child
    }

    // set stdin and stdout back to terminal
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);

    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);

    }
    return 0;
}