/**
 * @file tftp_mode.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/tftp_mode.h"

extern tftp_socket_t
*global_tst;     /* global tftp socket strcuture for connection info */
extern char buf[BUFSIZ];              /* buffer for holding packet contents */

void
set_mode (int argc, char *mode)
{
  if (global_tst == NULL)
    global_tst = malloc (sizeof (tftp_socket_t));


  if (mode_validator (mode))
    strncpy (global_tst->mode, mode, MAXMODELEN);
}


void
tftp_setbinary (int argc, char **argv)
{
  if (argument_error (argc, 1))
    return;

  set_mode (argc, "octet");
}

void
tftp_setascii (int argc, char **argv)
{
  if (argument_error (argc, 1))
    return;


  set_mode (argc, "netascii");
}