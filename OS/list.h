//Konstanta
#pragma once
#define Nil NULL
 
typedef int Infotype;
typedef struct TElmtList *Address;

typedef struct TElmtList {
	Infotype 	info;
	Address 	next;
	Address		prev;
} ElmtList;

typedef struct {
	int			size;
	Address		first;
	Address		last;
} List;
 
#define First(L) (L).first
#define Next(P) (P)->next
#define Prev(X) (X)->prev
#define Info(P) (P)->info
#define Last(L) (L).last

Address alokasi(Infotype);

void dealokasi (Address*);

Address push_back(List*,Infotype);
//push int ke list, kembalikan address dari alokasi

void popfront(List *L,Infotype *X);
//kembalikan first(LRU) ke Infotype, hilangkan dari list

void swap(Address, List*);
//tukar address dengan last (MRU)

void construct(List*);
//buat list kosong

int is_empty(List);

int is_one_elmt(List);
