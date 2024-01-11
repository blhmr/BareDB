#include "baredb.h"
#include <stdbool.h>

typedef struct
{
	char name[20];
	int age;
	float gpa;
	bool is_male;
} student_t;

void read_database(table_t* table);

int main(void)
{
	table_t table;
	
	student_t s1 = {"Hatim", 17, 17.70, true};
	student_t s2 = {"Jane Doe", 17, 18.0, false};

	size_t num;

	int r = bare_open(&table, "database.db", sizeof(student_t));
	if (r > 0)
		printf("Successfully opened %s!\n", table.filename);

	num = bare_size(&table);
	printf(">> Number of struct/records: %zu\n", num);

	int i1 = bare_insert(&table, &s1);
	int i2 = bare_insert(&table, &s2);

	if (i1 > 0 && i2 > 0)
		printf("Successfully inserted s1 and s2!\n");
	
	num = bare_size(&table);
	printf(">> Number of struct/records: %zu\n", num);

	student_t s;
	bare_get(&table, &s, 0);
	printf("Got (%s, %d, %.2f, %d) from %s!\n", s.name, s.age, s.gpa, s.is_male, table.filename);

	printf("Reading:\n");
	read_database(&table);

	printf("Updating struct index 1..\n");

	student_t new = {"John Doe", 15, 15.25, true};
	
	bare_update(&table, &new, 1);

	read_database(&table);

	printf("Deleting a record (index 0)..\n");
	bare_delete(&table, 0);

	read_database(&table);
	
	num = bare_size(&table);
	printf(">> Number of struct/records: %zu\n", num);
	
	bare_close(&table);

	return 0;
}

void read_database(table_t* table)
{
	size_t num = bare_size(table);
	int i;

	for (i = 0; i < num; i++)
	{
		student_t read;
		bare_get(table, &read, i);	
		printf("(%s, %d, %.2f, %d)\n", read.name, read.age, read.gpa, read.is_male);
	}
}
