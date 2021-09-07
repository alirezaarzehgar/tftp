#if !defined(TFTP_CMDTBL_H)
#define TFTP_CMDTBL_H

#include "tftp_sock_init.h"
#include "tftp_help.h"
#include "tftp_quit.h"
#include "tftp_mode.h"
#include "tftp_put.h"
#include "tftp_get.h"
#include "tftp_helper.h"
#include "tftp_connect.h"
#include "tftp_status.h"

#define N_CMDS            sizeof(cmdTable) / sizeof(struct cmd) - 1

struct cmd
{
  const char *name;

  const char *help;

  void (*handler) (int, char **);
};

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
    .help = "get help",
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

#endif // TFTP_CMDTBL_H
