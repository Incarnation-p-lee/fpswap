#ifndef DEFINITION_H
#define DEFINITION_H

#define FILENAME_LEN    128
#define LENGTH_INDEX    124
#define COMMAND_LEN     128
#define SEND_CNT        128
#define NUL             (char)0
#define SPACE           " "
#define READ_LEN        4096
#define SEND_DELAY      1
#define DELAY           2
#define SPLITER         ":"
#define FREAD_LEN       (1024 << 10)

typedef enum OPERATION{
  NA, PUT, GET, CONT, EXIT,
}OPT;

/* net related */
#define BUFFER_LEN      FREAD_LEN
#define IP_LENGTH       16
#define FILE_CONFIG     "net.conf"


#define LISTEN_COUNT    3
#define SEND_LEN        1024


#define TIME_START      get_time_start()
#define TIME_END        get_time_end()

#endif
