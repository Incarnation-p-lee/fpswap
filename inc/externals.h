#ifndef EXTERNALS_H
#define EXTERNALS_H

extern OPT
input_check(char *);
extern void
init_socket(void);
extern void
data_send(char*, char*, int);
extern void
error_handle(const char*);
extern void
env_reset(void);

#endif
