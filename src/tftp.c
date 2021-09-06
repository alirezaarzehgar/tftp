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
usage (char *name)
{
  int flag = 0;
  for (size_t i = 0; i < N_CMDS; i++)
    {
      if (cmdTable[i].name != NULL && strcmp (name, cmdTable[i].name) == 0)
        {
          printf ("%s\t\t%s\n", cmdTable[i].name, cmdTable[i].help);
          flag = 1;
        }
    }

  if (!flag)
    printf ("%s not found\n", name);
}

void
tftp_help (int argc, char **argv)
{
  if (argc == 1)
    {
      for (size_t i = 1; i < N_CMDS; i++)
        usage ((char *)cmdTable[i].name);

      return;
    }

  for (size_t i = 1; i < argc; i++)
    usage (argv[i]);
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

  char *ch;

  int cpArgc;

  char **cpArgv;

  *argv = NULL;

  cpArgv = (char **)malloc3d (20, sizeof (char) * 15);

  cpArgc = 0;

  cpArgv[cpArgc++] = strtok (cmd, " ");

  while ((tmp = strtok (NULL, " ")) != NULL)
    cpArgv[cpArgc++] = tmp;

  ch = (char *)&cpArgv[cpArgc - 1][strlen (cpArgv[cpArgc - 1]) - 1];

  *ch = *ch == '\n' ? '\0' : *ch;

  ch = (char *)&cpArgv[cpArgc - 1][0];

  if (ch[0] == '\0')
    cpArgc--;

  *argc = cpArgc;

  *argv = cpArgv;
}
