#include <baredb.h>

typedef struct {
	int x;
	int y;
} point;

int main(void) {
	table_t table;

	bare_open(&table, "database.db", sizeof(point));

	// Let's remove the first point (index 0)
	int r = bare_delete(&table, 0);

	if (r > 0)
		printf("Successfully deleted the point!\n");
	else
		printf("Failed to delete the point.\n");

	bare_close(&table);
	return 0;
}
