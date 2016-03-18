#pragma once
#include "list.h"

//-----------------------------------------------------------------------------
typedef struct {
    int Valid;
    int Frame;
    int Dirty;
    int Requested;
    Address ListAddr;
    } page_table_entry;

typedef page_table_entry* page_table_pointer;
//-----------------------------------------------------------------------------
