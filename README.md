## bincmp: a simple utility that compares byte-by-byte two files

### Why?

* I needed this for a project.
* To do something in good old C.

### Usage

* cc -o bincmp bincmp.c
* ./bincmp file1 file2

then you will get a table of the differences between the two files, in the format of

offset   file1   file2


