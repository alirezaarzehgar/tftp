#if !defined(TFTP_SOCK_H)
#define TFTP_SOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

struct  tftphdr
{
  short th_opcode;      /* packet type */
  union
  {
    char  tu_padding[3];    /* sizeof() compat */
    struct
    {
      union
      {
        unsigned short  tu_block; /* block # */
        short tu_code;    /* error code */
      } __attribute__ ((__packed__)) th_u3;
      char tu_data[0];  /* data or error string */
    } __attribute__ ((__packed__)) th_u2;
    char  tu_stuff[0];    /* request packet stuff */
  } __attribute__ ((__packed__)) th_u1;
} __attribute__ ((__packed__));

struct tftp_socket
{
  bool empty;

  int fd;

  struct sockaddr_in saddr;

  socklen_t saddrLen;

  char mode[MAXMODELEN];
};

typedef struct tftphdr tftphdr_t;

typedef struct tftp_socket tftp_socket_t;

int tftp_sock_init (int port, const char *ip, char *mode);

void tftp_sock_close();

void tftp_sock_restart (int port);

#endif // TFTP_SOCK_H
