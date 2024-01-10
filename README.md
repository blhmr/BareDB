# BareDB - Minimalistic and Lightweight C Library for Generic Struct Database

BareDB is a lightweight and easy-to-use C library for basic database operations. It allows you to add, read, update, and delete structs in a database file.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Why BareDB] (#why-baredb)
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
- Delete structs at a specific index from a .db file (Soon...)
- More in the future
(You can use .bin files)

## Why BareDB

BareDB offers a compelling choice for developers seeking a straightforward and efficient solution for basic database operations in the C programming language. As a lightweight and user-friendly C library, BareDB simplifies the process of managing structured data by providing an intuitive interface for adding, reading, updating, and deleting structs (soon) within a database file. Its simplicity allows even those new to database programming to seamlessly incorporate database functionalities into their C applications. With BareDB, developers can leverage its ease of use and minimalist design to streamline their codebase, ensuring that database operations are both accessible and efficient. Whether for small-scale projects or as an easy-to-integrate component in larger applications, BareDB stands out as a valuable tool for simplifying the implementation of fundamental database functionalities in C, contributing to a more straightforward and organized development process.

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

3. Clean:
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

See the examples directory for usage examples. (Coming soon)

## Contributing

Contributions are welcome! Feel free to open issues, submit pull requests, or provide feedback.

## License

BareDB is open-source software licensed under the [MIT License](LICENSE).
