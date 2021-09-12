/**
 * @file address_parser.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftpd_commands/parse_address.h"

bool
parse_address (char *addr, char **ip, int *port)
{
  char *tmp = (char *)malloc (sizeof (char) * 16);

	strncpy(tmp, addr, 16);

  *ip = strtok (tmp, ":");

  if ((tmp = strtok (NULL, ":")) != NULL)
    * port = atoi (tmp);
  else
    *port = 69;

  if (*port > MAX_PORT_NUMBER || *port < 1)
    return false;

  return true;
}