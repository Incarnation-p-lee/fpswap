#ifndef DEFINITION_H
#define DEFINITION_H

#define FILENAME_LEN    128
#define LENGTH_INDEX    124
#define COMMAND_LEN     128
#define NUL             (char)0
#define SPACE           " "
#define READ_LEN        4096
#define SEND_DELAY      8
#define DELAY           2
#define SPLITER         ":"

typedef enum OPERATION{
  NA, PUT, GET, CONT, EXIT,
}OPT;

/* net related */
#define BUFFER_LEN      (1024 << 6)
#define IP_LENGTH       16
#define FILE_CONFIG     "net.conf"


#define LISTEN_COUNT    3
#define SEND_LEN        1024

#endif
