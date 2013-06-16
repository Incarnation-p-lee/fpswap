#ifndef VARIABLE_H
#define VARIABLE_H

char get_filename[FILENAME_LEN];
char put_filename[FILENAME_LEN];
char command_line[COMMAND_LEN];

/* net related */
char rev_buf[BUFFER_LEN];
struct sockaddr_in addr_rmt;
struct sockaddr_in addr_loc;
int local_port;
int remote_port;
char local_ip[IP_LENGTH];
char remote_ip[IP_LENGTH];

/* file related */
char *send_buf;
FILE *fwriter;

#ifdef __linux__
int sock_srv;
int sock_clt;
struct timeval start;
struct timeval end;
#endif

#ifdef _WINDOWS_
SOCKET sock_srv;
SOCKET sock_clt;
SYSTEMTIME start;
SYSTEMTIME end;
#endif

#endif
