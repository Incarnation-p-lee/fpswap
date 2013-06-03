#ifndef INCLUDE_H
#define INCLUDE_H


#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>


#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif


#ifdef __WINDOWS__

#endif


#endif
