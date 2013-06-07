#ifndef DEFINITION_H
#define DEFINITION_H

#define FILENAME_LEN    128
#define LENGTH_INDEX    124
#define COMMAND_LEN     128
#define NUL             (char)0
#define SPACE           " "
#define READ_LEN        4096
#define DELAY           2

typedef enum OPERATION{
  NA, PUT, GET, CONT,                     
}OPT;

/* net related */
#define BUFFER_LEN      (1024 << 6)

#ifdef __linux__
#define RMT_PORT        (8192 << 1)
#define LOC_PORT        (8192 << 2)
/* Hard code IP for temporay */
#define REMOTE_IP       "192.168.0.100"
#define LOCAL_IP        "192.168.0.101"
#endif

#ifdef WIN32
#define RMT_PORT        (8192 << 2)
#define LOC_PORT        (8192 << 1)
/* Hard code IP for temporay */
#define REMOTE_IP       "192.168.0.101"
#define LOCAL_IP        "192.168.0.100"
#endif

#define LISTEN_COUNT    3
#define SEND_LEN        1024

#endif
