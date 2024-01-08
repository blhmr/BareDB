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

2. Include the `baredb.h` header file in your C program.

3. Link your program with `baredb.c`.

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

**MIT License**

Copyright (c) 2024 Hatim

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.