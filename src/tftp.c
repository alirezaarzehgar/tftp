/**
 * @file tftp.c
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
#include "messages.h"
#include "common/malloc3d.h"


/**
 * @brief initialize a socket for tftp connections
 *
 * @param port
 * @param ip
 * @return tftp_socket_t*
 */
tftp_socket_t *
tftp_sock_init (int port, const char *ip)
{
  tftp_socket_t *tst;

  int retval;

  tst = malloc (sizeof (tftp_socket_t));

  /* create socket */

  tst->fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (tst->fd == -1)
    return NULL;

  /* binding */
  tst->saddr.sin_family = AF_INET;

  tst->saddr.sin_port = htons (port);

  tst->saddr.sin_addr.s_addr = inet_addr (ip);

  tst->saddrLen = sizeof (tst->saddr);

  return tst;
}

/* user interface commands */

void
tftp_quit (int argc, char **argv)
{
  (void)argc;
  (void)argv;

  printf (GOODBYE_MSG);
  exit (EXIT_SUCCESS);
}

void
tftp_help (int argc, char **argv)
{

}

void
tftp_put (int argc, char **argv)
{

}

void
tftp_get (int argc, char **argv)
{

}

void
tftp_status (int argc, char **argv)
{

}

void
tftp_setbinary (int argc, char **argv)
{

}

void
tftp_setascii (int argc, char **argv)
{

}

void
tftp_connect (int argc, char **argv)
{

}

void
tftp_extract_argv (char *cmd, int *argc, char ***argv)
{
  char *tmp;

  int ac;

  char **cp;

  *argv = NULL;

  cp = (char **)malloc3d (20, sizeof (char) * 15);

  ac = 0;

  cp[ac++] = strtok (cmd, " ");
  
  while ((tmp = strtok (NULL, " ")) != NULL)
  {
    cp[ac++] = tmp;
  }

  cp[ac - 1][strlen(cp[ac - 1]) - 1] = '\0';

  printf("%s\n", cp[ac - 1]);

  *argc = ac;

  *argv = cp;
}
