/**
 * @file validator.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-12W
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftpd_commands/validator.h"

bool
validate_dir_path_exists (char *path)
{
  return access (path, F_OK) == F_OK && opendir (path) != NULL;
}

bool
validate_address (char *addr)
{
  int tmpfd;

  struct sockaddr_in saddr;

  char *ip = (char *)malloc (sizeof (char) * 16);

  int port;

  if (!parse_address (addr, &ip, &port))
    return false;

  tmpfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (tmpfd == -1)
    return false;

  saddr.sin_addr.s_addr = inet_addr (ip);
  saddr.sin_family = AF_INET;
  saddr.sin_port = port;

  return inet_aton (ip, NULL)
         && bind (tmpfd, (struct sockaddr *)&saddr, sizeof (saddr)) == 0
         && close (tmpfd) == 0;
}