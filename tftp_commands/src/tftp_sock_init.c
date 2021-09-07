/**
 * @file tftp_sock.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/tftp_sock_init.h"

/* global tftp socket strcuture for connection info */
tftp_socket_t *global_tst;

/* buffer for holding packet contents */
char buf[BUFSIZ];

/**
 * @brief initialize a socket for tftp connections
 *
 * @param port
 * @param ip
 * @return int
 */
int
tftp_sock_init (int port, const char *ip, char *mode)
{
  int retval;

  global_tst = malloc (sizeof (tftp_socket_t));

  /* create socket */

  global_tst->fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (global_tst->fd == -1)
    return -1;

  /* binding */
  global_tst->saddr.sin_family = AF_INET;

  global_tst->saddr.sin_port = htons (port);

  global_tst->saddr.sin_addr.s_addr = inet_addr (ip);

  global_tst->saddrLen = sizeof (global_tst->saddr);

  /* set default mode */
  global_tst->empty = false;

  strncpy (global_tst->mode, mode, MAXMODELEN);

  return 0;
}

void
tftp_sock_close()
{
  close (global_tst->fd);

  bzero (buf, BUFSIZ);

  global_tst->empty = true;
}

void
tftp_sock_restart (int port)
{
  tftp_sock_close();

  tftp_sock_init (port, inet_ntoa (global_tst->saddr.sin_addr),
                  global_tst->mode);
}
