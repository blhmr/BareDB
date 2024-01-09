#include "../include/baredb.h"

#include <stdbool.h>

struct student {
	char name[20];
	int age;
	bool is_male;
};

int main(void) {
	table_t table;
	
	// Opening a database
	bare_open(&table, "filename.db", sizeof(struct student)); // Replace filename with any name

	printf("Opened a database with filename (%s) and element size (%zu)\n", table.filename, table.element_size);

	bare_close(&table); // Don't forget to close the database after dealing with it!
						
	return 0
}
