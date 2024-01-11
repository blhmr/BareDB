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

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	// If little endian, swap byte order
	for (size_t i = 0; i < table->obj_size / 2; ++i) {
		uint8_t temp = ((uint8_t*)data)[i];
		((uint8_t*)data)[i] = ((uint8_t*)data)[table->obj_size - i - 1];
		((uint8_t*)data)[table->obj_size - i - 1] = temp;
	}
#endif

	fseek(table->file, 0, SEEK_END); // Positioning the cursor pointer to the end
	fwrite(data, table->obj_size, 1, table->file); // Write to file (assuming the size of 'data' and table->obj_file are the same)
	return 1; // Return success
}

// Getting data from the database
int bare_get(table_t* table, void* data, uint64_t index) {
	// Error handling !
	if (table->file == NULL)
		return -1;

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	// If little endian, swap byte order
	for (size_t i = 0; i < table->obj_size / 2; ++i) {
		uint8_t temp = ((uint8_t*)data)[i];
		((uint8_t*)data)[i] = ((uint8_t*)data)[table->obj_size - i - 1];
		((uint8_t*)data)[table->obj_size - i - 1] = temp;
	}
#endif

	fseek(table->file, index * table->obj_size, SEEK_SET); // Positioning the cursor to the targeted struct
	fread(data, table->obj_size, 1, table->file); // Read the data from the database

	return 1; // Return success	
}

// Getting number of structs/records in the database
size_t bare_size(table_t* table) {
	// Error handling
	if (table->file == NULL)
		return -1;

	size_t bites; // Number of bites in the file

	fseek(table->file, 0, SEEK_END);
	bites = ftell(table->file); // Get the number of bites

	return (size_t) bites / table->obj_size;
}

// Updating a record/struct in the database
int bare_update(table_t* table, void* data, uint64_t index) {
    // Error handling
    if (table->file == NULL)
        return -1;

    fseek(table->file, index * table->obj_size, SEEK_SET); // Positioning the cursor to the targeted struct

    // If big endian, swap byte order before updating
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        for (size_t i = 0; i < table->obj_size / 2; ++i) {
            uint8_t temp = ((uint8_t*)data)[i];
            ((uint8_t*)data)[i] = ((uint8_t*)data)[table->obj_size - i - 1];
            ((uint8_t*)data)[table->obj_size - i - 1] = temp;
        }
    #endif

    fwrite(data, table->obj_size, 1, table->file); // Overwrite data

    // If big endian, swap byte order back after updating
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        for (size_t i = 0; i < table->obj_size / 2; ++i) {
            uint8_t temp = ((uint8_t*)data)[i];
            ((uint8_t*)data)[i] = ((uint8_t*)data)[table->obj_size - i - 1];
            ((uint8_t*)data)[table->obj_size - i - 1] = temp;
        }
    #endif

    return 0; // Return success
}

// Deleting a record/struct at a specific index
int bare_delete(table_t *table, uint64_t index) {
    // Error handling
    if (table->file == NULL)
        return -1;

    FILE *temp_file = fopen("temp_file.db", "wb+"); // Open a new temporary file for writing
    if (temp_file == NULL)
        return -1;

    // Copy records from the original file to the new file, excluding the record to be deleted
    for (uint64_t i = 0; i < bare_size(table); ++i) {
        if (i != index) {
            fseek(table->file, i * table->obj_size, SEEK_SET); // Read record from the original file
            char buffer[table->obj_size];
            fread(buffer, table->obj_size, 1, table->file);

            fwrite(buffer, table->obj_size, 1, temp_file); // Write the record to the new file
        }
    }

    fclose(table->file); // Close the original file

    fclose(temp_file); // Close the new file and rename it to the original file
    if (rename("temp_file.db", table->filename) != 0) {
        remove("temp_file.db");
        return -1;
    }

    table->file = fopen(table->filename, "rb+"); // Reopen the original file for reading and writing

    // Return success
    return 1;
}
