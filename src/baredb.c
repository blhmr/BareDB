#include "../include/baredb.h"

void bare_open(table_t* table, const char* filename, size_t element_size) {
	strcpy(table->filename, filename);
	table->file = fopen(filename, "wb+");
	table->element_size = element_size;
	fseek(table->file, 0, SEEK_SET);
	if (NULL == table->file) {
		_throw_error(table->filename, "bare_open()");
	}
}

void bare_close(table_t* table) {
	table->element_size = 0;
	fclose(table->file);
}

void bare_insert(table_t* table, void* object) {
	if (table->file != NULL) {
		fseek(table->file, 0, SEEK_END);
		fwrite(object, table->element_size, 1, table->file);
	}
	else {
		_throw_error(table->filename, "bare_insert()");
	}
}

void bare_get(table_t* table, void* object, int index) {
	if (table->file != NULL) {
		fseek(table->file, index * table->element_size, SEEK_SET);
		fread(object, table->element_size, 1, table->file);
	}
	else {
		_throw_error(table->filename, "bare_get()");
	}
}

size_t bare_size(table_t* table) {
	if (table->file != NULL) {
		size_t bit_size;
		fseek(table->file, 0, SEEK_END);
		bit_size = ftell(table->file);
		fseek(table->file, 0, SEEK_SET);
		return bit_size / table->element_size;
	}
	else {
		_throw_error(table->filename, "bare_size()");
		return 0;
	}
}

void bare_update(table_t* table, void* object, int index) {
	if (table->file != NULL) {
		fseek(table->file, table->element_size * index, SEEK_SET);
		fwrite(object, table->element_size, 1, table->file);
	}
	else {
		_throw_error(table->filename, "bare_update()");
	}
}

void bare_delete(table_t* table, int index) {
	if (table->file != NULL) {
		FILE* new_file = fopen("newtemp.bin", "wb+");

		if (!new_file) {
			_throw_error("newtemp.bin", "bare_delete()");
			return;
		}

		FILE* old_file = table->file;
		size_t obj_size = table->element_size;
		int current_index = 0;

		void* obj = malloc(obj_size);

		if (!obj) {
			perror("Memory allocation error.");
			fclose(new_file);
			return;
		}

		fseek(old_file, 0, SEEK_SET);

		while (fread(obj, obj_size, 1, old_file)) {
			if (current_index != index) {
				fwrite(obj, obj_size, 1, new_file);
			}
			current_index++;
		}

		free(obj);
		table->file = new_file;
		fclose(old_file);
		remove(table->filename);
		rename("newtemp.bin", table->filename);
	}
	else {
		_throw_error(table->filename, "bare_delete()");
	}
}
