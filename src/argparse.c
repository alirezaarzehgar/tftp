/**
 * @file argparse.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "common/common.h"
#include "tftp.h"
#include "argparse.h"

bool
ip_validator (char *ip)
{
  struct sockaddr_in s;

  int result = inet_aton (ip, &s.sin_addr);

  return result != 0;
}

bool
filename_validator (char *cmd, char *filename)
{
  return strcmp (cmd, "put") == 0 || access (filename, F_OK) == 0;
}

static inline bool
valid_item (char *item, char **items)
{
  int flag = false;

  for (size_t i = 0; i <= sizeof (items) / sizeof (char *); i++)
    {
      if (strcmp (item, items[i]) == 0)
        flag = true;
    }

  return flag;
}

bool
mode_validator (char *mode)
{
  return valid_item (mode, modes);
}

bool
port_validator (int port)
{
  return port > 1 && port < MAX_PORT_NUMBER;
}

bool
cmd_validator (char *cmd)
{
  return valid_item (cmd, argcmds);
}
