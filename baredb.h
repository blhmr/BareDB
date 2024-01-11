// Header guards or something I don't know but they are useful
// when it comes to conflicting files (they work :D)

#ifndef __BARE_DB__
#define __BARE_DB__

// Include necessary standard header files
#include <stdio.h> // File handling
#include <string.h> // Copying string
#include <stdlib.h> // Memory allocation
#include <inttypes.h> // uint64_t

#pragma pack 1

typedef struct {
	char filename[255]; // Name of the file/database
	FILE* file; // Pointer to the file/database
	size_t obj_size; // Size of object type we want to store (MUST BE THE SAME STRUCT (Check documentation))
} table_t;

// Opening and Closing a database
int bare_open(table_t* table, const char* filename, size_t size); // Opening a database in writing + reading mode
void bare_close(table_t* table); // Closing the database

// Inserting and getting data from the database
int bare_insert(table_t* table, void* data); // Inserting data to the database
int bare_get(table_t* table, void* data, uint64_t index); // Getting data to the database based on its index (starting from 0)

// Getting number of structs/records in the database
size_t bare_size(table_t* table);

// Update a data in the database
int bare_update(table_t* table, void* data, uint64_t index); // Updating a record/struct in the database
#endif
