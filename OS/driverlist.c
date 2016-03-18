//file: driverlist.c

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
	List L;
	int X;
	Address P;
	 //coba push
	construct(&L);
	int i=1;
	do{
		scanf("%d",&X);
		if(X!=(-1)){
			P = push_back(&L, X);
			i++; //trial;
		}
	} while (X!=(-1));
	
	printf("List dari depan ke belakang: ");
	P = First(L);
	while (P!=NULL)
	{
		printf("%d ",Info(P));
		P=Next(P);
	}
	printf("\n");
	
	printf("List dari belakang ke depan: ");
	P = Last(L);
	while (P!=NULL)
	{
		printf("%d ",Info(P));
		P=Prev(P);
	}
	printf("\n");
	
	printf("Is One Element : %d \n",is_one_elmt(L));
	printf("Is Empty : %d \n",is_empty(L));
	
	//coba pop
	printf("Pop: ");
	P = Last(L);
	while ((P!=NULL)&&(is_one_elmt(L)==0)){
		popfront(&L,&X);
		printf("%d ",X);
	}
	printf("\n");
	
	printf("List dari depan ke belakang: ");
	P = First(L);
	while (P!=NULL)
	{
		printf("%d ",Info(P));
		P=Next(P);
	}
	printf("\n");
	
	printf("List dari belakang ke depan: ");
	P = Last(L);
	while (P!=NULL)
	{
		printf("%d ",Info(P));
		P=Prev(P);
	}
	printf("\n");
	
	printf("Is One Element : %d \n",is_one_elmt(L));
	printf("Is Empty : %d \n",is_empty(L));
	
	//coba pop is_one_elmt
	printf("Pop: ");
	P = Last(L);
	popfront(&L,&X);
	printf("%d ",X);
	printf("\n");
	
	printf("List dari depan ke belakang: ");
	P = First(L);
	while (P!=NULL)
	{
		printf("%d ",Info(P));
		P=Next(P);
	}
	printf("\n");
	
	printf("List dari belakang ke depan: ");
	P = Last(L);
	while (P!=NULL)
	{
		printf("%d ",Info(P));
		P=Prev(P);
	}
	printf("\n");
	
	printf("Is One Element : %d \n",is_one_elmt(L));
	printf("Is Empty : %d \n",is_empty(L));
	
	return 0;
}
