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

#define false 0;
#define true 1;

page_table_entry P;
page_table_pointer s;
int frame = 0;
int NumberOfPages = 0;
short int finished = false;

void PrintPageTable(page_table_entry PageTable[],int NumberOfPages) {

    int Index;
	printf("%d\n",NumberOfPages);
    for (Index =  0;Index < NumberOfPages;Index++) {
        printf("%2d: Valid=%1d Frame=%2d Dirty=%1d Requested=%1d\n",Index,
PageTable[Index].Valid,PageTable[Index].Frame,PageTable[Index].Dirty,
PageTable[Index].Requested);
    }

}

void SigUsr1(int);


int main(int argc,char* argv[]){
	//menggunakan 2 argumen tambahan, jumlah page dan jumlah frame secara berurutan
	if (argc != 3){
		printf("error, argument doesn't match\n");
		exit(EXIT_FAILURE);
	}
	int jpage = atoi(argv[1]);
	int jframe = atoi(argv[2]);
	int pidOS = getpid();
	printf("The shared memory key (PID) is %d\n",pidOS);
	printf("Initializing page table\n");
	int shmid;
	NumberOfPages = jpage;
	printf("from OS %d\n",NumberOfPages);
	//get shared memory id
	if ((shmid = shmget(pidOS, NumberOfPages*sizeof(page_table_entry), IPC_CREAT|0666)) < 0) {
		printf("1\n");
        perror("shmget");
        exit(1);
    }
    //get shared memory (page table) pointer
    page_table_pointer shm;
    if ((shm = shmat(shmid, NULL, 0)) == (void*)-1) {
        perror("shmat");
        exit(1);
    }
    //inisialisasi page table
    s = shm;
    int i;
    for (i=0;i<NumberOfPages;i++){
		s[i].Valid = 0;
		s[i].Frame = -1;
		s[i].Dirty = 0;
		s[i].Requested = 0;
	}
	printf("Page table initialized\n");
	//inisialisasi command untuk menjalankan MMU
	char* command = "./MMU.ls ";
	char* buffer = malloc(100);
	strcpy(buffer,command);
	strcat(buffer,argv[1]);
	strcat(buffer," W2 R3 W3 R4 ");
	char PID[5];
	sprintf(PID, "%d", pidOS);
	strcat(buffer,PID);
	printf("%s\n",buffer);
	//system(buffer);
	signal(SIGUSR1,SigUsr1);
	while(!(finished)) 
	{
	  signal(SIGUSR1,SigUsr1);
	}
	printf("from OS\n");
	return 0;
}

void SigUsr1(int useless){
	short int found = false;
	int i=0;
	int pidMMU;
	for (i=0;i<NumberOfPages;i++){
		if (s[i].Requested != 0){
			found = true;
			pidMMU = s[i].Requested;
			printf("Process %d has requested page %d\n",pidMMU,i);
			s[i].Valid = 1;
			s[i].Requested = 0;
			s[i].Frame = frame;
			printf("Put it in free frame %d\n",frame);
			frame++;
			//s[i].Dirty = 1;
			printf("Unblock MMU\n");
			sleep(1);
			kill(pidMMU,SIGCONT);
			break;
		}
	}
	if (!found)
		finished = true;
}
