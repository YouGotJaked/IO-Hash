# I/0 Hash
This program use hashes in order to solve an I/O or file systems' related problem.

## Compilation

A Makefile has been included to easily compile all C source files in this project. Type the following to compile them all:

```
make all
```

If any of the files fail to compile, they can also be compiled using the respective commands below.

## File Descriptions

### output.c

This file accept an input file `src.txt` containing a sequences of strings. It reads each string until an end of file is detected, and outputs the following:
- the length of the string
- the string itself
- the result of applying the hash function on the string.
- the result of applying the hash function on the string and the preceding hash value (i.e., concatenating the string with the hash value, where the very first string assumes the preceding hash was simply the null string).

The output of this program is sent to stdout and then piped into a new file `des.txt`.

Compilation:

```
gcc -o output output.c -L/usr/local/lib/ -lssl -lcrypto
```

Execution:

```
./output <input file> 2>&1 | tee <output file>
```

### invalid.c

This file takes the output file of `output.c` as its input and prints out a message indicating if any strings in the file do not have a valid hash code.

Compilation:

```
gcc -o invalid invalid. -L/usr/local/lib/ -lssl -lcrypto
```

Execution:

```
./invalid <input file>
```

### omission.c

This file takes the output file of `output.c` as its input and prints out a message indicating if it has detected an omission from the file.

Compilation:

```
gcc -o omission omission.c -L/usr/local/lib/ -lssl -lcrypto
```

Execution:

```
./omission <input file>
```

### helper.c

This file, along with `helper.h`, contains all of the functions to be used in the preceeding functions. It also contains the structure declaration `data` used to hold the strings, string length, and hash values.

### CosmicRay.c

This file simulates the occasional random bit flips caused by high-energy rays. It inserts a random ASCII character at some random location in the file. It is used to test `invalid.c` and `omission.c`.

Compilation:

```
gcc -o CosmicRay CosmicRay.c
```

Execution:

```
./CosmicRay <input file>
```

### key_value.c

This file, along with `key_value.h`,  contains a `SET` data structure with each element containing a string and a hash value. This structure uses the hash values to prevent adding duplicate strings.

### test.c

This file is used to test the `SET` data structure. It takes in an input file and reads each word in the file. All unique elements are added to the set. The user is then prompted to search to see if a word is found in the set. If the word is found, its hash value is returned. The file also returns the total number of words read as well as number of distinct words.

Compilation:

```
gcc -o test test.c
```

Execution:

```
./test <input file>
```

## Analysis

1. How would you use such a program to detect duplicate strings (without modifying the programs themselves, but only using operations conducted on their output)?

2. How would you save space, using the key-lookup that you have previousy implemented, if you were told that the strings were very long, and that many of them were identical to each other?
