#ifndef NETWORK_H
#define NETWORK_H

extern void
error_handle(const char*);
extern void
data_recv(int, char*);
extern FILE *
file_create(char*);
extern void
file_write(char*, int);
extern int
file_buf(FILE*);

extern char rev_buf[BUFFER_LEN];
extern struct sockaddr_in addr_rmt;
extern struct sockaddr_in addr_loc;
extern int sock_clt;
extern int sock_srv;
extern char put_filename[FILENAME_LEN];
extern FILE *fwriter;
extern int local_port;
extern int remote_port;
extern char local_ip[IP_LENGTH];
extern char remote_ip[IP_LENGTH];

void
init_socket(void);
void
data_recv(int, char*);
void
data_send(char*, char*, int);
void
net_setup(void);
static void *
server_start(void*);
static void 
net_send(int, char*, int);
static void
init_socket_parms(void);
static void
net_recv_write(int, char*, int);
static int
net_setup_handle(char*, int, FILE*);
static void
frame_send(int, char*, int);

#endif
