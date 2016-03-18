#include "list.h"
#include <stdlib.h>

Address alokasi(Infotype X){
	Address P = (Address) malloc (sizeof(ElmtList));
	if (P != NULL)
		Info(P) = X;
	return P;
}

void dealokasi (Address* P){
	free(*P);
}

Address push_back(List* L,Infotype X){
	Address P = alokasi (X);
	if (P != NULL){
		Next(Last(*L)) = P;
		Prev(P) = Last(*L);
		Last(*L) = P;
	}
	return P;
}

void pop_front(List* L,Infotype* X){
	(*X) = Info(First(*L));
	First(*L) = Next(First(*L));
}

void swap(Address P, List* L){
	Address P1 = First(*L);
	while ((P1 != NULL)&&(P1 != P)){
		P1 = Next(P1);
	}
	if (P1 == P) {
		if (Next(P) == Last(*L)){
			Address PrevP = Prev(P);
			Address Next(P) = Next(P);
			Prev(Last(*L)) = PrevP;
			Next(Last(*L)) = NextP;
			Next(PrevP) = Last(*L);
			Next(P) = NULL;
			
			Last(*L) = P;
		}
		else {
			Address PrevL = Prev(Last(*L));
			Prev(Last(*L)) = Prev(P);
			Next(Last(*L)) = Next(P);
			Last(*L) = P;
			Next(PrevL) = P;
			Prev(P) = PrevL;
			Next(P) = NULL;
		}
	}
}
