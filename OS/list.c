#include "list.h"
#include <stdlib.h>

Address alokasi(Infotype X){
	Address P = (Address) malloc (sizeof(ElmtList));
	if (P != NULL)
		Info(P) = X;
		Next(P) = NULL;
		P->prev = NULL;
	return P;
}

void dealokasi (Address* P){
	free(*P);
}

Address push_back(List* L,Infotype X){
	Address P = alokasi (X);
	if (P != NULL){
		if(is_empty(*L) == 1){
			First(*L)=P;
			Last(*L)=P;
		}
		else {
			Next(Last(*L)) = P;
			P->prev = Last(*L);
			Last(*L) = P;
		}
	}
	return P;
}

void popfront(List *L,Infotype *X){
	//prekondisi: List tidak kosong
	(*X) = Info(First(*L));
	Address P = First(*L);
	if(is_one_elmt(*L) == 1){
		First(*L) = NULL;
		Last(*L) = NULL;
	}
	else {
		(Next(P))->prev =  NULL;
		First(*L) = Next(P);
	}
	dealokasi(&P);//bisa dihapus
}

void swap(Address P, List* L){
	Address P1 = First(*L);
	while ((P1 != NULL)&&(P1 != P)){
		P1 = Next(P1);
	}
	if (P1 == P) {
		if (P==First(*L)){
			if(is_one_elmt(*L)==1){
				//do nothing
			}
			else{
				if(Next(P) == Last(*L)){
					(Last(*L))->prev = NULL;
					Next(Last(*L)) = P;
					P->prev = Last(*L);
					Next(P) = NULL;
					First(*L) = Last(*L);
					Last(*L) = P;
				}
				else{
					Address NextP = Next(P);
					Address PrevL = (Last(*L))->prev;
					(Last(*L))->prev = NULL;
					Next(Last(*L)) = NextP;
					(NextP)->prev = Last(*L);
					P->prev = PrevL;
					Next(PrevL) = P;
					Next(P) = NULL;
					First(*L) = Last(*L);
					Last(*L) = P;
				}
			}
		}
		else{ 
			if (Next(P) == Last(*L)){
				Address PrevP = P->prev;
				(Last(*L))->prev = PrevP;
				Next(PrevP) = Last(*L);
				Next(Last(*L)) = P;
				P->prev = Last(*L);
				Next(P) = NULL;
				Last(*L) = P;
			}
			else {
				Address PrevL = (Last(*L))->prev;
				Address PrevP = P->prev;
				Address NextP = Next(P);
				(Last(*L))->prev = PrevP;
				Next(PrevP) = Last(*L);
				Next(Last(*L)) = NextP;
				(NextP)->prev = Last(*L);
				P->prev = PrevL;
				Next(PrevL) = P;
				Next(P) = NULL;
				Last(*L) = P;
			}
		}
	}
	else {
		Next(Last(*L))=P;
		P->prev=Last(*L);
		Last(*L)=P;
	}
}

void construct(List* L){
	First(*L)=NULL;
	Last(*L)=NULL;
}

int is_empty(List L){
	if((First(L) == NULL) && (Last(L) == NULL)){
		return 1;
	}
	else {
		return 0;
	}
}

int is_one_elmt(List L){
	if((First(L) == Last(L))&&(is_empty(L)==0)) {
		return 1;
	}
	else {
		return 0;
	}
}
