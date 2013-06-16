#ifndef MAINTAIN_H
#define MAINTAIN_H


extern char get_filename[FILENAME_LEN];
extern char put_filename[FILENAME_LEN];
extern char rev_buf[BUFFER_LEN];
extern char *send_buf;
extern char command_line[COMMAND_LEN];


#ifdef __linux__
extern struct timeval start;
extern struct timeval end;
#endif

#ifdef _WINDOWS_
extern SYSTEM start;
extern SYSTEM end;
#endif


void
error_handle(const char *);
void
env_reset(void);
static void
buffer_clearup(void);
void
get_time_start(void);
unsigned long long
get_time_end(void);


#endif
