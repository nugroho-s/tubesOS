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


page_table_entry P;

void PrintPageTable(page_table_entry PageTable[],int NumberOfPages) {

    int Index;
	printf("%d\n",NumberOfPages);
    for (Index =  0;Index < NumberOfPages;Index++) {
        printf("%2d: Valid=%1d Frame=%2d Dirty=%1d Requested=%1d\n",Index,
PageTable[Index].Valid,PageTable[Index].Frame,PageTable[Index].Dirty,
PageTable[Index].Requested);
    }

}


int main(int argc,char* argv[]){
	//menggunakan 2 argumen tambahan, jumlah page dan jumlah frame secara berurutan
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
    page_table_pointer s = shm;
    int i;
    for (i=0;i<NumberOfPages;i++){
		s[i].Valid = 0;
		s[i].Frame = -1;
		s[i].Dirty = 0;
		s[i].Requested = 0;
	}
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
	system(buffer);
	
	return 0;
}
