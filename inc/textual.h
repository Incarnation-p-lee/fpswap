#ifndef TEXTUAL_H
#define TEXTUAL_H


extern char get_filename[FILENAME_LEN];
extern char put_filename[FILENAME_LEN];

OPT
input_check(char *);
static void
ignore_space(char **);
static void
cpy_filename(char *, char *);
extern void
error_handle(const char*);


#endif
