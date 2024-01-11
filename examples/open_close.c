#include <baredb.h>

typedef struct {
	int x;
	int y;
} point;

int main(void) {
	table_t table;
	
	int r = bare_open(&table, "database.db", sizeof(point)); // Opening a database table with name "database.db" and type "point" struct

	// Check if successful
	if (r > 0)
		printf("Successfully opened database %s!\n", table.filename);
	else
		printf("Failed to open the database.\n");

	// Closing the database
	bare_close(&table);
	return 0;
}
