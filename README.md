# BareDB - Minimalistic and Lightweight C Library for Generic Struct Database

BareDB is a lightweight and easy-to-use C library for basic database operations. It allows you to add, read, update, and delete structs in a database file.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Limitations](#limitations)
- [Why BareDB](#why-baredb)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Overview

BareDB is designed to provide a simple yet powerful solution for basic database operations in C. It is open-source and released under the MIT License.

## Features

- Add structs to a database
- Read structs from a database
- Update structs in a database
- Delete structs at a specific index from a database
- More in the future
(You can use .bin files)

## Limitations
- Not endian clean, so portability is an issue especially when you want to write in a little endian machine and read data in a big endian machine (or vice-versa) (Working on this issue)

## Why BareDB

BareDB simplifies basic database operations in C with a user-friendly and lightweight approach. It provides an intuitive interface for adding, reading, updating, and deleting structs in a database file. Even for beginners, BareDB offers a straightforward way to incorporate database functionalities into C applications. Its minimalist design streamlines code, making database operations accessible and efficient. Whether for small projects or as a component in larger applications, BareDB is a valuable tool, simplifying the implementation of fundamental database functions in C.

## Getting Started

To use BareDB in your C project, follow these steps:

1. Clone this repo:
```bash
git clone https://github.com/blhmr/BareDB.git
```

2. Change directory and build to see an example of usage (`main.c`):
```bash
cd BareDB
make build
./main
```

3. In case you to install the library as a default library on your system (Linux):
- For a static library:
```bash
gcc -c baredb.c -o libbaredb.o # Compile the Library
ar rcs libbaredb.a libbaredb.o
sudo cp libbaredb.so /usr/lib # Copy the Library
sudo ldconfig # Update Library Cache
sudo cp baredb.h /usr/include # Include Header Files
```

Usage in Programs:
```c
#include <baredb.h>

int main(void) {
    // Your program logic using BareDB functions
    return 0;
}
```

```bash
gcc -o your_program your_program.c -lbaredb
```

5. Clean:
```bash
make clean
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
Of course you can read `main.c` to see how all the functions work!

## Examples

See the examples directory for usage examples.

## Contributing

Contributions are welcome! Feel free to open issues, submit pull requests, or provide feedback.

## License

BareDB is open-source software licensed under the [MIT License](LICENSE).
