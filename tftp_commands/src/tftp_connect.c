/**
 * @file tftp_connect.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "tftp_commands/tftp_connect.h"

extern tftp_socket_t
*global_tst;     /* global tftp socket strcuture for connection info */
extern char buf[BUFSIZ];              /* buffer for holding packet contents */

void
tftp_connect (int argc, char **argv)
{
  if (argument_error (argc, 2))
    return;

  if (global_tst == NULL)
    global_tst = malloc (sizeof (tftp_socket_t));

  if (ip_validator (argv[1]))
    global_tst->saddr.sin_addr.s_addr = inet_addr (argv[1]);
  else
    fprintf (stderr, MSG_INVALID_IP, argv[1]);
}

