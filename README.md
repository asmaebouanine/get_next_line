
# get_next_line

## Introduction

The get_next_line project is about creating a function that reads a file line by line. Every time you call the function, it returns the next line from the file. This is useful when working with large files where you don't want to load the entire content into memory at once.

---

## Goal

Write a function:
  
```c
char *get_next_line(int fd);
```

This function should:

* Read from a file one line at a time.
* Return the line each time it is called.
* Handle multiple files at the same time.

---

## How It Works

1. You give the function a file descriptor (from `open()` or `STDIN_FILENO`).
2. It reads from the file until it finds a newline (`\n`) or the end of the file.
3. It returns the line as a string.
4. You call the function again to get the next line.

---

## Project Rules

* You must not read the whole file at once.
* You can only use the allowed C functions (`read`, `malloc`, etc.).
* You must handle memory correctly (no leaks).
* Use a buffer size defined by `BUFFER_SIZE`.

---

## Key Concepts

* **File Descriptors**: Numbers that refer to open files.
* **Buffers**: Small memory spaces to read parts of a file.
* **Dynamic Memory**: You need to use `malloc` to return strings.
* **Static Variables**: Used to remember data between function calls.
* **Newline Detection**: Stop reading when a full line is found.

---

## Conclusion

The `get_next_line` project teaches you how to read from a file step by step. It helps improve your understanding of memory, file handling, and how to write clean and efficient C code. You will learn how to manage reading with limited memory and return results piece by piece.
