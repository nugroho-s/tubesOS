#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PageTable.h"
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "PageTable.h"

int main(int argc,char* argv[]){
	if (argc != 3){
		printf("error, argument doesn't match\n");
		exit(EXIT_FAILURE);
	}
	int jpage = atoi(argv[1]);
	int jframe = atoi(argv[2]);
	int pidOS = getpid();
	int shmid;
	int NumberOfPages = jpage;
	printf("from OS %d\n",NumberOfPages);
	if ((shmid = shmget(pidOS, NumberOfPages*sizeof(page_table_entry), IPC_CREAT|0)) < 0) {
		printf("1\n");
        perror("shmget");
        exit(1);
    }
	char* command = "./MMU.ls ";
	char* buffer = malloc(100);
	strcpy(buffer,command);
	strcat(buffer,argv[1]);
	strcat(buffer," W2 R3 W3 R4 ");
	char PID[5];
	sprintf(PID, "%d", pidOS);
	strcat(buffer,PID);
	printf("%s\n",buffer);
	system(buffer);
	return 0;
}
