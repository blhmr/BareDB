#include "baredb.h"

// Opening a database
int bare_open(table_t* table, const char* filename, size_t size) {
	table->file = fopen(filename, "wb+"); // Open file	
	// Error handling !
	if (table->file == NULL)
		return -1;
	
	strcpy(table->filename, filename); // Copy filename
	table->obj_size = size; // Object size
	
	return 1; // Return success
}

// Closing a database
void bare_close(table_t* table) {
	fclose(table->file); // Closing the file pointer
	strcpy(table->filename, "0"); // Reset the filename to 0
	table->obj_size = 0; // Reset size to 0
}

// Inserting data to the database
int bare_insert(table_t* table, void* data) {
	// Error handling !
	if (table->file == NULL)
		return -1;

	fseek(table->file, 0, SEEK_END); // Positioning the cursor pointer to the end
	fwrite(data, table->obj_size, 1, table->file); // Write to file (assuming the size of 'data' and table->obj_file are the same)
	
	return 1; // Return success
}

// Getting data from the database
int bare_get(table_t* table, void* data, uint64_t index) {
	// Error handling !
	if (table->file == NULL)
		return -1;

	fseek(table->file, index * table->obj_size, SEEK_SET); // Positioning the cursor to the targeted struct
	fread(data, table->obj_size, 1, table->file); // Read the data from the database

   return 1; // Return success	
}

// Getting number of structs/records in the database
size_t bare_size(table_t* table) {
	// Error handling
	if (table->file == NULL)
		return -1;

	size_t bytes; // Number of bytes in the file

	fseek(table->file, 0, SEEK_END);
	bytes = ftell(table->file); // Get the number of bites

	return (size_t) bytes / table->obj_size;
}

// Updating a record/struct in the database
int bare_update(table_t* table, void* data, uint64_t index) {
	// Error handling
	if (table->file == NULL)
		return -1;

	fseek(table->file, index * table->obj_size, SEEK_SET); // Positioning the cursor to the targeted struct
	fwrite(data, table->obj_size, 1, table->file); // Overwrite data

	return 0; // Return success
}
