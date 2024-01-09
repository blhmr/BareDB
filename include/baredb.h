#ifndef __BAREDB_H__
#define __BAREDB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __attribute__((packed)) {
	FILE* file;
	char filename[255];
	size_t element_size;
} table_t;

#define _throw_error(filename, function) fprintf(stderr, "Error: No file is associated with table '%s' when using function '%s'\n", filename, function);

void bare_open(table_t* table, const char* filename, size_t element_size);
void bare_close(table_t* table);
void bare_insert(table_t* table, void* object);
void bare_get(table_t* table, void* object, int index);
size_t bare_size(table_t* table);
void bare_update(table_t* table, void* object, int index);

void bare_delete(table_t* table, int index); // IN PROGRESS...

#endif
