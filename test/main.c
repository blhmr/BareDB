#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/baredb.h"

typedef struct {
    int x;
    int y;
} point_t;

point_t create_point(int x, int y) {
    return (point_t) {.x = x, .y = y};
}

int main(void) {
    table_t table;
    int i;

    bare_open(&table, "database.db", sizeof(point_t)); // Opening the database
    printf("Opened database '%s'!\n", table.filename);

    printf("------------\n");

    printf("INSERTING:\n");

    for (i = 0; i < 5; i++) {
        point_t p = create_point(i, 5-i);
        bare_insert(&table, &p);
        printf("(%d, %d)\n", p.x, p.y);
    }

    printf("------------\n");

    printf("READING:\n");
    point_t p;

	for (i = 0; i < 5; i++) {
		bare_get(&table, &p, i);
		printf("(%d, %d)\n", p.x, p.y);
	}

	printf("------------\n");

	printf("UPDATING:\n");
	point_t new_p = create_point(0, 0);
	bare_update(&table, &new_p, 3);

	printf("After updating index 3:\n");

	point_t read_p;

	for (i = 0; i < 5; i++) {
		bare_get(&table, &read_p, i);
		printf("(%d, %d)\n", read_p.x, read_p.y);
	}

	size_t num = bare_size(&table);
	printf("There are %zu points in the database.\n", num);

	printf("-----------------\n");
	printf("DELETING INDEX 2:\n");

	bare_delete(&table, 2);

	point_t new_read_p;

	for (i = 0; i < 4; i++) {
		bare_get(&table, &new_read_p, i);
		printf("(%d, %d)\n", new_read_p.x, new_read_p.y);
	}

	num = bare_size(&table);
	printf("There are %zu points in the database.\n", num);
    
	printf("Closing '%s'...", table.filename);
    bare_close(&table); // Closing the database
    printf("Closed the database!\n");
}

