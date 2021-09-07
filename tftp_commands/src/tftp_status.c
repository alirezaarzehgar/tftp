/**
 * @file tftp_status.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/tftp_status.h"

extern tftp_socket_t
*global_tst;     /* global tftp socket strcuture for connection info */
extern char buf[BUFSIZ];              /* buffer for holding packet contents */

void
tftp_status (int argc, char **argv)
{
  if (global_tst == NULL || global_tst->empty != false)
  {
    fprintf (stderr, MSG_CONNECTION_INIT_ERR);
    exit (EXIT_FAILURE);
  }

  char *ip = inet_ntoa (global_tst->saddr.sin_addr);

  printf (MSG_CONNECTED_TO_FORMAT, ip != NULL ? ip : MSG_UNDEFINED);

  printf (MSG_PORT_STATUS, htons (global_tst->saddr.sin_port));

  printf (MSG_MODE_FORMAT, mode_validator (global_tst->mode) ? global_tst->mode :
          MSG_UNDEFINED);
}
