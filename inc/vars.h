#ifndef VARIABLE_H
#define VARIABLE_H

char get_filename[FILENAME_LEN];
char put_filename[FILENAME_LEN];
static char command_line[COMMAND_LEN];

/* net related */
char rev_buf[BUFFER_LEN];
struct sockaddr_in addr_rmt;
struct sockaddr_in addr_loc;
int sock_loc;
int sock_rmt;

#endif
