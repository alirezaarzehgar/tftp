#if !defined(ARGPARSE_H)
#define ARGPARSE_H

#include <stdbool.h>
#include <string.h>

#define ERROR_INVALID_IP   "invalid ipv4 %s\n" \
                            "use default ipv4 " DEFAULT_IP ", "
#define ERROR_INVALID_MODE  "%s is invalid mode\n"

#define ERROR_INVALID_PORT  "invalid port number : %d, use default port number\n"

#define ERROR_INVALID_CMD   "invalid command : %s\n"

#ifndef __MODES__
#define __MODES__
static char *modes[] =
{
  "netascii", "octet"
};

#endif // !__MODES__

#ifndef __CMDS__
#define __CMDS__
static char *argcmds[] =
{
  "get", "put"
};

#endif // !__CMDS__

bool ip_validator (char *ip);

bool filename_validator (char *cmd, char *filename);

bool mode_validator (char *mode);

bool port_validator(int port);

bool cmd_validator(char *cmd);

#endif // ARGPARSE_H
