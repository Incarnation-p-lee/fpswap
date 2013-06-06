#ifndef NETWORK_H
#define NETWORK_H

extern void
error_handle(const char*);
extern void
data_recv(int, char*);

extern char rev_buf[BUFFER_LEN];
extern struct sockaddr_in addr_rmt;
extern struct sockaddr_in addr_loc;
extern int sock_clt;
extern int sock_srv;


void
init_socket(void);
void
data_send(int, char*, int);
void
data_recv(int, char*);
static void *
server_start(void*);
static void 
net_send(int, char*, int);
static void
init_socket_parms(void);

#endif
