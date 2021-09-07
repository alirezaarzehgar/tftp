#if !defined(TFTP_H)
#define TFTP_H

#include "common/common.h"

#define MAXIPLEN          14
#define MAXMODELEN        10
#define MAX_ARG_CMD_LEN         4
#define MAX_FILENAME_LEN  225
#define MAX_USER_CMD_LEN  MAX_FILENAME_LEN + 4

#define MAX_PORT_NUMBER   65535

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

/**/
#define N_CMDS            sizeof(cmdTable) / sizeof(struct cmd) - 1

/**
 * @brief tftp header
 *
 */
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

struct cmd
{
  const char *name;

  const char *help;

  void (*handler) (int, char **);
};

typedef struct tftphdr tftphdr_t;

typedef struct tftp_socket tftp_socket_t;

int tftp_sock_init (int port, const char *ip, char *mode);

void tftp_sock_close();

void tftp_sock_restart (int port);

/* commands */

void tftp_quit (int argc, char **argv);

void tftp_help (int argc, char **argv);

void tftp_put (int argc, char **argv);

void tftp_get (int argc, char **argv);

void tftp_status (int argc, char **argv);

void tftp_setbinary (int argc, char **argv);

void tftp_setascii (int argc, char **argv);

void tftp_connect (int argc, char **argv);

void tftp_nothing (int argc, char **argv);

/* command table */

static struct cmd cmdTable[] =
{
  {
    .name = "put",
    .help = "send file",
    .handler = tftp_put
  },
  {
    .name = "get",
    .help = "receive file",
    .handler = tftp_get
  },
  {
    .name = "connect",
    .help = "connect to remote tftp",
    .handler = tftp_connect
  },
  {
    .name = "binary",
    .help = "set mode to octet",
    .handler = tftp_setbinary
  },
  {
    .name = "ascii",
    .help = "set mode to netascii",
    .handler = tftp_setascii
  },
  {
    .name = "help",
    .help = "print help information",
    .handler = tftp_help
  },
  {
    .name = "?",
    .help = "print help information",
    .handler = tftp_help
  },
  {
    .name = "quit",
    .help = "exit tftp",
    .handler = tftp_quit
  },
  {
    .name = "status",
    .help = "show current status",
    .handler = tftp_status
  },
  {"", "", tftp_nothing}
};

void tftp_extract_argv (char *cmd, int *argc, char ***argv);

#endif // TFTP_H
