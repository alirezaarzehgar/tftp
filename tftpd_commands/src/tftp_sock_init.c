/**
 * @file sock_init.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftpd_commands/tftp_sock_init.h"

struct tftp_connection *tftp_conn;

bool
tftp_sock_init (char *ip, u_short port)
{
  int retval;

  tftp_conn = (struct tftp_connection *)malloc (sizeof (struct tftp_connection));

  tftp_conn->fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (tftp_conn->fd == -1)
    return false;

  bzero (tftp_conn->mode, 10);

  tftp_conn->addr.sin_family = AF_INET;

  tftp_conn->addr.sin_port = htons (port);

  tftp_conn->addr.sin_addr.s_addr = inet_addr (ip);

  tftp_conn->saddrLen = sizeof (tftp_conn->addr);

  retval = bind (tftp_conn->fd, (struct sockaddr *)&tftp_conn->addr,
                 tftp_conn->saddrLen);

  if (retval == -1)
    return false;

  return true;
}