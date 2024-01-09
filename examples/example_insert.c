#include "../include/baredb.h"

typedef struct {
	int x;
	int y;
} point;

int main(void) {
	table_t table;
	bare_open(&table, "filename.db", sizeof(point));

	point p = {.x = 5, .y = 10};

	// Inserting
	bare_insert(&table, &p);

	bare_close(&table);
}
