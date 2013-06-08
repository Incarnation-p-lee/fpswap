#ifndef IOFILE_H
#define IOFILE_H

extern char *send_buf;

extern void
error_handle(const char*);

int
file_buf(char*);
void
file_write(FILE**, char*, int);
FILE*
file_create(char*);

#endif
