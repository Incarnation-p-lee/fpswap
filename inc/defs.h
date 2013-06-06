#ifndef DEFINITION_H
#define DEFINITION_H

#define FILENAME_LEN    128
#define COMMAND_LEN     128
#define NUL             (char)0
#define SPACE           " "
#define READ_LEN        4096

typedef enum OPERATION{NA, PUT, GET}OPT;

/* net related */
#define BUFFER_LEN      4096
#define RMT_PORT        (8192 << 2)
#define LOC_PORT        (8192 << 1)
/* Hard code IP for temporay */
#define REMOTE_IP       "192.168.0.103"
#define LOCAL_IP        "192.168.0.100"
#define LISTEN_COUNT    3
#define SEND_LEN        1024

#endif
