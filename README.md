# BareDB - Minimalistic and Lightweight C Library for Generic Struct Database

BareDB is a lightweight and easy-to-use C library for basic database operations. It allows you to add, read, update, and delete structs in a database file.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Overview

BareDB is designed to provide a simple yet powerful solution for basic database operations in C. It is open-source and released under the MIT License.

## Features

- Add structs to a .db file
- Read structs from a .db file
- Update structs in a .db file
- Delete structs at a specific index from a .db file
- More in the future
(You can use .bin files)

## Getting Started

To use BareDB in your C project, follow these steps:

1. Clone the repository or download the source files.
```git clone https://github.com/blhmr/BareDB.git```

2. Create an installation script.
```bash
#!/bin/bash

# Compile the library
gcc -c src/baredb.c -o libbaredb.o

# Create a shared library
gcc -shared -o libbaredb.so libbaredb.o

# Copy the header file to the default include directory
cp baredb.h /usr/include/

# Copy the library file to the default library directory
cp libbaredb.so /usr/lib/

# Inform the user about the installation
echo "BareDB library installed successfully!"
```
3. Run the installation.
```bash
chmod +x install.sh
./install.sh
```

## Usage

Bellow is a simple program to insert a point struct into a "database.db" database:

```c
#include "baredb.h"

typedef struct {
    int x;
    int y;
} point;

int main(void) {
    // Open the database
    table_t table;
    bare_open(&table, "database.db", sizeof(point));

    // Create a point struct with specific values
    point p = {.x = 5, .y = 10};

    // Insert the point struct into the database
    bare_insert(&table, &p);

    // Close the database
    bare_close(&table);

    return 0;
}
```

## Examples

See the examples directory for usage examples.

## Contributing

Contributions are welcome! Feel free to open issues, submit pull requests, or provide feedback.

## License

BareDB is open-source software licensed under the [MIT License](LICENSE).
