#ifndef MAINTAIN_H
#define MAINTAIN_H


extern char get_filename[FILENAME_LEN];
extern char put_filename[FILENAME_LEN];
extern char rev_buf[BUFFER_LEN];
extern char *send_buf;
extern char command_line[COMMAND_LEN];


void
error_handle(const char *);
void
env_reset(void);
static void
buffer_clearup(void);

#endif
