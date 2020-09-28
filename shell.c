/* This is the only file you should update and submit. */

/* Fill in your Name and GNumber in the following two comment fields
 * Name:
 * GNumber:
 */

#include "logging.h"
#include "shell.h"

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
		
		
    } 
}
/* end main */
  

