#ifndef IOFILE_H
#define IOFILE_H

extern char *send_buf;
extern FILE *fwriter;

extern void
error_handle(const char*);

int
file_buf(char*);
void
file_write(char*, int);
void
file_create(char*);

#endif
