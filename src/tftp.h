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
  int fd;

  struct sockaddr_in saddr;

  socklen_t saddrLen;
};

struct cmd
{
  const char *name;

  const char *help;

  void (*handler) (int, char **);
};

typedef struct tftphdr tftphdr_t;

typedef struct tftp_socket tftp_socket_t;

tftp_socket_t *tftp_sock_init (int port, const char *ip);


/* commands */

void tftp_quit (int argc, char **argv);

void tftp_help (int argc, char **argv);

void tftp_put (int argc, char **argv);

void tftp_get (int argc, char **argv);

void tftp_status (int argc, char **argv);

void tftp_setbinary (int argc, char **argv);

void tftp_setascii (int argc, char **argv);

void tftp_connect (int argc, char **argv);

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
  }
};

void tftp_extract_argv (char *cmd, int *argc, char ***argv);

#endif // TFTP_H
