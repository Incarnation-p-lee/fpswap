#ifndef NETWORK_H
#define NETWORK_H

extern void
error_handle(const char*);

extern char rev_buf[BUFFER_LEN];
extern struct sockaddr_in addr_rmt;
extern struct sockaddr_in addr_loc;
extern int sock_loc;
extern int sock_rmt;


void
init_socket(void);
static void
server_start(void);

#endif
