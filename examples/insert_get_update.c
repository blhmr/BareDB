#include <baredb.h>

typedef struct {
	int x;
	int y;
} point;

int main(void) {
	table_t table;

	if (bare_open(&table, "database.db", sizeof(point)) > 0)
		printf("Opening database\n");

	point p1 = {10, 5};
	int r1 = bare_insert(&table, &p1);

	if (r > 0)
		printf("Successfully added (%d,%d) to the database!\n", p1.x, p1.y);
	else
		printf("Failed to add record.\n");

	// Now {10, 5} is added to the database at index 0, let's get the struct!
	point p2;
	bare_get(&table, &p2, 0);

	printf("Got (%d, %d)!\n", p2.x, p2.y);

	// Let's update it to another point (15, 2)
	point p3 = {15, 2};
	int r2 = bare_update(&table, &p3, 0);

	if (r2 > 0)
		printf("Successfully updated the point at index 0!\n");

	// Let's get the struct again
	point p4;

	bare_get(&table, &p4, 0);

	printf("Got (%d, %d)!\n", p4.x, p4.y);
	
	// Closing the database after finishing working with it
	bare_close(&table);
	return 0;
}
