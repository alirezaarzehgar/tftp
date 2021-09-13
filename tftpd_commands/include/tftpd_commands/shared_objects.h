#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/fcntl.h>
#include <sys/types.h>
#include <dirent.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "tftp_hdr.h"

#if !defined(SHARED_OBJECT_H)
#define SHARED_OBJECT_H

#define MAXIPLEN          14
#define MAXMODELEN        10
#define MAX_ARG_CMD_LEN         4
#define MAX_FILENAME_LEN  225
#define MAX_USER_CMD_LEN  MAX_FILENAME_LEN + 4

#define RRQ               01
#define WRQ               02
#define DATA              03
#define ACK               04
#define ERROR             05

#define SEGMENT_SIZE      512
#define PACKET_SIZE       SEGMENT_SIZE+4

#define th_block  th_u1.th_u2.th_u3.tu_block
#define th_code   th_u1.th_u2.th_u3.tu_code
#define th_stuff  th_u1.tu_stuff
#define th_data   th_u1.th_u2.tu_data
#define th_msg    th_u1.th_u2.tu_data

struct tftp_connection
{
  int fd;

  struct sockaddr_in addr;

  socklen_t saddrLen;

  char mode[MAXMODELEN];
};

extern struct tftp_connection *tftp_conn;

#endif // SHARED_OBJECT_H
