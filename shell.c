
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define MAXLINE 80


char* parse_command(char* args[],char str[]){
		int counter = 0; //tracking index of args

    char* currentptr;
    char* prev_ptr;
    prev_ptr = str;
    char* word;

		str[strlen(str)] = ' ';

    for(int x = 0; x < strlen(str); x++){

      if(str[x] == ' '){
        currentptr = &str[x];
        int length = currentptr - prev_ptr;
        word = (char *) malloc((length + 1) * sizeof(char));
        strncpy(word, prev_ptr, length);
        prev_ptr = currentptr + 1;

        args[counter] = word;
        counter++;
      }//end if

    }//end for loop
    args[counter] = NULL; //last entry is NULL

return *args;
}


int main(void)
{
	char *args[MAXLINE/2 + 1];
	int should_run = 1;
	char command[MAXLINE]; //to store user input

	printf("CS149 Shell from Joanitha Christle Gomez\n");

	while (should_run) {

			memset(command, 0, MAXLINE);

			printf("Joanitha-697> "); //prompt
			fgets(command, MAXLINE, stdin); //get command from user

			if(command[strlen(command) - 1] == '\n') { //if last character is a newline, replace with null
			  command[strlen(command)-1] = '\0';
			}

			if(strcmp(command, "exit") == 0){ // exit if user entered exit
				should_run = 0;

			}//end if
			else{

					parse_command(args, command);

					int pid = fork();
					int status;
					if(pid < 0){
						printf("Fork error");
					}
					else if(pid == 0){
						printf("%d , %s\n", execvp(args[0], args), strerror(errno));
					}
					else{
						printf("Start..\n" );
						if(command[strlen(command)-2] != '&')
							waitpid(pid, &status, 0);
						printf("Done\n");
					}
			}//end else

		} //end while
return 0;
}//end main
