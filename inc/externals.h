#ifndef EXTERNALS_H
#define EXTERNALS_H

extern OPT
input_check(char *);
extern void
init_socket(void);
extern void
data_send(int, char*, int);
extern int
file_buf(const char*);
extern void
error_handle(const char*);

#endif
