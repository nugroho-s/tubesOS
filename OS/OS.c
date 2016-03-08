#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PageTable.h"

page_table_entry P;

int main(int argc,char* argv[]){
	if (argc != 3){
		printf("error, argument doesn't match\n");
		exit(EXIT_FAILURE);
	}
	int jpage = atoi(argv[1]);
	int jframe = atoi(argv[2]);
	int pidOS = getpid();
	char* command = "./MMU.ls ";
	char* buffer = malloc(50);
	strcpy(buffer,command);
	strcat(buffer,argv[1]);
	strcat(buffer," W2 ");
	char PID[5];
	sprintf(PID, "%d", pidOS);
	strcat(buffer,PID);
	printf("%s\n",buffer);
	system(buffer);
	return 0;
}
