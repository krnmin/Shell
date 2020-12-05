/* This is the only file you should update and submit. */

/* Fill in your Name and GNumber in the following two comment fields
 * Name: Minki Chwa
 * GNumber: G01015962
 */

#include "logging.h"
#include "shell.h"
#include "string.h"

struct record
{
	
};


char resetArgs(char * argv[MAXLINE], int arg)
{
	char * newArray[MAXLINE];
	for(int i = 0; i < arg,i ++)
	{
		if(strcmp(token, ">") != 0 || strcmp(token, "<") != 0 || strcmp(token, ">>") != 0) 
		{
			strcpy(newArray[i] ,argv[i])
		}
		
	}
}

/* Feel free to define additional functions and update existing lines */
/* main */
/* The entry of your shell program */
int main() 
{
    char cmdline[MAXLINE]; /* Command line */

    while (1) {
	/* Print prompt */
  	log_prompt();
	
	/* Read a line */
	// note: fgets will keep the ending '\'
	if (fgets(cmdline, MAXLINE, stdin)==NULL)
	{
	   	if (errno == EINTR)
			continue;
	    	exit(-1); 
	}
	if (feof(stdin)) {
	    	exit(0);
	}

	/* Parse command line and evaluate */

	// parsing user input. using > 1 so it doesn't break the shell
	// shell won't get next input and return null
	if(strlen(cmdline)>1){
		// takes out the trailing \n character obtained from fgets
		strtok(cmdline,"\n");

	}
	// help will print out shell description by calling log_help()
	// should print out the list of built in commands
	if(strcmp(cmdline, "help") == 0)
	{
		log_help();
	}
	// calling quit will terminate the shell
	// can assume that there will be no background processes
	if(strcmp(cmdline, "quit" ) == 0)	
	{
		log_quit();
		exit(0);	
	}

	// else none of the built in functions have been called
	// 1. with and without args, with and without redirection e.g /bin/sleep, ls, pwd
	// 2. only with redirection e.g /bin/wc <file.txt
	else
	{
		//background jobs must call log_start_bg(pid,cmd)
		//
		//print statement to get this shit outta here
		//
		// parse white spaces to get arguments
		// /usr/bin/cmdline[0]
		//
		char* argv[500];
		char  frChar[2];
		char * delim = " ";
		char * token = strtok(cmdline,delim);
		int arg = 0;
		int fileArg = 0;
		pid_t pid;
		// fr = file redirect flag
		int fr = 0;
		while(token != NULL)
		{
			// check to see if a file redirect prompt exists... bad true shell development
			if(strcmp(token, ">") == 0 || strcmp(token, "<") == 0 || strcmp(token, ">>") == 0) 
			{
				strcpy(frChar,token);	
				fr = 1;
				// filename comes afer the operator
				// so we can find the file name here or index of 
				// arg +=2?
				fileArg = arg+1;
			}
			argv[arg++] = token;
			token = strtok(NULL,delim);
		}
		// found a file redirect prompt
		if(fr == 1)
		{
			
			printf("filearg = :%s\n", argv[fileArg]);

			//removing instance of' >' ' <' '>>' from args
			for(int i =0;i <arg; i++)
			{
				if(i == fileArg-1)
				{
					argv[i] = argv[i+1];
				}
				if(i == arg-1)
				{
					
				}
				printf("string at %d is  %s\n",i,argv[i]);
			}
			if((pid = fork()) ==0)
			{
				int fd = -1;
				if(strcmp(frChar, ">")==0)
				{
					
					fd = open(argv[fileArg] ,O_WRONLY|O_TRUNC|O_CREAT,0600);
					if(fd == -1)
					{
						printf("failed to open file: '%s'\n",argv[fileArg]);
					}
					// need to execute command
					dup2(fd, STDOUT_FILENO);
					execv(argv[0],argv);
					exit(1);
				}
				if(strcmp(frChar,">>")==0)
				{
					fd = open(argv[fileArg] ,O_WRONLY|O_APPEND|O_CREAT);
					if(fd == -1)
					{
						printf("failed to open file: '%s'\n",argv[fileArg]);
					}
					dup2(fd,STDOUT_FILENO);
					execv(argv[0],argv);
					exit(1);
				}
				if(strcmp(frChar, "<")==0)
				{
					fd = open(argv[fileArg] ,O_RDONLY);
					if(fd == -1)
						{
							printf("failed to open file: '%s'\n",argv[fileArg]);
						}
					dup2(fd,STDIN_FILENO);
					execv(argv[0],argv);
					exit(1);
				}

				exit(0);
			}
			else
			{
				waitpid(pid,NULL,0);
			}
		}
				/* //prints args
		for(int i = 0; i < arg; i++)
		{
			printf("%s\n",array[k]);
		}

		*/

		// creates file path
	
		// user has entered a & hence the command must be a background process
		// make this shit into a background process	
		else if(strcmp(argv[arg-1],"&") == 0)
		{
			arg--;
			char * newArray[500];
			// taking out the last '&' statement
			for(int i =0;i<arg;i++)
			{
				newArray[i] = argv[i];
			}
	
			if((pid = fork()) == 0)
			{
				// in child process
				//printf("pid = %ld\n",(long) getpid());
				
				log_start_bg(pid,argv[0]);
				// execv only returns -1 if something wrong happened. 
				// Doesn't return anything if execv works correctly
				execv(argv[0],newArray);
				// if exec fails will run below	
				log_command_error(argv[0]);
				exit(1);
	
			}
			else 
			{
				//printf("parent\n");	
				//printf("pid = %ld\n",(long) getpid());
				memset(argv,0,sizeof(argv));
			}
	

			
		}	
		else
		{
		
		// creating a new foreground process
		if((pid = fork()) == 0)
		{
			// in child process
		//	printf("pid = %ld\n",(long) getpid());
			
			// execv only returns -1 if something wrong happened. 
			// Doesn't return anything if execv works correctly	

			execv(argv[0],argv);		
			log_command_error(argv[0]);
			exit(1);
	/*
			if(execv(cmd,array) < 0)
			{
				log_command_error(cmd);
				exit(0);
			}
			*/

		}
		else 
		{
			waitpid(pid,NULL,0); // cause this to be a foreground 
		//	printf("parent\n");	
		//	printf("pid = %ld\n",(long) getpid());
			memset(argv,0,sizeof(argv));
		}
		
		//
		//failure to load must call log_command_error(cmd)
		//
		}
		// **** testing **** 
		//
	}


    } 
}
/* end main */
  

